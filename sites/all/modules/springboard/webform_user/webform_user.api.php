<?php

/**
 * @file
 * Sample hooks demonstrating usage in Webform User.
 */

/**
 * Respond to a Webform submission being assigned to user.
 *
 * @param $node
 *   The Webform node on which this submission was made.
 * @param $submission
 *   The Webform submission that has just been assigned to a user.
 */
function hook_webform_user_assign_submission($node, $submission) {
  // Update a record in a 3rd-party module table when a submission is updated.
  db_update('mymodule_table')
    ->fields(array(
      'foo' => 'foo_data',
    ))
    ->condition('nid', $node->nid)
    ->condition('sid', $submission->sid)
    ->execute();
}
