<?php

/**
 * @file
 * Drush commands for the Springboard data warehouse module.
 */

/**
 * Implements hook_drush_help().
 */
function springboard_dw_drush_help($command) {

  switch ($command) {
    case 'drush:springboard-dw-export-queue-process':
      return dt('Processes the Springboard data warehouse export queue.');
    case 'drush:springboard-dw-csv-reports-queue-process':
      return dt('Processes the Springboard data warehouse CSV reports export
      queue.');
  }
}

/**
 * Implements hook_drush_command().
 */
function springboard_dw_drush_command() {

  $items = array();
  $items['springboard-dw-export-queue-process'] = array(
    'description' => dt('Processes the Springboard data warehouse export queue.'),
    'examples' => array(
      'Standard example' => 'springboard-dw-export-queue-process',
    ),
    'aliases' => array('sb-dw-export'),
  );

  $items['springboard-dw-csv-reports-queue-process'] = array(
    'description' => dt('Processes the Springboard data warehouse CSV reports export
      queue.'),
    'examples'    => array(
      'Standard example' => 'springboard-dw-csv-reports-queue-process',
    ),
    'aliases'     => array('sb-dw-csv-export'),
  );

  return $items;
}

/**
 * Callback function for drush springboard-dw-export-queue-process.
 *
 * Processes the Springboard data warehouse export queue.
 */
function drush_springboard_dw_export_queue_process() {
  require_once "sites/all/libraries/springboard_composer/vendor/autoload.php";

  // If the data warehouse config is not set, don't try to process the queue.
  if (!variable_get('springboard_dw_api_endpoint', FALSE) || !variable_get('springboard_dw_api_endpoint', FALSE)) {
    drush_print('Could not process the data warehouse queue because config has not been set.');
    watchdog('data_warehouse', 'Could not process the data warehouse queue because config has not been set.', WATCHDOG_ERROR);
  }
  else {
    // Provide CLI feedback.
    drush_log('Processing the Springboard data warehouse export queue.', 'ok');

    // Process the items in the queue.
    $counter = springboard_dw_process_queue();
    if (!is_null($counter)) {
      drush_log(dt('Processed !counter items in Springboard data warehouse export queue.', array('!counter' => $counter)), 'ok');
    }

    // Log to the command line with an OK status.
    drush_log('Finished processing the Springboard data warehouse export queue.', 'ok');
  }
}

/**
 * Callback function for drush springboard-dw-export-queue-process.
 *
 * Processes the Springboard data warehouse export queue.
 */
function drush_springboard_dw_csv_reports_queue_process() {

  // Process the items in the CSV export queue.
  springboard_dw_process_csv_export_queue();
}
