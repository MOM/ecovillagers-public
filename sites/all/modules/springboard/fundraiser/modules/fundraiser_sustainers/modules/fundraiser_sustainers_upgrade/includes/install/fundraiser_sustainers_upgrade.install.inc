<?php

/**
 * @file
 * Install functions for sustainer upgrades.
 */

/**
 * Creates the springboard_petition content type.
 */
function _fundraiser_sustainers_upgrade_add_content_type() {
  $type = node_type_set_defaults();
  $type->name = t('Sustainer Upgrade Form');
  $type->type = 'sustainers_upgrade_form';
  $type->description = '';
  $type->title_label = t('Title');
  $type->has_title = TRUE;
  $type->base = 'node_content';
  $type->custom = TRUE;
  $type->modified = TRUE;
  $type->module = 'fundraiser_sustainers_upgrade';
  // Save or reset persistent variable values.
  $variables = array(
    'field_bundle_settings_node_' => array(),
    'menu_parent' => 'main-menu:0',
    'menu_options' => array(
      0 => 'main-menu',
    ),
    'node_submitted' => 0,
    'node_preview' => 1,
    'node_options' => array('status' => 'status'),
    'fundraiser' => 0,
    'webform_user' => 0,
  );
  foreach ($variables as $key => $value) {
    $variable_new = $key . '_' . $type->type;
    if (is_array($value)) {
      $value = array_keys(array_filter($value));
    }
    variable_set($variable_new, $value);
  }
  node_type_save($type);
  node_types_rebuild();
  node_add_body_field($type);
  // Add as a webform.
  $webform_node_types = variable_get('webform_node_types', array('webform'));
  $webform_node_types_primary = variable_get('webform_node_types_primary', array('webform'));
  $webform_node_types = array_merge($webform_node_types, array('sustainers_upgrade_form'));
  $webform_node_types_primary = array_merge($webform_node_types_primary, array('sustainers_upgrade_form'));
  variable_set('webform_node_types', array_unique($webform_node_types));
  variable_set('webform_node_types_primary', array_unique($webform_node_types_primary));
  // Done.
  drupal_set_message(t('The content type Sustainers Upgrade Form has been added.'));
  watchdog('fundraiser_sustainers_upgrade', 'Added content type Sustainers Upgrade Form.');

}


/**
 * Delete sustainer upgrade nodes.
 */
function _fundraiser_sustainers_upgrade_delete_nodes() {

  $result = db_select('node', 'n')
    ->fields('n', array('nid'))
    ->condition('type', 'sustainers_upgrade_form')
    ->execute();

  $nids = $result->fetchCol();

  if (!empty($nids)) {
    node_delete_multiple($nids);
    drupal_set_message('Springboard message actions have been deleted.');
  }
}
