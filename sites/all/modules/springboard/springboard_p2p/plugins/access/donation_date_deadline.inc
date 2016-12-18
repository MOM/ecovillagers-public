<?php

/**
 * @file
 * Ctools access plugin for checking if a node field has been populated
 */

/**
 * Plugins are described by creating a $plugin array which will
 * be used by the system that includes the file.
 */

$plugin = array(

  // Plugin user-friendly name.
  'title' => t('Check for P2P personal campaign date expiry.'),
  // Plugin description.
  'description' => t('Access control that tests for P2P personal campaign date expiry.'),
  // Without required context plugin will now be shown in Panels UI.
  'required context' => new ctools_context_required(t('Node'), 'node'),
  // Function which will allow or restrict access.
  'callback' => 'springboard_p2p_donation_date_deadline_ctools_access_check',
  // Plugin settings form.
  'settings form' => 'springboard_p2p_donation_date_deadline_ctools_settings',
  'settings form submit' => 'springboard_p2p_donation_date_deadline_ctools_settings_submit',
  // Provides a summary descriptions depends on settings selected.
  'summary' => 'springboard_p2p_donation_date_deadline_ctools_summary',
);

/**
 * Custom callback defined by 'callback' in the $plugin array.
 *
 * Callback, Check if the date on the p2p personal campaign has expired.
 */
function springboard_p2p_donation_date_deadline_ctools_access_check($conf, $context) {

  // Define the node.
  $node = menu_get_object();

  // Check if p2p_personal_campaign node.
  if ($node->type == 'p2p_personal_campaign') {

    // Pull in field_p2p_fundraising_deadline and check if it's a date that's expired already.
    $wrapper = entity_metadata_wrapper('node', $node);
    $value = $wrapper->field_p2p_fundraising_deadline->value();
    if (empty($value)) {
      return TRUE;
    }
    $end_date = date('Y-m-d', $value);
    // Make end date just before midnight.
    if (strtotime($end_date . '11:59:59pm') < mktime(0, 0, 0)) {

      return FALSE;
    }
    return TRUE;
  }

}

/**
 * Provide a summary.
 */
function springboard_p2p_donation_date_deadline_ctools_summary($conf, $context) {

  // Pretty label for the main selection rules page.
  return t('Access Control that tests if the donation date has passed');
}

/**
 * Settings form for the 'node_field_populated' access plugin.
 */
function springboard_p2p_donation_date_deadline_ctools_settings($form, &$form_state, $conf) {

  // Add some default text with a P2P message.
  $form['#prefix'] = '<h2 style="margin: 0 0 20px 0;">' . t('This plugin has no settings, it simply tests if a donation date has expired') . '</h2>';

  return $form;

}
