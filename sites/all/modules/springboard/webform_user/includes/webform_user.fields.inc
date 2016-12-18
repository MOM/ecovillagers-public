<?php
/**
 * @file
 * webform_user.fields.inc
 */

/**
 * Add fields needed by webform_user to a node type.
 *
 * @param string $type
 *   The type of node to check if the webform_user fields exist,
 *   and if not add them to.
 */
function _webform_user_add_default_fields($type) {
  $fields = _webform_user_default_fields_settings($type);
  foreach ($fields as $field_name => $field) {
    // These should be added on each page request, but to be sure do it again.
    module_load_include('inc', 'field', 'field.crud');
    module_load_include('inc', 'field', 'field.info');

    // If the field doesn't exist create it.
    if (!field_info_field($field_name)) {
      field_create_field($field['field_config']);
    }
    // Before adding the field check that it does not exist on the node type.
    if (!field_info_instance('node', $field_name, $type)) {
      field_create_instance($field['field_instance']);
    }
  }
}

/**
 * Returns an array of field configurations.
 *
 * This is copied from a features export.
 *
 * @param string $type
 *   The type of node these fields will be added to,
 *   used to populate the bundle property.
 */
function _webform_user_default_fields_settings($type) {
  $fields = array();

  $fields['field_webform_user_internal_name'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_webform_user_internal_name',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'translatable' => '0',
      'type' => 'text',
    ),
    'field_instance' => array(
      'bundle' => $type,
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '2',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_webform_user_internal_name',
      'label' => 'Internal Name',
      'required' => 1,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '0',
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Internal Name');

  return $fields;
}
