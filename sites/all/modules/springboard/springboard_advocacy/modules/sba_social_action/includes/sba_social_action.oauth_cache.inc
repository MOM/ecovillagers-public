<?php

/**
 * @file
 * Helper functions for cache expiration.
 *
 * Save encrypted oauth tokens and secrets to db cache instead of in
 * session, so that they may be easily expired.
 *
 * Modeled on http://www.drupal.org/projects/session_cache
 */

/**
 * Wrapper around cache_set.
 *
 * @param $bin
 */
function sba_social_action_cache_set($bin, $data) {
  $sid = sba_social_action_get_sid();
  if ($data == NULL) {
    cache_clear_all("$bin:$sid", 'cache_sba_social_action');
  }
  else {
    cache_set("$bin:$sid", $data, 'cache_sba_social_action', sba_social_action_expiration_time());
  }
}

/**
 * Wrapper around cache_get.
 *
 * @param $bin
 * @return null
 */
function sba_social_action_cache_get($bin) {
  $sid = sba_social_action_get_sid();
  $cache = cache_get("$bin:$sid", 'cache_sba_social_action');
  if (is_object($cache) && !empty($cache->data)) {
    if (time() < $cache->expire) {
      return $cache->data;
    }
  }
  return NULL;
}

/**
 * The cache expiration, in hours.
 *
 * @return int
 */
function sba_social_action_expiration_time() {
  return REQUEST_TIME + 60 * 60 * variable_get('sba_social_action_cache_expire_period', '1');
}

/**
 * Set and Get a cookie with theOauth Cache ID.
 *
 * @return string
 */
function sba_social_action_get_sid() {
  if (empty($_COOKIE['Drupal_social_action_sid'])) {
    $sid = drupal_substr(session_id(), 0, 12);
    global $cookie_domain;
    $cdom = ($cookie_domain == '.localhost') ? ini_get('session.cookie_domain') : $cookie_domain;
    setcookie('Drupal.sba_social_action.sid', $sid, sba_social_action_expiration_time(), '/', $cdom, NULL, TRUE);
    $_COOKIE['Drupal_social_action_sid'] = $sid;
  }
  else {
    $sid = $_COOKIE['Drupal_social_action_sid'];
  }
  return $sid;
}

/**
 * Implements hook_cron().
 *
 * Delete any oauth caches that are an hour past their default expiration
 */
function sba_social_action_cron_expire_sessions() {
  db_delete('cache_sba_social_action')->condition('expire', time() - (60 * 60), '<')->execute();
}
