<?php

/**
 * Adds the node fields and field group
 */
function _fundraiser_sustainers_upgrade_add_fields($update = FALSE) {

  $fields = array();

  // Get the field definitions.
  _fundraiser_sustainers_upgrade_name_field($fields);
  _fundraiser_sustainers_upgrade_body_field($fields);
  _fundraiser_sustainers_upgrade_fail_field($fields);
  _fundraiser_sustainers_upgrade_rollback_field($fields);
  _fundraiser_sustainers_upgrade_rollback_body($fields);
  _fundraiser_sustainers_upgrade_auto_field($fields);
  _fundraiser_sustainers_upgrade_cancel_field($fields);


  // Create the fields.
  foreach ($fields as $key => $values) {
    $instance = $values['_instance'];
    unset($values['_instance']);
    $base = field_info_field($key);
    $node = field_info_instance('node', $key, 'sustainers_upgrade_form');
    if (empty($base)) {
      field_create_field($values);
    }
    if (empty($node)) {
      field_create_instance($instance);
    }
  }

  // Create the field groups.
  if ($update == FALSE) {
    _fundraiser_sustainers_upgrade_install_groups();
  }
}

/**
 * Installs the options fieldgroup.
 */
function _fundraiser_sustainers_upgrade_install_groups() {

  $export = array();
  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sustainers_upgrade_options|node|sustainers_upgrade_form|form';
  $field_group->group_name = 'group_sustainers_upgrade_options';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'sustainers_upgrade_form';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->label = 'Upgrade Options';
  $field_group->weight = '33';
  $field_group->children = array(
    0 => 'field_sustainers_upgrade_fail',
    1 => 'field_sustainers_auto_upgrade',
    2 => 'field_sustainers_upgrade_b_roll',
    3 => 'field_sustainers_upgrade_roll',
    4 => 'field_sustainers_upgrade_cancel',


  );
  $field_group->format_type = 'fieldset';
  $field_group->format_settings = array(
    'label' => 'field_sustainers_upgrade_fail',
    'instance_settings' => array(
      'required_fields' => 1,
      'classes' => 'group-upgrade-options-mode field-group-fieldset',
      'description' => '',
    ),
    'formatter' => 'collapsible',
  );

  $export['group_sustainers_upgrade_options|node|sustainers_upgrade_form|form'] = $field_group;

  $groups = field_group_read_groups(array(
    'entity_type' => 'node',
    'bundle'      => 'sustainers_upgrade_form',
    'view_mode'   => 'full',
  ));

  foreach ($export as $field_group) {
    if (empty($groups['node']['sba_message_action']['form'][$field_group->group_name])) {
      field_group_group_save($field_group);
    }
  }
}


/**
 * Field definition function.
 *
 * @param $fields
 */
function _fundraiser_sustainers_upgrade_name_field(&$fields) {
  $fields['field_sustainers_upgrade_name'] = array(
    'active' => '1',
    'cardinality' => '1',
    'deleted' => '0',
    'entity_types' => array(),
    'field_name' => 'field_sustainers_upgrade_name',
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

    '_instance' => array(
      'bundle' => 'sustainers_upgrade_form',
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
      'field_name' => 'field_sustainers_upgrade_name',
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
        'weight' => '-4.5',
      ),
    ),
  );
}

/**
 * Field definition function.
 *
 * @param $fields
 */
function _fundraiser_sustainers_upgrade_body_field($fields) {
  $fields['body'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'node',
    ),
    'field_name' => 'body',
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
    'locked' => 0,
    'module' => 'text',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'text_with_summary',
    '_instance' => array(
      'bundle' => 'sustainers_upgrade_form',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => 5,
        ),
        'teaser' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(
            'trim_length' => 600,
          ),
          'type' => 'text_summary_or_trimmed',
          'weight' => 5,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'body',
      'label' => 'Body',
      'required' => 1,
      'settings' => array(
        'display_summary' => 1,
        'text_processing' => 1,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'rows' => 10,
          'summary_rows' => 5,
        ),
        'type' => 'text_textarea_with_summary',
        'weight' => 5,
      ),
    ),
  );
}

/**
 * Field definition function.
 *
 * @param $fields
 */
function _fundraiser_sustainers_upgrade_fail_field(&$fields) {

  $fields['field_sustainers_upgrade_fail'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'node',
    ),
    'field_name' => 'field_sustainers_upgrade_fail',
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
    'locked' => 0,
    'module' => 'text',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'text_long',
    '_instance' => array(
      'bundle' => 'sustainers_upgrade_form',
      'default_value' => array(
        0 => array(
          'value' => "",
          'format' => 'filtered_html',
        ),
      ),
      'deleted' => 0,
      'description' => 'This text will appear if the upgrade cannot be started',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'settings' => array(),
          'type' => 'text_long',
          'weight' => 6,
        ),
        'teaser' => array(
          'label' => 'hidden',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_sustainers_upgrade_fail',
      'label' => 'Failure Message',
      'required' => 0,
      'settings' => array(
        'text_processing' => 1,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'rows' => 3,
        ),
        'type' => 'text_textarea',
        'weight' => 3,
      ),
    ),
  );
}

