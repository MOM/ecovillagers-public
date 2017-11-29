<?php

function _page_wrappers_create_file_entities() {

  // Ensure file_entity is installed before creating file types.
  if (!module_exists('file_entity')) {
    module_enable(array('file_entity'));
  }

  $file_types = array();

  $file_type = new stdClass();
  $file_type->disabled = FALSE; /* Edit this to true to make a default file_type disabled initially */
  $file_type->api_version = 1;
  $file_type->type = 'page_wrappers_asset_css';
  $file_type->label = 'Page Wrappers Styles';
  $file_type->description = '@TODO'; // @TODO
  $file_type->mimetypes = array(
    0 => 'text/css',
  );
  $file_types[$file_type->type] = $file_type;

  $file_type = new stdClass();
  $file_type->disabled = FALSE; /* Edit this to true to make a default file_type disabled initially */
  $file_type->api_version = 1;
  $file_type->type = 'page_wrappers_asset_js';
  $file_type->label = 'Page Wrappers Script';
  $file_type->description = '@TODO'; // @TODO
  $file_type->mimetypes = array(
    0 => 'application/x-javascript',
  );
  $file_types[$file_type->type] = $file_type;

  foreach ($file_types as $file_type) {
    file_type_save($file_type);
  }

  $fields = array(
    'pw_asset_title' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_pw_asset_title',
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
      '_instances' => array(
        'page_wrappers_asset_css' => array(
          'bundle' => 'page_wrappers_asset_css',
          'default_value' => NULL,
          'deleted' => 0,
          'description' => 'Enter a title for this file that will make it easy to search for. If you leave this field blank, the name of the file you upload will be used.',
          'display' => array(
            'default' => array(
              'label' => 'none',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 1,
            ),
            'preview' => array(
              'label' => 'none',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 0,
            ),
            'teaser' => array(
              'label' => 'none',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 0,
            ),
          ),
          'entity_type' => 'file',
          'field_name' => 'field_pw_asset_title',
          'label' => 'Title',
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
            'weight' => 0,
          ),
        ),

        'page_wrapper_asset_js' => array(
          'bundle' => 'page_wrappers_asset_js',
          'default_value' => NULL,
          'deleted' => 0,
          'description' => 'Enter a title for this file that will make it easy to search for. If you leave this field blank, the name of the file you upload will be used.',
          'display' => array(
            'default' => array(
              'label' => 'none',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 1,
            ),
            'preview' => array(
              'label' => 'none',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 0,
            ),
            'teaser' => array(
              'label' => 'none',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 0,
            ),
          ),
          'entity_type' => 'file',
          'field_name' => 'field_pw_asset_title',
          'label' => 'Title',
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
            'weight' => 0,
          ),
        ),
      ),
    ),

    'pw_asset_description' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_pw_asset_description',
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
      '_instances' => array(
        'page_wrapper_asset_css' => array(
          'bundle' => 'page_wrappers_asset_css',
          'default_value' => NULL,
          'deleted' => 0,
          'description' => 'Enter a description for this file that will help others to understand its purpose. You may also use this space to make notes about how to best use this file',
          'display' => array(
            'default' => array(
              'label' => 'none',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 0,
            ),
            'preview' => array(
              'label' => 'none',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 0,
            ),
            'teaser' => array(
              'label' => 'none',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 0,
            ),
          ),
          'entity_type' => 'file',
          'field_name' => 'field_pw_asset_description',
          'label' => 'Description',
          'required' => 0,
          'settings' => array(
            'text_processing' => 0,
            'user_register_form' => FALSE,
          ),
          'widget' => array(
            'active' => 1,
            'module' => 'text',
            'settings' => array(
              'rows' => 5,
            ),
            'type' => 'text_textarea',
          ),
        ),
        'page_wrapper_asset_js' => array(
          'bundle' => 'page_wrappers_asset_js',
          'default_value' => NULL,
          'deleted' => 0,
          'description' => 'Enter a description for this file that will help others to understand its purpose. You may also use this space to make notes about how to best use this file',
          'display' => array(
            'default' => array(
              'label' => 'none',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 0,
            ),
            'preview' => array(
              'label' => 'none',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 0,
            ),
            'teaser' => array(
              'label' => 'none',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 0,
            ),
          ),
          'entity_type' => 'file',
          'field_name' => 'field_pw_asset_description',
          'label' => 'Description',
          'required' => 0,
          'settings' => array(
            'text_processing' => 0,
            'user_register_form' => FALSE,
          ),
          'widget' => array(
            'active' => 1,
            'module' => 'text',
            'settings' => array(
              'rows' => 5,
            ),
            'type' => 'text_textarea',
          ),
        ),
      ),
    ),
  );
  foreach ($fields as $key => $values) {
    $instances = $values['_instances'];
    unset($values['_instances']);
    $field_exists = field_info_field($values['field_name']);
    if (empty($field_exists)) {
      field_create_field($values);
    }
    foreach ($instances as $instance) {
      $instance_exists = field_info_instance('file', $instance['field_name'], $instance['bundle']);
      if (empty($instance_exists)) {
        field_create_instance($instance);
      }
    }
  }

  // Disable unecessary file entities.
  $disable_entities = array('document', 'audio', 'video');
  foreach ($disable_entities as $type) {
    file_type_disable($type);
  }

  // Prepare the Page Wrappers directories.
  $tpl_dir = PAGE_WRAPPERS_TPL_DIR;
  $css_dir = PAGE_WRAPPERS_CSS_DIR;
  $js_dir = PAGE_WRAPPERS_JS_DIR;
  file_prepare_directory($tpl_dir, FILE_CREATE_DIRECTORY);
  file_prepare_directory($css_dir, FILE_CREATE_DIRECTORY);
  file_prepare_directory($js_dir, FILE_CREATE_DIRECTORY);

}

function _page_wrappers_delete_file_entity_fields() {
  $fields = array(
    'field_pw_asset_description',
  );
  foreach ($fields as $field_name) {
    $field = field_info_instance('node', $field_name, 'page_wrappers_asset');
    field_delete_instance($field);
    $field = field_info_field($field_name);
    field_delete_field($field);
  }
  drupal_set_message(t('Page Wrapper Asset fields deleted.'));
}

function _page_wrappers_delete_file_entities() {
  // @TODO
  //require_once 'page_wrappers.module';
  //$nids = page_wrappers_get_nodes();
  //node_delete_multiple($nids);
  //drupal_set_message(t('Page Wrappers have been deleted.'));
}
