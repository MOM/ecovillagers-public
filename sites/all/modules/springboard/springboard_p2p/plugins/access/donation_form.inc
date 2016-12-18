<?php

/**
 * @file
 * Ctools access plugin for checking if we are on a p2p donation page.
 */

/**
 * Plugins are described by creating a $plugin array which will
 * be used by the system that includes the file.
 */
$plugin = array(

  // Plugin user-friendly name.
  'title' => t('Check for P2P Donation Form'),
  // Plugin description.
  'description' => t('Access Control that tests if the donation form is a P2P Donation form'),
  // Without required context plugin will now be shown in Panels UI.
  'required context' => new ctools_context_required(t('Node'), 'node'),
  // Function which will allow or restrict access.
  'callback' => 'springboard_p2p_donation_form_ctools_access_check',
  // Plugin settings form.
  'settings form' => 'springboard_p2p_donation_form_ctools_settings',
  'settings form submit' => 'springboard_p2p_donation_form_ctools_settings_submit',
  // Provides a summary descriptions depends on settings selected.
  'summary' => 'springboard_p2p_donation_form_ctools_summary',
);

/**
 * Custom callback defined by 'callback' in the $plugin array.
 *
 * Callback, Check if this is a p2p donation form or not.
 */
function springboard_p2p_donation_form_ctools_access_check($conf, $context) {
  // If for some unknown reason that $context isn't set,
  // we just want to be sure.
  if (empty($context) || empty($context->data)) {
    return FALSE;
  }

  // Define the node object.
  $node = menu_get_object();

  // Define the form types.
  $is_fundraiser_type = fundraiser_is_donation_type($node->type);
  $is_webform_user_type = _webform_user_is_webform_user_node_type($node->type);

  // Check to see if we are on a webform_user form or donation form.
  if ($is_fundraiser_type || $is_webform_user_type) {

    // Query the url string to see if it belongs to P2P.
    if (empty($_GET['p2p_pcid'])) {
      return FALSE;
    }
    return TRUE;
  }

}

/**
 * Provide a summary.
 */
function springboard_p2p_donation_form_ctools_summary($conf, $context) {

  // Pretty label for the main selection rules page.
  return t('Access Control that tests if the donation form is a P2P Donation form');
}

/**
 * Settings form for the 'node_field_populated' access plugin.
 */
function springboard_p2p_donation_form_ctools_settings($form, &$form_state, $conf) {

  // Add some default text with a P2P message.
  $form['#prefix'] = '<h2 style="margin: 0 0 20px 0;">' . t('This plugin has no settings, it simply tests for true or false on a p2p donation form.') . '</h2>';

  return $form;

}
