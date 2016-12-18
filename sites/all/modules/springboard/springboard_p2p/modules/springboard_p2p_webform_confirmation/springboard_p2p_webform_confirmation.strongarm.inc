<?php
/**
 * @file
 * springboard_p2p_webform_confirmation.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function springboard_p2p_webform_confirmation_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pm_existing_pages_disabled_p2p_webform_confirmation';
  $strongarm->value = FALSE;
  $export['pm_existing_pages_disabled_p2p_webform_confirmation'] = $strongarm;

  return $export;
}
