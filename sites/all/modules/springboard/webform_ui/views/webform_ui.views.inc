<?php

/**
 * Implements hook_views_data_alter().
 */
function webform_ui_views_data_alter(&$data) {
  $data['webform_submissions']['views_bulk_operations'] = array(
    'title' => t('Webform Submissions'),
    'group' => t('Bulk operations'),
    'help' => t('Provide a checkbox to select the row for bulk operations.'),
    'real field' => 'nid',
    'field' => array(
      'handler' => 'webform_ui_bulk_operations_handler_field_operations',
      'click sortable' => FALSE,
    ),
  );
}
