<?php
/**
 * @file
 * Class to abstract some of the inconsistencies in user profile field names.
 *
 * Some user field names are named differently on different sites. The purpose
 * of this class is to provide a common interface to these differing field
 * names.
 */

class SpringboardUserWrapper {
  protected $account;

  /**
   * Load up the full user account from a uid or user object.
   *
   * @param int|object $account
   *   Either a user id, or an account object, such as the global $user.
   */
  public function __construct($account) {
    if (is_numeric($account)) {
      $this->account = user_load($account);
    }
    else {
      $this->account = user_load($account->uid);
    }
  }

  /**
   * Get the first name from the account.
   *
   * @return string
   *   The first name, or empty string.
   */
  public function getFirstName() {
    $keys = array('sbp_first_name', 'field_profile_first_name');
    return $this->getTextValue($keys);
  }

  /**
   * Get the last name from the account.
   *
   * @return string
   *   The last name, on empty string.
   */
  public function getLastName() {
    $keys = array('sbp_last_name', 'field_profile_last_name');
    return $this->getTextValue($keys);
  }

  /**
   * Get the value of the first key found in the account.
   *
   * @param array $keys
   *   An array of keys to search for.
   *
   * @return string
   *   The text vavlue or empty string.
   */
  private function getTextValue(array $keys = array()) {
    $key = $this->findKey($keys);

    if ($key && !empty($this->account->{$key})) {
      return $this->account->{$key}[$this->getLanguage()][0]['safe_value'];
    }

    return '';
  }

  /**
   * Search for a list of keys in the account and return the first one we find.
   *
   * @param array $keys
   *   An array of keys to search for, in order of preference.
   *
   * @return string|bool
   *   The name of the found key, or FALSE if it doesn't exist.
   */
  private function findKey(array $keys) {
    foreach ($keys as $key) {
      if (isset($this->account->$key)) {
        return $key;
      }
    }

    return FALSE;
  }

  /**
   * Get the account's language setting, or 'und' if it's empty.
   *
   * @return string
   *   The user language, or 'und'.
   */
  private function getLanguage() {
    if (!empty($this->account->language)) {
      return $this->account->language;
    }

    return 'und';
  }
}
