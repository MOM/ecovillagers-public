<?php

/**
 * @file
 * Rules integration with Springboard P2P.
 */

/**
 * Implements hook_rules_event_info().
 */
function springboard_p2p_rules_rules_event_info() {
  $defaults = array(
    'group' => t('Springboard P2P'),
    'module' => 'springboard_p2p_rules',
    'access callback' => 'springboard_p2p_rules_integration_access',
  );

  return array(
    'springboard_p2p_user_register_no_campaign' => $defaults + array(
      'label' => t('After a user registers for P2P (no campaign)'),
      'variables' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('User registering'),
        ),
        'dashboard_url' => array(
          'type' => 'uri',
          'label' => t('User P2P dashboard URL'),
          'description' => t("The URL to the user's list of personal campaigns."),
        ),
      ),
    ),
    'springboard_p2p_user_register_private_campaign' => $defaults + array(
      'label' => t('After a user registers for P2P (private campaign)'),
      'variables' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('User registering'),
        ),
        'dashboard_url' => array(
          'type' => 'uri',
          'label' => t('User P2P dashboard URL'),
          'description' => t("The URL to the user's list of personal campaigns."),
        ),
        'campaign' => array(
          'type' => 'node',
          'bundle' => 'p2p_campaign',
          'label' => t('Campaign node'),
          'optional' => TRUE,
        ),
      ),
    ),
    'springboard_p2p_user_register_public_campaign' => $defaults + array(
      'label' => t('After a user registers for P2P (public campaign)'),
      'variables' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('User registering'),
        ),
        'dashboard_url' => array(
          'type' => 'uri',
          'label' => t('User P2P dashboard URL'),
          'description' => t("The URL to the user's list of personal campaigns."),
        ),
        'campaign' => array(
          'type' => 'node',
          'bundle' => 'p2p_campaign',
          'label' => t('Campaign node'),
          'optional' => TRUE,
        ),
        'create_personal_campaign_url' => array(
          'type' => 'uri',
          'label' => t('Create personal campaign URL'),
          'description' => t('The URL to the personal campaign creation page.'),
        ),
      ),
    ),
    'springboard_p2p_user_requests_approval' => $defaults + array(
      'label' => t('After a user requests approval for a private campaign (excludes registration)'),
      'variables' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('User requesting approval'),
        ),
        'dashboard_url' => array(
          'type' => 'uri',
          'label' => t('User P2P dashboard URL'),
          'description' => t("The URL to the user's list of personal campaigns."),
        ),
        'campaign' => array(
          'type' => 'node',
          'bundle' => 'p2p_campaign',
          'label' => t('Private campaign node'),
        ),
      ),
    ),
    'springboard_p2p_user_is_approved' => $defaults + array(
      'label' => t('After a user is approved for a private campaign'),
      'variables' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('Approved user'),
        ),
        'dashboard_url' => array(
          'type' => 'uri',
          'label' => t('User P2P dashboard URL'),
          'description' => t("The URL to the user's list of personal campaigns."),
        ),
        'campaign' => array(
          'type' => 'node',
          'bundle' => 'p2p_campaign',
          'label' => t('Private campaign node'),
        ),
        'create_personal_campaign_url' => array(
          'type' => 'uri',
          'label' => t('Create personal campaign URL'),
          'description' => t('The URL to the personal campaign creation page for the campaign.'),
        ),
      ),
    ),
    'springboard_p2p_user_is_rejected' => $defaults + array(
      'label' => t('After a user is rejected for a private campaign'),
      'variables' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('Rejected user'),
        ),
        'dashboard_url' => array(
          'type' => 'uri',
          'label' => t('User P2P dashboard URL'),
          'description' => t("The URL to the user's list of personal campaigns."),
        ),
        'campaign' => array(
          'type' => 'node',
          'bundle' => 'p2p_campaign',
          'label' => t('Private campaign node'),
        ),
      ),
    ),
    'springboard_p2p_user_requests_password_reset' => $defaults + array(
      'label' => t('After a user requests a password reset via the P2P UI.'),
      'variables' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('User requesting a password reset'),
        ),
        'reset_url' => array(
          'type' => 'uri',
          'label' => t('Password reset URL'),
          'description' => t("The URL to the P2P password reset page."),
        ),
      ),
    ),
    'springboard_p2p_user_creates_campaign' => $defaults + array(
      'label' => t("After a user creates a personal campaign (excludes the user's first personal campaign)."),
      'variables' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('User creating the campaign'),
        ),
        'dashboard_url' => array(
          'type' => 'uri',
          'label' => t('User P2P dashboard URL'),
          'description' => t("The URL to the user's list of personal campaigns."),
        ),
        'personal_campaign' => array(
          'type' => 'node',
          'bundle' => 'p2p_personal_campaign',
          'label' => t('Personal campaign node that was just created.'),
        ),
      ),
    ),
  );
}

/**
 * P2P integration access callback.
 */
function springboard_p2p_rules_integration_access($type, $name) {
  if ($type == 'event') {
    return entity_access('view', 'user') && entity_access('view', 'node');
  }

  return FALSE;
}
