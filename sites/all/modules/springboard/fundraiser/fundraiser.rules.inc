<?php

/**
 * @file
 * Provides rules integration for fundraiser events.
 */

/**
 * Implements hook_rules_event_info().
 */
function fundraiser_rules_event_info() {
  $events = array(
    'fundraiser_gateway_test_mode_detected' => array(
      'label' => t('Test mode gateway configuration was detected on a live donation form'),
      'group' => t('Fundraiser'),
      'variables' => array(
        'gateway_node_id' => array('type' => 'text', 'label' => t('The the node ID of the donation form.')),
        'gateway_method_name' => array('type' => 'text', 'label' => t('The payment type.')),
        'gateway_id'=> array('type' => 'text', 'label' => t('The gateway ID.')),
        'gateway_status'=> array('type' => 'text', 'label' => t('The gateway status.')),
        'gateway_edit_link'=> array('type' => 'text', 'label' => t('The gateway edit link.')),
        ),
      ),
   );
  return $events;
}
