<?php
/**
 * @file
 * Integration layer to communicate with the Twitter REST API 1.1.
 * https://dev.twitter.com/docs/api/1.1
 *
 * Modified for Social Actions from https://www.drupal.org/project/twitter
 * includes/twitter.lib.php
 * Removed unneeded methods and config variables -  We only need
 * to post status updates
 *
 * Original work my James Walker (@walkah).
 * Upgraded to 1.1 by Juampy (@juampy72).
 */

/**
 * Exception handling class.
 */
class socialTwitterException extends Exception {}

/**
 * Primary Twitter API implementation class
 */
class socialTwitter {
  /**
   * @var $source the twitter api 'source'
   */
  protected $source = 'drupal';

  protected $signature_method;

  protected $consumer;

  protected $token;


  /********************************************//**
   * Authentication
   ***********************************************/
  /**
   * Constructor for the Twitter class
   */
  public function __construct($consumer_key, $consumer_secret, $oauth_token = NULL,
                              $oauth_token_secret = NULL) {
    $this->signature_method = new OAuthSignatureMethod_HMAC_SHA1();
    $this->consumer = new OAuthConsumer($consumer_key, $consumer_secret);
    if (!empty($oauth_token) && !empty($oauth_token_secret)) {
      $this->token = new OAuthConsumer($oauth_token, $oauth_token_secret);
    }
  }

  public function get_request_token($params = array()) {
    $oauth_callback = variable_get('social_actions_twitter_callback_url', SBA_TWITTER_OAUTH_CALLBACK_URL);
    $url = SBA_TWITTER_API . '/oauth/request_token';

    try {
      $params += array('oauth_callback' => url($oauth_callback, array('absolute' => TRUE)));
      $response = $this->auth_request($url, $params);
    }
    catch (socialTwitterException $e) {
      watchdog('twitter', '!message', array('!message' => $e->__toString()), WATCHDOG_ERROR);
      return FALSE;
    }
    parse_str($response, $token);
    $this->token = new OAuthConsumer($token['oauth_token'], $token['oauth_token_secret']);
    return $token;
  }

  public function get_authorize_url($token) {
    $url =  SBA_TWITTER_API . '/oauth/authorize';
    $url.= '?oauth_token=' . $token['oauth_token'];

    return $url;
  }

  public function get_authenticate_url($token) {
    $url = SBA_TWITTER_API . '/oauth/authenticate';
    $url.= '?oauth_token=' . $token['oauth_token'];

    return $url;
  }

  /**
   * Request an access token to the Twitter API.
   * @see https://dev.twitter.com/docs/auth/implementing-sign-twitter
   *
   * @param string$oauth_verifier
   *   String an access token to append to the request or NULL.
   * @return
   *   String the access token or FALSE when there was an error.
   */
  public function get_access_token($oauth_verifier = NULL) {
    $url = SBA_TWITTER_API . '/oauth/access_token';

    // Adding parameter oauth_verifier to auth_request
    $parameters = array();
    if (!empty($oauth_verifier)) {
      $parameters['oauth_verifier'] = $oauth_verifier;
    }

    try {
      $response = $this->auth_request($url, $parameters);
    }
    catch (socialTwitterException $e) {
      watchdog('twitter', '!message', array('!message' => $e->__toString()), WATCHDOG_ERROR);
      return FALSE;
    }
    parse_str($response, $token);
    $this->token = new OAuthConsumer($token['oauth_token'], $token['oauth_token_secret']);
    return $token;
  }

  /**
   * Performs an authenticated request.
   */
  public function auth_request($url, $params = array(), $method = 'GET') {
    $request = OAuthRequest::from_consumer_and_token($this->consumer, $this->token, $method, $url, $params);
    $request->sign_request($this->signature_method, $this->consumer, $this->token);

    try {
      switch ($method) {
        case 'GET':
          return $this->request($request->to_url());
        case 'POST':
          return $this->request($request->get_normalized_http_url(), $request->get_parameters(), 'POST');
      }
    }
    catch (socialTwitterException $e) {
      watchdog('twitter', '!message', array('!message' => $e->__toString()), WATCHDOG_ERROR);
      return FALSE;
    }
  }

  /**
   * Performs a request.
   *
   * @throws socialTwitterException
   */
  protected function request($url, $params = array(), $method = 'GET') {
    $data = '';
    if (count($params) > 0) {
      if ($method == 'GET') {
        $url .= '?'. http_build_query($params, '', '&');
      }
      else {
        $data = http_build_query($params, '', '&');
      }
    }

    $headers = array();

    $headers['Authorization'] = 'Oauth';
    $headers['Content-type'] = 'application/x-www-form-urlencoded';

    $response = $this->doRequest($url, $headers, $method, $data);
    if (!isset($response->error)) {
      return $response->data;
    }
    else {
      $error = $response->error;
      $data = $this->parse_response($response->data);
      if (isset($data['error'])) {
        $error = $data['error'];
      }
      throw new socialTwitterException($error);
    }
  }
  

  /**
   * Actually performs a request.
   *
   * This method can be easily overriden through inheritance.
   *
   * @param string $url
   *   The url of the endpoint.
   * @param array $headers
   *   Array of headers.
   * @param string $method
   *   The HTTP method to use (normally POST or GET).
   * @param array $data
   *   An array of parameters
   * @return
   *   stdClass response object.
   */
  protected function doRequest($url, $headers, $method, $data) {
    $response = drupal_http_request($url, array('headers' => $headers, 'method' => $method, 'data' => $data));
    return $response;
  }

  /**
   * @see https://www.drupal.org/node/985544
   */
  protected function parse_response($response) {
    $length = strlen(PHP_INT_MAX);
    $response = preg_replace('/"(id|in_reply_to_status_id|in_reply_to_user_id)":(\d{' . $length . ',})/', '"\1":"\2"', $response);
    return json_decode($response, TRUE);
  }

  /**
   * Creates an API endpoint URL.
   *
   * @param string $path
   *   The path of the endpoint.
   * @param string $format
   *   The format of the endpoint to be appended at the end of the path.
   * @return
   *   The complete path to the endpoint.
   */
  protected function create_url($path, $format = '.json') {
    $url =  SBA_TWITTER_API .'/1.1/'. $path . $format;
    return $url;
  }

  /**
   * Updates the authenticating user's current status, also known as tweeting.
   *
   * @param string $status
   *   The text of the status update (the tweet).
   * @param array $params
   *   an array of parameters.
   *
   * @see https://dev.twitter.com/docs/api/1.1/post/statuses/update
   */
  public function statuses_update($status, $params = array()) {
    $params['status'] = $status;
    $values = $this->call('statuses/update', $params, 'POST');
    return $values;
  }

  public function users_show($screen_name, $include_entities = NULL) {
    $params = array();
    $params['screen_name'] = $screen_name;
    if ($include_entities !== NULL) {
      $params['include_entities'] = $include_entities;
    }
    $values = $this->call('users/show', $params, 'GET');
    return $values;
  }

  /********************************************//**
   * Utilities
   ***********************************************/
  /**
   * Calls a Twitter API endpoint.
   */
  public function call($path, $params = array(), $method = 'GET') {
    $url = $this->create_url($path);

    try {
      $response = $this->auth_request($url, $params, $method);
    }
    catch (socialTwitterException $e) {
      watchdog('twitter', '!message', array('!message' => $e->__toString()), WATCHDOG_ERROR);
      return FALSE;
    }

    if (!$response) {
      return FALSE;
    }

    return $this->parse_response($response);
  }
}
