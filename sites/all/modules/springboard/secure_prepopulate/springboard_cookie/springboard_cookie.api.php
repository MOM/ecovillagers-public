<?php

/**
 * @file
 * This file contains no working PHP code; it exists to provide additional
 * documentation for doxygen as well as to document hooks in the standard
 * Drupal manner.
 */

/**
 * Invoked whenever a client is tagged with a user ID for the first time.
 * 
 * I.e., there wasn’t a uid in the cookie before, and now there is. In essence, this means we 
 * just learned who an anonymous user is. This will fire when an anonymous user logs into Drupal, 
 * and it will fire when an email is added via the "sbck" query string parameter to a cookie 
 * without an email.
 * 
 * @param array $new_cookie
 *   An array of name/value pairs, including the pre-existing client_id and the new uid and 
 *   associated user email.
 */
function hook_springboard_cookie_uid($new_cookie) {
  $client_id = $new_cookie['client_id'];
  $user = user_load($new_cookie['uid']);
  // Now we can look for saved instances of client_id and associate them with this user.
}
