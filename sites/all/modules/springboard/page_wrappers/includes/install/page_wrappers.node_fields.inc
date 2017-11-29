<?php

/**
 * Node and associated field setup for Page Wrappers content type.
 */
function _page_wrappers_create_fields() {
  $t = get_t();

  // Build list of themes for the theme css select field's options.
  $themes = list_themes();
  $themes_options = array();
  foreach ($themes as $theme) {
    $themes_options[$theme->name] = $theme->info['name'];
  }
  $fields = array(
    // Theme css select field.
    'theme_css' => array(
      'active' => 1,
      'cardinality' => -1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'page_wrappers_theme_css',
      'foreign keys' => array(),
      'indexes' => array(
        'value' => array(
          0 => 'value',
        ),
      ),
      'locked' => 0,
      'module' => 'list',
      'settings' => array(
        'allowed_values' => $themes_options,
      ),
      'translatable' => 0,
      'type' => 'list_text',
      '_instance' => array(
        'bundle' => 'page_wrapper',
        'default_value' => NULL,
        'deleted' => 0,
        'description' => '',
        'entity_type' => 'node',
        'field_name' => 'page_wrappers_theme_css',
        'label' => 'Include Theme CSS',
        'required' => 0,
        'settings' => array(
          'user_register_form' => FALSE,
        ),
        'widget' => array(
          'active' => 1,
          'module' => 'options',
          'settings' => array(),
          'type' => 'options_select',
          'weight' => 1,
        ),
      ),
    ),

    // CSS filefield.
    'css_file_entity' => array(
      'active' => 1,
      'cardinality' => -1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'sb_page_wrappers_css',
      'foreign keys' => array(
        'file_managed' => array(
          'columns' => array(
            'target_id' => 'fid',
          ),
          'table' => 'file_managed',
        ),
      ),
      'indexes' => array(
        'target_id' => array(
          0 => 'target_id',
        ),
      ),
      'locked' => 0,
      'module' => 'entityreference',
      'settings' => array(
        'handler' => 'views',
        'handler_settings' => array(
          'behaviors' => array(
            'views-select-list' => array(
              'status' => 0,
            ),
          ),
          'view' => array(
            'args' => array(),
            'display_name' => 'entityreference_1',
            'view_name' => 'pw_asset_autocomplete',
          ),
        ),
        'target_type' => 'file',
      ),
      'translatable' => 0,
      'type' => 'entityreference',
      '_instance' => array(
        'bundle' => 'page_wrapper',
        'default_value_function' => '',
        'deleted' => 0,
        'description' => '',
        'display' => array(
          'default' => array(
            'label' => 'above',
            'module' => 'entityreference',
            'settings' => array(
              'link' => FALSE,
            ),
            'type' => 'entityreference_label',
            'weight' => 2,
          ),
          'teaser' => array(
            'label' => 'above',
            'settings' => array(),
            'type' => 'hidden',
            'weight' => 0,
          ),
        ),
        'entity_type' => 'node',
        'field_name' => 'sb_page_wrappers_css',
        'label' => 'Upload a Stylesheet',
        'required' => 0,
        'settings' => array(
          'behaviors' => array(
            'prepopulate' => array(
              'status' => 0,
            ),
          ),
          'user_register_form' => FALSE,
        ),
        'widget' => array(
          'active' => 1,
          'module' => 'inline_entity_form',
          'settings' => array(
            'fields' => array(),
            'type_settings' => array(
              'allow_clone' => 0,
              'allow_existing' => 1,
              'allow_new' => 1,
              'delete_references' => 0,
              'label_plural' => 'stylesheets',
              'label_singular' => 'stylesheet',
              'match_operator' => 'CONTAINS',
              'override_labels' => 1,
            ),
          ),
          'type' => 'inline_entity_form',
          'weight' => 31,
        ),
      ),
    ),

    // Javascript filefield.
    'js_filefield' => array(
      'active' => 1,
      'cardinality' => -1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'sb_page_wrappers_js',
      'foreign keys' => array(
        'file_managed' => array(
          'columns' => array(
            'target_id' => 'fid',
          ),
          'table' => 'file_managed',
        ),
      ),
      'indexes' => array(
        'target_id' => array(
          0 => 'target_id',
        ),
      ),
      'locked' => 0,
      'module' => 'entityreference',
      'settings' => array(
        'handler' => 'views',
        'handler_settings' => array(
          'behaviors' => array(
            'views-select-list' => array(
              'status' => 0,
            ),
          ),
          'view' => array(
            'args' => array(),
            'display_name' => 'entityreference_2',
            'view_name' => 'pw_asset_autocomplete',
          ),
        ),
        'target_type' => 'file',
      ),
      'translatable' => 0,
      'type' => 'entityreference',
      '_instance' => array(
        'bundle' => 'page_wrapper',
        'default_value_function' => '',
        'deleted' => 0,
        'description' => '',
        'display' => array(
          'default' => array(
            'label' => 'above',
            'module' => 'entityreference',
            'settings' => array(
              'link' => FALSE,
            ),
            'type' => 'entityreference_label',
            'weight' => 2,
          ),
          'teaser' => array(
            'label' => 'above',
            'settings' => array(),
            'type' => 'hidden',
            'weight' => 0,
          ),
        ),
        'entity_type' => 'node',
        'field_name' => 'sb_page_wrappers_js',
        'label' => 'Upload a Script',
        'required' => 0,
        'settings' => array(
          'behaviors' => array(
            'prepopulate' => array(
              'status' => 0,
            ),
          ),
          'user_register_form' => FALSE,
        ),
        'type' => 'inline_entity_form',
        'weight' => 31,
        'widget' => array(
          'active' => 1,
          'module' => 'inline_entity_form',
          'settings' => array(
            'fields' => array(),
            'match_operator' => 'CONTAINS',
            'path' => '',
            'size' => 60,
            'type_settings' => array(
              'allow_clone' => 0,
              'allow_existing' => 1,
              'allow_new' => 1,
              'delete_references' => 0,
              'label_plural' => 'scripts',
              'label_singular' => 'script',
              'match_operator' => 'CONTAINS',
              'override_labels' => 1,
            ),
          ),
          'type' => 'inline_entity_form',
          'weight' => 32,
        ),
      ),
    ),

    // HTML template.
    'html_template' => array(
      'field_name' => 'page_wrappers_html_template',
      'type' => 'text_with_summary',
      'cardinality' => 1,
      'settings' => array(),
      'entity_types' => array('node'),
      '_instance' => array(
        'field_name' => 'page_wrappers_html_template',
        'entity_type' => 'node',
        'bundle' => 'page_wrapper',
        'required' => TRUE,
        'label' => st('HTML Template'),
        'description' => st('HTML version of the email body.'),
        'widget' => array(
          'type' => 'text_with_summary',
          'weight' => 6,
          'settings' => array(),
        ),
      ),
    ),
  );

  foreach ($fields as $key => $values) {
    $instance = $values['_instance'];
    unset($values['_instance']);

    $field_exists = field_info_field($values['field_name']);
    if (empty($field_exists)) {
      field_create_field($values);
    }
    $instance_exists = field_info_instance('node', $values['field_name'], 'page_wrapper');
    if (empty($instance_exists)) {
      field_create_instance($instance);
    }

  }
}

/**
 * Delete pagewrapers fields.
 */
function _page_wrappers_delete_fields() {
  $fields = array(
    'sb_page_wrappers_js',
    'sb_page_wrappers_css',
    'page_wrappers_html_template',
    'page_wrappers_theme_css',
  );
  foreach ($fields as $field_name) {
    $field = field_info_instance('node', $field_name, 'email_wrapper');
    field_delete_instance($field);
    $field = field_info_field($field_name);
    field_delete_field($field);
  }
  drupal_set_message(t('Page Wrapper fields deleted.'));
}