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
  'title' => t('Check for P2P donation thank you page'),
  // Plugin description.
  'description' => t('Access control that tests if the donation thank you page belongs to P2P'),
  // Without required context plugin will now be shown in Panels UI.
  'required context' => new ctools_context_required(t('Node'), 'node'),
  // Function which will allow or restrict access.
  'callback' => 'springboard_p2p_donation_thank_you_ctools_access_check',
  // Plugin settings form.
  'settings form' => 'springboard_p2p_donation_thank_you_ctools_settings',
  'settings form submit' => 'springboard_p2p_donation_thank_you_ctools_settings_submit',
  // Provides a summary descriptions depends on settings selected.
  'summary' => 'springboard_p2p_donation_thank_you_ctools_summary',
);

/**
 * Custom callback defined by 'callback' in the $plugin array.
 *
 * Callback, Check if this is a p2p donation form or not.
 */
function springboard_p2p_donation_thank_you_ctools_access_check($conf, $context) {

// Query the url string to see if it belongs to P2P.
  if (!empty($_GET['p2p_pcid']) && (arg(2) == 'done')) {
    return TRUE;
  }
  return FALSE;
}

/**
 * Provide a summary.
 */
function springboard_p2p_donation_thank_you_ctools_summary($conf, $context) {

  // Pretty label for the main selection rules page.
  return t('Access Control that tests if the donation thank you page is a P2P thank you page.');
}

/**
 * Settings form for the 'node_field_populated' access plugin.
 */
function springboard_p2p_donation_thank_you_ctools_settings($form, &$form_state, $conf) {

  // Add some default text with a P2P message.
  $form['#prefix'] = '<h2 style="margin: 0 0 20px 0;">' . t('This plugin has no settings, it simply tests for true or false on a p2p donation thank you page.') . '</h2>';

  return $form;

}
