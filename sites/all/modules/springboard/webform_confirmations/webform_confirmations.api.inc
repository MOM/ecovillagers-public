<?php

/**
 * @file
 * API example code for module developers.
 */

/**
 * Alter the webform confirmation message.
 *
 * Alter the webform confirmation before tokens are replaced or its run through
 * text formatting.
 *
 * @param string $confirmation_message
 *   The webform confirmation message.
 * @param array $variables
 *   Array of variables, including the node and donation for fundraiser form.
 */
function hook_webform_confirmations_confirmation_message_alter(&$confirmation_message, array $variables) {
  // Wrap the confirmation message in additional div.
  $confirmation_message = '<div>' . $confirmation_message . '</div>';
}
