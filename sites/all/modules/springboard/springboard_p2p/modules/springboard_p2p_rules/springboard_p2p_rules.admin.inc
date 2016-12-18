<?php

/**
 * @file
 * Rules admin page for P2P.
 */

/**
 * Builds the P2P Rules settings page using the Rules UI.
 */
function springboard_p2p_rules_admin_page() {
  $ui = rules_ui();;
  $options = array(
    'show plugin' => FALSE,
    'base path' => 'admin/springboard/p2p/rules',
  );

  // Add the table for enabled P2P rules.
  $content['enabled']['title']['#markup'] = '<h3>' . t('Enabled P2P rules') . '</h3>';

  $conditions = array(
    'event' => array(
      'springboard_p2p_user_register_no_campaign',
      'springboard_p2p_user_register_private_campaign',
      'springboard_p2p_user_register_public_campaign',
      'springboard_p2p_user_requests_approval',
      'springboard_p2p_user_is_approved',
      'springboard_p2p_user_is_rejected',
      'springboard_p2p_user_requests_password_reset',
      'springboard_p2p_user_creates_campaign',
    ),
    'plugin' => 'reaction rule',
    'active' => TRUE,
  );

  $content['enabled']['rules'] = $ui->overviewTable($conditions, $options);
  $content['enabled']['rules']['#empty'] = t('There are no active P2P rules.');

  // Add the table for disabled Springboard P2P rules.
  $content['disabled']['title']['#markup'] = '<h3>' . t('Disabled P2P rules') . '</h3>';

  $conditions['active'] = FALSE;
  $content['disabled']['rules'] = $ui->overviewTable($conditions, $options);
  $content['disabled']['rules']['#empty'] = t('There are no disabled P2P rules.');

  // Store the function name in the content array to make it easy to alter the
  // contents of this page.
  $content['#page_callback'] = 'springboard_p2p_rules_admin_page';

  return $content;
}
