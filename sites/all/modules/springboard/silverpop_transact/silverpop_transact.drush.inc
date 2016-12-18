<?php
/**
 * @file
 * Defines drush commands.
 */

/**
 * Implements hook_drush_command().
 */
function silverpop_transact_drush_command() {

  $items['silpop-send-queued-messages'] = array(
    'description' => 'Submit queued xml messages to Silverpop Transact.',
    'aliases' => array('ssqm'),
  );
  $items['silpop-update-status-messages'] = array(
    'description' => 'Get status of sent messages from Silverpop Transact.',
    'aliases' => array('suls'),
  );

  return $items;
}

/**
 * Drush command callback for silpop-send-queued--messages.
 */
function drush_silverpop_transact_silpop_send_queued_messages() {
  $queue = DrupalQueue::get('silverpop_transact_queue_xml');

  while ($item = $queue->claimItem()) {
    drush_log(dt("Submitting silverpop message xml, item id: !item-id.",
        array('!item-id' => $item->item_id)), 'ok');
    try {
      silverpop_transact_process_cron_queue($item->data);
      $queue->deleteItem($item);
    }
    catch (Exception $e) {
      // In case of exception log it and leave the item in the queue
      // to be processed again later.
      watchdog_exception('silverpop_transact', $e);
    }
  }
  return TRUE;
}

/**
 * Drush command callback for silpop-update-status-message.
 */
function drush_silverpop_transact_silpop_update_status_messages() {
  drush_log(dt("Updated the Silverpop Message field on !count log records.",
        array('!count' => silverpop_transact_cron_log_status_update())), 'ok');

}
