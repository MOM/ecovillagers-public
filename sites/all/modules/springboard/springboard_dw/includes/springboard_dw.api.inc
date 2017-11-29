<?php
/**
 * @file
 * API functions for Springboard data warehouse.
 */

// Use the autoloaded Guzzle client and client exception handlers.
use GuzzleHttp\Client as guzzle_client;
use GuzzleHttp\Exception\ClientException as guzzle_client_exception;

Class GuzzleResponseExceptionMarshall {
  function __construct() {
    $this->statusCode = 500;
  }

  /**
   * Get the generic status code, or the one set with the setter method.
   * @return int
   */
  public function getStatusCode() {
    return $this->statusCode;
  }

  /**
   * Setter method to set the status code to be returned by the class.
   * @param $code
   * @return int
   */
  public function setStatusCode($code) {
    $this->statusCode = $code;

    return $this->statusCode;
  }
}

/**
 * Returns a new instance of Guzzle Http client.
 *
 * @return \GuzzleHttp\Client $guzzle
 *   Return an instance of the Guzzle client.
 */
function springboard_dw_api_client() {

  // Include the Composer autoload file.
  include_once "sites/all/libraries/springboard_composer/vendor/autoload.php";

  // Load Guzzle client.
  $guzzle = new guzzle_client(['http_errors' => FALSE, 'verify' => FALSE]);

  // Return an instance of the client.
  return $guzzle;
}

/**
 * Returns the endpoint for the data warehouse receiver app.
 *
 * @param string $endpoint_route
 *   The endpoint route to use in constructing the full URL for the api call.
 *
 * @return string
 *   The full api endpoint.
 */
function springboard_dw_api_endpoint($endpoint_route) {
  $api_endpoint = variable_get('springboard_dw_api_endpoint', NULL);

  return $api_endpoint . '/' . ltrim($endpoint_route, '/');
}

/**
 * Removes the queue type, adds auth and preps api call.
 *
 * @param array $item
 *   An array of values.
 *
 * @return array $item
 *   An array of values with authentication and client identification
 *   parameters added.
 */
function springboard_dw_api_prep_call($item) {
  // Remove the queue type from the item.
  unset($item['queue_type']);

  // Unset the queue item update flag from the item if it is present.
  if(isset($item['queue_item_update'])) {
    unset($item['queue_item_update']);
  }

  // Add the authentication token and client id.
  $item['authenticationToken'] = variable_get('springboard_dw_authentication_token', NULL);

  return $item;
}

/**
 * Make an api call to the warehouse providing endpoint and form params.
 *
 * @param string $endpoint_route
 *   The endpoint route used to construct the full URI for the API call.
 * @param array $params
 *   The parameters used in the API call added to the URI for debugging
 *   purposes.
 * @param string $method
 *   The HTTP verb/method to use for the API call (defaults to POST).
 *
 * @return mixed|\Psr\Http\Message\ResponseInterface
 *   Return the api response
 */
function springboard_dw_api_call($endpoint_route, $params, $method = 'POST') {
  // Define the endpoint.
  $endpoint = springboard_dw_api_endpoint($endpoint_route);

  // Instantiate an API client instance.
  $api_client = springboard_dw_api_client();

  // Clean up the item and add authentication to the form params.
  $params = springboard_dw_api_prep_call($params);

  // Guzzle requires parameters to be labeled differently depending on the
  // HTTP verb.
  if ($method == 'GET') {
    $request_params = array('query' => $params);
  }
  else {
    $request_params = array('form_params' => $params);
  }

  // Set a reasonable timeout for the request.
  $request_params['timeout'] = 30;

  // Attempt the Guzzle API request and capture any exceptions encountered.
  try {
    $api_response = $api_client->request(
      $method,
      $endpoint,
      $request_params
    );

    // Setup an array of the API call details prepped for logging.
    $api_call['endpoint'] = $endpoint;
    $api_call['method'] = $method;
    $api_call['params'] = $params;
    $api_call['response'] = $api_response->getBody()->getContents();
    $api_call['responseCode'] = $api_response->getStatusCode();
    $api_call['fullUrl'] = $endpoint . '?' . http_build_query(springboard_dw_api_prep_call
      ($api_call['params']));

    $watchdog_string = "<pre>Warehouse API call: \n" . print_r($api_call, TRUE) . "</pre>";

    // Log the full API call details to watchdog if logging is enabled.
    springboard_dw_watchdog_log($watchdog_string);

    return $api_response;
  }
  catch (guzzle_client_exception $e) {
    // Setup an array of the API call details prepped for logging the failure.
    $api_call['endpoint'] = $endpoint;
    $api_call['method'] = $method;
    $api_call['params'] = $params;
    $api_call['responseCode'] = $e->hasResponse() ? $e->getResponse(): 500;
    $api_call['exception'] = $e->getMessage();
    $api_call['fullUrl'] = $endpoint . '?' . http_build_query(springboard_dw_api_prep_call
      ($api_call['params']));

    // Log the full API call failure details.
    $watchdog_string = "<pre>Springboard DW API Client Exception:\n". print_r($api_call, TRUE) . '</pre>';
    watchdog('data_warehouse', $watchdog_string, WATCHDOG_ERROR);

    // Create a non-200 response to indicate there was an exception on the
    // server.
    $api_response = new GuzzleResponseExceptionMarshall;

    // If the exception has a response code status use that.
    if ($e->hasResponse()) {
      $exceptionStatusCode = $e->getResponse();

      $api_response->setStatusCode($exceptionStatusCode);
    }

    // Return the API response.
    return $api_response;
  }
}

/**
 * Mark an item in Drupal as being warehoused.
 *
 * @param string $type
 *   The type or identifier for what kind of item we are tracking.
 * @param int $identifier
 *   The unique identifier for the item (typically a Drupal ID unless it is a
 *   message item in which case it is a MongoId string).
 *
 * @throws \Exception
 */
function springboard_dw_track_item_warehouse_success($type, $identifier) {
  // Insert the user account into the Drupal data warehouse table.
  db_insert('springboard_data_warehouse')->fields(
    array(
      'type'      => $type,
      'drupal_id' => $identifier,
      'created'   => time(),
    )
  )->execute();
}
