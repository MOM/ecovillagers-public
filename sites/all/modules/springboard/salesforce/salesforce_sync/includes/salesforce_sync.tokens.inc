<?php

/**
 * @file
 * Contains SalesforceSyncTokenScanner
 */

/**
 * Functionality for finding and replacing Salesforce relationship tokens.
 */
class SalesforceSyncTokenScanner {

  /**
   * An array of processed Salesforce items.
   *
   * @var array
   */
  protected $tokenValueCache;

  /**
   * Setter for tokenValueCache property.
   *
   * @param array $token_value_cache
   *   An array of Salesforce ids to use for token replacement.
   */
  public function setTokenValueCache($token_value_cache) {
    $this->tokenValueCache = $token_value_cache;
  }

  /**
   * Construct the object.
   *
   * @param array $token_value_cache
   *   An array of Salesforce ids to use for token replacement.
   */
  public function __construct($token_value_cache) {
    $this->tokenValueCache = $token_value_cache;
  }

  /**
   * Replaces tokens in a batch of Salesforce objects.
   *
   * @param array $batch
   *   A populated queue processor batch.
   */
  public function batchTokenReplace(&$batch) {
    if (!isset($batch['sobjects'])) {
      // Some batches do not have sobjects, such as delete.
      return;
    }
    foreach ($batch['sobjects'] as &$object) {
      $this->objectTokenReplace($object);
    }
  }

  /**
   * Replaces tokens in a single Salesforce object.
   *
   * @param object $object
   *   The object record whose fields to scan for tokens.
   */
  public function objectTokenReplace(&$object) {
    // See if the object has any tokens in it.
    $tokens = $this->findTokens($object);
    $object->tokens_replaced = TRUE;
    // If we've got tokens, replace them.
    if (!empty($tokens)) {
      // Invoke hook_salesforce_sync_tokens_alter() so that other modules
      // can change the tokens before replacement.
      drupal_alter('salesforce_sync_tokens', $tokens, $object);
      $this->tokenReplace($object, $tokens);
    }
  }

  /**
   * Replace each tokenized field SFID from tokenValueCache or database.
   *
   * @param object $object
   *   The object whose tokenized field values need to be replaced.
   * @param array $tokens
   *   An array of tokenized fields.
   */
  public function tokenReplace(&$object, $tokens) {
    foreach ($tokens as $field => $token) {
      // If the token cache is populated, attempt to get value from cache.
      if ($this->cachePopulated() && $value = $this->getTokenValueFromCache($token)) {
        $object->fields[$field] = $value;
      }
      elseif ($value = $this->getTokenValueFromDB($token)) {
        $object->fields[$field] = $value;
      }
      else {
        // What do we do here? No token found, bummer! This will cause the
        // object to fail.
        $object->fields[$field] = $token;
        $object->tokens_replaced = FALSE;
      }
    }
  }

  /**
   * Replaces a token with its value from a cache of values.
   *
   * @param string $token
   *   The token to replace.
   */
  public function getTokenValueFromCache($token) {
    // Split token into something useful for cache lookup.
    $token = $this->splitToken($token);
    // TODO: Optimize this! isset() perhaps?
    if (array_key_exists($token['sf_type'], $this->tokenValueCache)
       && array_key_exists($token['drupal_type'], $this->tokenValueCache[$token['sf_type']])
       && array_key_exists($token['drupal_id'], $this->tokenValueCache[$token['sf_type']][$token['drupal_type']])) {

      return $this->tokenValueCache[$token['sf_type']][$token['drupal_type']][$token['drupal_id']];
    }

    return FALSE;
  }

  /**
   * Replaces a token with its value from the database.
   *
   * @param string $token
   *   The token to replace.
   */
  public function getTokenValueFromDB($token) {
    // Split token into something useful for database lookup.
    $token = $this->splitToken($token);

    // Look for Id in object mapping db2_tables(connection)
    $sfid = db_select('salesforce_sync_map', 'm')
      ->fields('m', array('sfid'))
      ->condition('object_type', $token['sf_type'])
      ->condition('delta', $token['drupal_type'])
      ->condition('drupal_id', $token['drupal_id'])
      ->execute()
      ->fetchField();

    return !empty($sfid) ? $sfid : FALSE;
  }

  /**
   * Splits a token into it's 3 respective parts.
   *
   * @param string $token
   *   The token to split.
   */
  public function splitToken($token) {
    // Remove [ and ]
    $token = substr($token, 1, -1);
    $token_pieces = explode(':', $token);

    // Convert to something more friendly.
    return array(
      'sf_type' => $token_pieces[0],
      'drupal_type' => $token_pieces[1],
      'drupal_id' => $token_pieces[2],
    );
  }

  /**
   * Searches for tokens in an sobject's fields array.
   *
   * @param object $object
   *   A Salesforce sobject.
   */
  public function findTokens($object) {
    return preg_grep('/
      \[             # [ - pattern start
      ([^\s\[\]:]*)  # match salesforce type not containing whitespace : [ or ]
      :              # : - separator
      ([^\s\[\]:]*)  # match module not containing whitespace : [ or ]
      :              # : - separator
      ([^\s\[\]:]*)   # match module not containing whitespace : [ or ]
      \]             # ] - pattern end
      /x', $object->fields);
  }

  /**
   * Adds an item to the token value cache.
   *
   * @param object $item
   *   The item to add to the cache.
   * @param string $sfid
   *   Salesforce ID of the item.
   */
  public function addItemToTokenCache($item, $sfid) {
    $this->tokenValueCache[$item->object_type][$item->delta][$item->drupal_id] = $sfid;
  }

  /**
   * Check if the cache is populated.
   */
  public function cachePopulated() {
    return !empty($this->tokenValueCache);
  }

}
