<?php
/**
 * @file
 * Provides views table data for Salesforce management related tables.
 */

/**
 * Implements hook_views_data().
 */
function springboard_views_salesforce_management_api_views_data() {
  $data = array();
  // Salesforce_management_object_map table metadata
  $data['salesforce_management_object_map']['table'] = array(
    'group' => t('Salesforce management object map'),
    'base' => array(
      'title' => t('Salesforce object'),
      'help' => t('Salesforce object data.'),
    ),
  );
  // Salesforce_management_object_map fields
  $data['salesforce_management_object_map']['drupal_type'] = array(
    'title' => t('Drupal type'),
    'help' => t('Drupal object type (e.g. "node", "comment").'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_in_operator',
      'options callback' => 'springboard_views_sf_drupal_types',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['salesforce_management_object_map']['sfid'] = array(
    'title' => t('Salesforce object ID'),
    'help' => t('The Salesforce object ID.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['salesforce_management_object_map']['fieldmap'] = array(
    'title' => t('Fieldmap'),
    'help' => t('The ID of the fieldmap associated with this object.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // --------------------------------------------------------------------------
  // Salesforce_management_field_map table metadata
  // TODO

  // --------------------------------------------------------------------------
  // Salesforce_management_api_error table metadata
  // TODO

  return $data;
}
