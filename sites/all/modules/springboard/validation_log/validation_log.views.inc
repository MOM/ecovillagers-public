<?php

/**
 * @file
 * Basic views integration for validation logs.
 */

/**
 * Implements hook_views_data(). From Views module.
 */
function validation_log_views_data() {
  $data['validation_log']['table']['group'] = t('Validation log');
  $data['validation_log']['table']['base'] = array(
    'field' => 'lid',
    'title' => t('Validation log table'),
    'help' => t("Validation log table contains log content."),
    'weight' => -10,
  );
  // Relationship to node.
  $data['validation_log']['nid'] = array(
    'title' => t('Validation log node'),
    'help' => t('Node referenced by validation log that references a node.'),
    'relationship' => array(
      'base' => 'node',
      'field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('Log node'),
    ),
  );
  // Fields.
  $data['validation_log']['lid'] = array(
    'title' => t('Log ID'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['validation_log']['form_key'] = array(
    'title' => t('Form key'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['validation_log']['time'] = array(
    'title' => t('Timestamp'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  $data['validation_log']['message'] = array(
    'title' => t('Message'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['validation_log']['cid'] = array(
    'title' => t('Component ID'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['validation_log']['ip'] = array(
    'title' => t('IP Address'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  return $data;
}
