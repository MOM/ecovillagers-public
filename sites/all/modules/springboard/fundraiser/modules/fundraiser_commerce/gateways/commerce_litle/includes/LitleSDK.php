<?php
/**
 * @file
 * Class to connect the Litle SDK library to Drupal Commerce.
 */

class LitleSDK {

  /**
   * @var null|\litle\sdk\LitleOnlineRequest
   */
  protected $request = NULL;

  /**
   * Loads the Litle SDK library and initializes a Request object.
   *
   * If the SDK can't be loaded, watchdog the error and throw an exception.
   *
   * @throws RuntimeException
   *   If the Litle SDK can't be loaded.
   */
  public function __construct() {
    $library = libraries_load('litle');

    if (!empty($library['loaded'])) {
      // Initialize an internal Request object.
      $this->newRequest();
      return;
    }

    // Couldn't load the library. Try to get some info and watchdog it.
    $replacements = array(
      '@error' => '',
      '@error_message' => '',
    );

    if (isset($library['error'])) {
      $replacements['@error'] = $library['error'];
    }
    if (isset($library['error message'])) {
      $replacements['@error_message'] = $library['error message'];
    }

    watchdog('Commerce Litle', 'Litle library not found! @error @error_message', $replacements, WATCHDOG_ALERT);

    throw new RuntimeException('Cannot load the Litle SDK');
  }

  /**
   * Initialize the Request object.
   */
  public function newRequest() {
    $this->request = new \litle\sdk\LitleOnlineRequest();
  }

  /**
   * Parses the response XML as a DomDocument.
   *
   * This method wraps the XmlParser static call in the SDK.
   *
   * @param string $xml
   *   The XML, usually from a response.
   *
   * @return DOMDocument
   *   The response XML loaded in as a DomDocument.
   */
  public function domParser($xml) {
    return \litle\sdk\XmlParser::domParser($xml);
  }

  /**
   * Get an element value from the response.
   *
   * This method wraps the XmlParser static call in the SDK.
   *
   * @param DomDocument $dom
   *   The response.
   * @param string $elementName
   *   The element/tag to match.
   *
   * @return string
   *   The value of the last matching element in the document.
   */
  public function getNode($dom, $elementName) {
    return \litle\sdk\XmlParser::getNode($dom, $elementName);
  }

  /**
   * Gets an attribute from the first matched element in a DomDocument.
   *
   * This method wraps the XmlParser static call in the SDK.
   *
   * @param DomDocument $dom
   *   The response.
   * @param string $elementName
   *   The element/tag to match.
   * @param string $attributeName
   *   The name of the attribute to get.
   *
   * @return string
   *   The value of the attribute.
   */
  public function getAttribute($dom, $elementName, $attributeName) {
    return \litle\sdk\XmlParser::getAttribute($dom, $elementName, $attributeName);
  }

  /**
   * Get the entire response as a string.
   *
   * This method wraps the XmlParser static call in the SDK.
   *
   * @param DomDocument $dom
   *   The response.
   *
   * @return bool|string
   *   The full response as a string of XML, or FALSE.
   */
  public function getDomDocumentAsString($dom) {
    return \litle\sdk\XmlParser::getDomDocumentAsString($dom);
  }

  /**
   * Make an authorization API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   Request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function authorizationRequest($hash_in) {
    return $this->request->authorizationRequest($hash_in);
  }

  /**
   * Make a sale API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function saleRequest($hash_in) {
    return $this->request->saleRequest($hash_in);
  }

  /**
   * Make an authReversal request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function authReversalRequest($hash_in) {
    return $this->request->authReversalRequest($hash_in);
  }

  /**
   * Make a credit API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function creditRequest($hash_in) {
    return $this->request->creditRequest($hash_in);
  }

  /**
   * Make a registerToken API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function registerTokenRequest($hash_in) {
    return $this->request->registerTokenRequest($hash_in);
  }

  /**
   * Make a forceCapture API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function forceCaptureRequest($hash_in) {
    return $this->request->forceCaptureRequest($hash_in);
  }

  /**
   * Make a capture API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function captureRequest($hash_in) {
    return $this->request->captureRequest($hash_in);
  }

  /**
   * Make a captureGivenAuth API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function captureGivenAuthRequest($hash_in) {
    return $this->request->captureGivenAuthRequest($hash_in);
  }

  /**
   * Make an echeckRedeposit API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function echeckRedepositRequest($hash_in) {
    return $this->request->echeckRedepositRequest($hash_in);
  }

  /**
   * Make an echeckSale API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function echeckSaleRequest($hash_in) {
    return $this->request->echeckSaleRequest($hash_in);
  }

  /**
   * Make an echeckCredit API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function echeckCreditRequest($hash_in) {
    return $this->request->echeckCreditRequest($hash_in);
  }

  /**
   * Make an echeckVerification request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function echeckVerificationRequest($hash_in) {
    return $this->request->echeckVerificationRequest($hash_in);
  }

  /**
   * Make a void API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function voidRequest($hash_in) {
    return $this->request->voidRequest($hash_in);
  }

  /**
   * Make an echeckVoid API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function echeckVoidRequest($hash_in) {
    return $this->request->echeckVoidRequest($hash_in);
  }

  /**
   * Make a depositReversal API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function depositReversalRequest($hash_in) {
    return $this->request->depositReversalRequest($hash_in);
  }

  /**
   * Make a refundReversal API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function refundReversalRequest($hash_in) {
    return $this->request->refundReversalRequest($hash_in);
  }

  /**
   * Make an activateReversal API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function activateReversalRequest($hash_in) {
    return $this->request->activateReversalRequest($hash_in);
  }

  /**
   * Make a deactivateReversal API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function deactivateReversalRequest($hash_in) {
    return $this->request->deactivateReversalRequest($hash_in);
  }

  /**
   * Make a loadReversal API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function loadReversalRequest($hash_in) {
    return $this->request->loadReversalRequest($hash_in);
  }

  /**
   * Make an unloadReversal API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function unloadReversalRequest($hash_in) {
    return $this->request->unloadReversalRequest($hash_in);
  }

  /**
   * Make an updateCardValidationNumOnToken API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function updateCardValidationNumOnToken($hash_in) {
    return $this->request->updateCardValidationNumOnToken($hash_in);
  }

  /**
   * Make an updateSubscription API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function updateSubscription($hash_in) {
    return $this->request->updateSubscription($hash_in);
  }

  /**
   * Make a cancelSubscription API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function cancelSubscription($hash_in) {
    return $this->request->cancelSubscription($hash_in);
  }

  /**
   * Make an updatePlan API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function updatePlan($hash_in) {
    return $this->request->updatePlan($hash_in);
  }

  /**
   * Make a createPlan API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function createPlan($hash_in) {
    return $this->request->createPlan($hash_in);
  }

  /**
   * Make an activate API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function activate($hash_in) {
    return $this->request->activate($hash_in);
  }

  /**
   * Make a deactivate API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function deactivate($hash_in) {
    return $this->request->deactivate($hash_in);
  }

  /**
   * Make a load API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function load($hash_in) {
    return $this->request->load($hash_in);
  }

  /**
   * Make an unload API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function unload($hash_in) {
    return $this->request->unload($hash_in);
  }

  /**
   * Make a balanceInquiery API request.
   *
   * This method wraps the LitleOnlineRequest.
   *
   * @param array $hash_in
   *   The request data.
   *
   * @return DOMDocument|SimpleXMLElement
   *   The response.
   */
  public function balanceInquiry($hash_in) {
    return $this->request->balanceInquiry($hash_in);
  }

}
