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
  'title' => t('Node: Field is populated'),
  'description' => t('Controls access by checking if the field has been populated with a value'),
  'callback' => 'springboard_p2p_node_field_populated_ctools_access_check',
  'settings form' => 'springboard_p2p_node_field_populated_ctools_settings',
  'settings form submit' => 'springboard_p2p_node_field_populated_ctools_settings_submit',
  'summary' => 'springboard_p2p_node_field_populated_ctools_summary',
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Custom callback defined by 'callback' in the $plugin array.
 *
 * Check for access.
 */
function springboard_p2p_node_field_populated_ctools_access_check($conf, $context) {
  // If for some unknown reason that $context isn't set,
  // we just want to be sure.
  if (empty($context) || empty($context->data)) {
    return FALSE;
  }

  // Check if the node field has a value.
  list($node_type, $field_name) = explode(':', $conf['node_field']);
  if (($context->data->type != $node_type) || empty($context->data->$field_name)) {
    return FALSE;
  }
  return TRUE;
}

/**
 * Settings form for the 'node_field_populated' access plugin.
 */
function springboard_p2p_node_field_populated_ctools_settings($form, &$form_state, $conf) {
  $entities = entity_get_info('node');
  $options = array();

  // Loop through the node entities adding each field as an option.
  foreach ($entities['bundles'] as $node_type => $bundle) {
    $instances   = field_info_instances('node', $node_type);
    foreach ($instances as $field_name => $field) {
      $options[$node_type . ':' . $field_name] = $bundle['label'] . ' - ' . $field['label'];
    }
  }

  $form['settings']['node_field'] = array(
    '#type' => 'select',
    '#title' => t('Field'),
    '#description' => t('Select the node field to check for a value'),
    '#default_value' => $conf['node_field'],
    '#options' => $options,
  );

  // Pass the labels so we an easily match them upon submission.
  $form['settings']['node_field_labels'] = array(
    '#type' => 'value',
    '#value' => $options,
  );

  return $form;
}

/**
 * Custom submit handler to save the pretty label in the conf array.
 */
function springboard_p2p_node_field_populated_ctools_settings_submit($form, &$form_state) {
  $form_state['values']['settings']['label'] = $form_state['values']['settings']['node_field_labels'][$form_state['values']['settings']['node_field']];
  unset($form_state['values']['settings']['node_field_labels']);
}

/**
 * Provide a summary description based upon the age.
 */
function springboard_p2p_node_field_populated_ctools_summary($conf, $context) {
  // Here we use the label value so it's pretty.
  return t('@label has been populated', array('@label' => $conf['label']));
}
