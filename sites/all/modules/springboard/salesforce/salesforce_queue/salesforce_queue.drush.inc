<?php

/**
 * @file
 * Drush commands for the Salesforce queue module.
 */


/**
 * Implements hook_drush_help().
 */
function salesforce_queue_drush_help($command) {
  switch ($command) {
    case 'drush:salesforce-queue-process':
      return dt('Processes the Salesforce queue.');
  }
}

/**
 * Implements hook_drush_command().
 */
function salesforce_queue_drush_command() {
  $items = array();
  $items['salesforce-queue-process'] = array(
    'description' => dt('Processes the Salesforce queue.'),
    'arguments' => array(
      'queue' => dt('Name of the queue to process'),
    ),
    'examples' => array(
      'Standard example' => 'drush salesforce-queue-process',
      'Argument example' => 'drush salesforce-queue-process all',
    ),
    'aliases' => array('sfqp'),
  );
  return $items;
}

/**
 * Callback function for drush salesforce-queue-process.
 *
 * Processes the specified Salesforce queue.
 *
 * @param string $queue
 *   An optional queue to process.
 */
function drush_salesforce_queue_process($queue = 'salesforce_queue') {
  if (isset($queue)) {
    drush_print('Processing ' . $queue);
  }

  $queue = salesforce_queue_load();
  $processor = salesforce_queue_load_processor($queue);
  $processor->process();

  drush_print(print_r($processor->getNewSfRecords(), TRUE));

  // Log to the command line with an OK status.
  drush_log('Running salesforce-queue-process', 'ok');
}