/**
 * Field definition function.
 *
 * @param $fields
 */
function _fundraiser_sustainers_upgrade_rollback_body(&$fields) {

  $fields['field_sustainers_upgrade_b_roll'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'node',
    ),
    'field_name' => 'field_sustainers_upgrade_b_roll',
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
    'locked' => 0,
    'module' => 'text',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'text_long',
    '_instance' => array(
      'bundle' => 'sustainers_upgrade_form',
      'default_value' => array(
        0 => array(
          'value' => "",
          'format' => 'filtered_html',
        ),
      ),
      'deleted' => 0,
      'description' => 'This text will appear before the upgrade is rolled back.',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 6,
        ),
        'teaser' => array(
          'label' => 'hidden',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_sustainers_upgrade_b_roll',
      'label' => 'Rollback Message',
      'required' => 0,
      'settings' => array(
        'text_processing' => 1,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'rows' => 3,
        ),
        'type' => 'text_textarea',
        'weight' => 4,
      ),
    ),
  );
}

/**
 * Field definition function.
 *
 * @param $fields
 */
function _fundraiser_sustainers_upgrade_rollback_field(&$fields) {

  $fields['field_sustainers_upgrade_roll'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'node',
    ),
    'field_name' => 'field_sustainers_upgrade_roll',
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
    'locked' => 0,
    'module' => 'text',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'text_long',
    '_instance' => array(
      'bundle' => 'sustainers_upgrade_form',
      'default_value' => array(
        0 => array(
          'value' => "",
          'format' => 'filtered_html',
        ),
      ),
      'deleted' => 0,
      'description' => 'This text will appear after the upgrade is rolled back.',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 6,
        ),
        'teaser' => array(
          'label' => 'hidden',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_sustainers_upgrade_roll',
      'label' => 'Rollback Confirmation Message',
      'required' => 0,
      'settings' => array(
        'text_processing' => 1,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'rows' => 3,
        ),
        'type' => 'text_textarea',
        'weight' => 5,
      ),
    ),
  );
}

/**
 * Field definition function.
 *
 * @param $fields
 */
function _fundraiser_sustainers_upgrade_auto_field(&$fields) {

  $fields['field_sustainers_auto_upgrade'] = array(
    'active' => 1,
    'cardinality' => 2,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_sustainers_auto_upgrade',
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        1 => 'Require Confirmation',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_text',
    '_instance' => array(
      'bundle' => 'sustainers_upgrade_form',
      'default_value' => array(
        0 => array(
          'value' => 1,
        ),
      ),
      'deleted' => 0,
      'description' => 'Determines whether the form will be auto-submitted.',
      'display' => array(
        'default' => array(
          'label' => 'Above',
          'module' => 'list',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 3,
        ),
        'teaser' => array(
          'label' => 'hidden',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_sustainers_auto_upgrade',
      'label' => 'Upgrade workflow',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'options',
        'settings' => array(),
        'type' => 'options_buttons',
        'weight' => 1,
      ),
    ),
  );

}

/**
 * Field definition function.
 *
 * @param $fields
 */
function _fundraiser_sustainers_upgrade_cancel_field(&$fields) {
  $fields['field_sustainers_upgrade_cancel'] = array(
    'active' => '1',
    'cardinality' => '1',
    'deleted' => '0',
    'entity_types' => array(),
    'field_name' => 'field_sustainers_upgrade_cancel',
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

    '_instance' => array(
      'bundle' => 'sustainers_upgrade_form',
      'default_value' => array(
        0 => array(
          'value' => variable_get('site_frontpage', 'node'),
        ),
      ),
      'deleted' => '0',
      'description' => 'The page to redirect to if the user clicks the "I\'m not" link; e.g, node/4',
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
      'field_name' => 'field_sustainers_upgrade_cancel',
      'label' => 'Cancel Redirect',
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
        'weight' => '10',
      ),
    ),
  );
}

/**
 * Delete springboard message action fields.
 */
function _fundraiser_sustainers_upgrade_delete_fields() {
  $fields = array(
    'field_sustainers_upgrade_name',
    'field_sustainers_upgrade_fail',
    'field_sustainers_auto_upgrade',
    'field_sustainers_upgrade_roll',
    'field_sustainers_upgrade_cancel',
    'field_sustainers_upgrade_b_roll',

  );
  foreach ($fields as $field_name) {
    $field = field_info_instance('node', $field_name, 'sustainers_upgrade_form');
    field_delete_instance($field);
    $field = field_info_field($field_name);
    field_delete_field($field);
  }
  drupal_set_message('Sustainer upgrade fields deleted.');
}
