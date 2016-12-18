<?php

/**
 * @file
 *  Runs webform_goals cron via drush.
 */

/**
 * Implementation of hook_drush_command().
 */
function webform_goals_drush_command() {
  $items['webform-goals-cron'] = array(
    'description' => 'Calculates webform goals progress and rebuilds widget files.',
    'arguments' => array(
    ),
    'options' => array(
    ),
  );

  return $items;
}

/**
 * Command callback. Runs webform goals cron.
 */
function drush_webform_goals_cron() {
  module_load_include('inc', 'webform_goals', 'includes/webform_goals.widget');
  drush_print(webform_goals_rebuild_widgets());
}
