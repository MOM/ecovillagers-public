<?php

/**
 * @file
 * Install helper functions for field API fields.
 */

/**
 * Create FieldAPi fields for social actions.
 */
function _sba_social_action_create_node_fields($update = false) {

  $fields = array(
    'field_sba_social_action_img' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array('node'),
      'field_name' => 'field_sba_social_action_img',
      'foreign keys' => array(
        'fid' => array(
          'columns' => array(
            'fid' => 'fid',
          ),
          'table' => 'file_managed',
        ),
      ),
      'indexes' => array(
        'fid' => array(
          0 => 'fid',
        ),
      ),
      'locked' => 0,
      'module' => 'image',
      'settings' => array(
        'default_image' => 0,
        'uri_scheme' => 'public',
      ),
      'translatable' => 0,
      'type' => 'image',

      '_instance' => array(
        'bundle' => 'sba_social_action',
        'deleted' => 0,
        'description' => '',
        'display' => array(
          'default' => array(
            'label' => 'hidden',
            'module' => 'image',
            'settings' => array(
              'image_link' => '',
              'image_style' => '',
            ),
            'type' => 'image',
            'weight' => -1,
          ),
          'teaser' => array(
            'label' => 'above',
            'settings' => array(),
            'type' => 'hidden',
            'weight' => 0,
          ),
        ),
        'entity_type' => 'node',
        'field_name' => 'field_sba_social_action_img',
        'label' => 'Image',
        'required' => 0,
        'settings' => array(
          'alt_field' => 1,
          'default_image' => 0,
          'file_directory' => '',
          'file_extensions' => 'png gif jpg jpeg',
          'max_filesize' => '',
          'max_resolution' => '',
          'min_resolution' => '',
          'title_field' => 0,
          'user_register_form' => FALSE,
        ),
        'widget' => array(
          'active' => 1,
          'module' => 'image',
          'settings' => array(
            'preview_image_style' => 'thumbnail',
            'progress_indicator' => 'throbber',
          ),
          'type' => 'image_image',
          'weight' => 0,
        ),
      ),
    ),
  );

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
      'bundle' => 'sba_social_action',
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
          'summary_rows' => 3,
        ),
        'type' => 'text_textarea_with_summary',
        'weight' => 6,
      ),
    ),
  );

  $fields['field_sba_social_fieldset_title'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'node',
    ),
    'field_name' => 'field_sba_social_fieldset_title',
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
    'type' => 'text',
    '_instance' => array(
      'bundle' => 'sba_social_action',
      'default_value' => array(0 => array(
      'value' => t('Send a Social Message'),
    ),
      ),
      'deleted' => 0,
      'description' => t('The title above the webform fields on the first-step page.'),
      'display' => array(
        'default' => array(
          'label' => 'hidden',
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
      'field_name' => 'field_sba_social_fieldset_title',
      'label' => 'User Form Label',
      'required' => 1,
      'settings' => array(
        'text_processing' => 0,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => 60,
        ),
        'type' => 'text_textfield',
        'weight' => 5,
      ),
    ),
  );

  $fields['field_sba_social_step_two_submit'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'node',
    ),
    'field_name' => 'field_sba_social_step_two_submit',
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
    'type' => 'text',
    '_instance' => array(
      'bundle' => 'sba_social_action',
      'default_value' => array(0 => array(
        'value' => t("I'm done"),
      ),
      ),
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
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
      'field_name' => 'field_sba_social_step_two_submit',
      'label' => 'Step Two Submit Button Text',
      'required' => 1,
      'settings' => array(
        'text_processing' => 0,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => 60,
        ),
        'type' => 'text_textfield',
        'weight' => 15,
      ),
    ),
  );


  // Exported field_base: 'field_sba_social_call_to_action'
  $fields['field_sba_social_call_to_action'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_sba_social_call_to_action',
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
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
    '_instance' => array(
      'bundle' => 'sba_social_action',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => 4,
        ),
        'teaser' => array(
          'label' => 'hidden',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 4,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_sba_social_call_to_action',
      'label' => 'Call to Action',
      'required' => 0,
      'settings' => array(
        'text_processing' => 0,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => 60,
        ),
        'type' => 'text_textfield',
        'weight' => 4,
      ),
    ),
  );

  // Exported field_base: 'field_sba_social_call_to_action'
  $fields['field_sba_social_step_two_header'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_sba_social_step_two_header',
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
      'bundle' => 'sba_social_action',
      'default_value' => '',
      'deleted' => 0,
      'description' => t('The header text at the top of the step two page.'),
      'display' => array(
        'default' => array(
          'label' => 'hidden',
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
      'field_name' => 'field_sba_social_step_two_header',
      'label' => 'Step Two Intro Text',
      'required' => 0,
      'settings' => array(
        'display_summary' => 1,
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
        'weight' => 7,
      ),
    ),
  );

  $fields['field_sba_test_mode'] = array(
    'active' => 1,
    'cardinality' => 2,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_sba_test_mode',
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
        1 => 'Enabled',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_text',
    '_instance' => array(
      'bundle' => 'sba_social_action',
      'default_value' => array(
        0 => array(
          'value' => 0,
        ),
      ),
      'deleted' => 0,
      'description' => 'Check this box to enable test mode. No tweets will be posted when test mode is enabled. Unpublished actions are always in test mode.',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
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
      'field_name' => 'field_sba_test_mode',
      'label' => 'Test mode',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'options',
        'settings' => array(),
        'type' => 'options_buttons',
        'weight' => 31,
      ),
    ),
  );

  $fields['field_sba_social_require_auth'] = array(
    'active' => 1,
    'cardinality' => 2,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_sba_social_require_auth',
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
        1 => 'Enabled',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_text',
    '_instance' => array(
      'bundle' => 'sba_social_action',
      'default_value' => array(
        0 => array(
          'value' => 1,
        ),
      ),
      'deleted' => 0,
      'description' => 'If you require authentication, users will have to log into the Springboard Twitter app before tweeting, and you will then gain access to some of their Twitter profile information. By Requiring Twitter Authentication you certify that you have read and agree to adhere to the Twitter terms of services, located <a href="https://twitter.com/tos">here</a>.',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
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
      'field_name' => 'field_sba_social_require_auth',
      'label' => 'Require Twitter Authentication?',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'options',
        'settings' => array(),
        'type' => 'options_buttons',
        'weight' => 31,
      ),
    ),
  );

  foreach ($fields as $key => $values) {
    $instance = $values['_instance'];
    unset($values['_instance']);
    $base = field_info_field($key);
    $node = field_info_instance('node', $key, 'sba_social_action');
    if (empty($base)) {
      field_create_field($values);
    }
    if (empty($node)) {
      field_create_instance($instance);
    }
  }
  if ($update == FALSE) {

    $export = array();

    $field_group = new stdClass();
    $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
    $field_group->api_version = 1;
    $field_group->identifier = 'group_sba_test_mode|node|sba_social_action|form';
    $field_group->group_name = 'group_sba_test_mode';
    $field_group->entity_type = 'node';
    $field_group->bundle = 'sba_social_action';
    $field_group->mode = 'form';
    $field_group->parent_name = '';
    $field_group->label = 'Test mode';
    $field_group->weight = '33';
    $field_group->children = array(
      0 => 'field_sba_test_mode',
    );
    $field_group->format_type = 'fieldset';
    $field_group->format_settings = array(
      'label' => 'Test mode',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-test-mode field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    );

    $export['group_sba_test_mode|node|sba_social_action|form'] = $field_group;

    $field_group = new stdClass();
    $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
    $field_group->api_version = 1;
    $field_group->identifier = 'group_sba_header_text|node|sba_social_action|form';
    $field_group->group_name = 'group_sba_header_text';
    $field_group->entity_type = 'node';
    $field_group->bundle = 'sba_social_action';
    $field_group->mode = 'form';
    $field_group->parent_name = '';
    $field_group->label = 'Multi-step options';
    $field_group->weight = '32';
    $field_group->children = array(
      0 => 'field_sba_social_step_two_header',
      1 => 'field_sba_social_step_two_submit',
      2 => 'field_sba_social_require_auth'
    );
    $field_group->format_type = 'fieldset';
    $field_group->format_settings = array(
      'label' => 'Intro Text',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-header-text field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    );

    $export['group_sba_header_text|node|sba_social_action|form'] = $field_group;


    $field_group = new stdClass();
    $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
    $field_group->api_version = 1;
    $field_group->identifier = 'group_sba_action_body|node|sba_social_action|form';
    $field_group->group_name = 'group_sba_action_body';
    $field_group->entity_type = 'node';
    $field_group->bundle = 'sba_social_action';
    $field_group->mode = 'form';
    $field_group->parent_name = '';
    $field_group->label = 'Body text';
    $field_group->weight = '31';
    $field_group->children = array(
      0 => 'body',
    );
    $field_group->format_type = 'fieldset';
    $field_group->format_settings = array(
      'label' => 'Body',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-body-text field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    );

    $export['group_sba_action_body|node|sba_social_action|form'] = $field_group;


    $field_group = new stdClass();
    $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
    $field_group->api_version = 1;
    $field_group->identifier = 'group_sba_social_page_elements|node|sba_social_action|form';
    $field_group->group_name = 'group_sba_social_page_elements';
    $field_group->entity_type = 'node';
    $field_group->bundle = 'sba_social_action';
    $field_group->mode = 'form';
    $field_group->parent_name = '';
    $field_group->label = 'Action options';
    $field_group->weight = '30';
    $field_group->children = array(
      0 => 'field_sba_social_call_to_action',
      1 => 'field_sba_social_action_img',
      2 => 'field_sba_social_fieldset_title',
    );
    $field_group->format_type = 'fieldset';
    $field_group->format_settings = array(
      'label' => 'Body',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-page-elements field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    );

    $export['group_sba_social_page_elements|node|sba_social_action|form'] = $field_group;

    foreach ($export as $field_group) {
      field_group_group_save($field_group);
    }
  }
}

/**
 * Delete springboard social action fields.
 */
function _sba_social_action_delete_fields() {
  $fields = array(
    'field_sba_social_call_to_action',
    'field_sba_social_action_img',
    'field_sba_social_fieldset_title',
    'field_sba_social_step_two_header',
    'field_sba_social_step_two_submit',
    'field_sba_social_require_auth'
  );
  foreach ($fields as $field_name) {
    $field = field_info_instance('node', $field_name, 'sba_social_action');
    field_delete_instance($field);
    $field = field_info_field($field_name);
    field_delete_field($field);
  }
  drupal_set_message('Springboard social action fields deleted.');
}
