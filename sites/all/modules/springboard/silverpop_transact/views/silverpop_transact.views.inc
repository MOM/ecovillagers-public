<?php
/**
 * @file
 * Provides integration with Views module.
 */

/**
 * Implements hook_views_data().
 */
function silverpop_transact_views_data() {

  $data = array();
  $data['silverpop_transact_log']['table']['group'] = t('Silverpop Transact');
  $data['silverpop_transact_log']['table']['base'] = array(
    'title' => t('Silverpop Transact'),
    'help' => t('Contains log records for Silverpop Transact.'),
  );
  // Expose the ID field.
  $data['silverpop_transact_log']['id'] = array(
    'title' => t('ID'),
    'help' => t('The record ID.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  // Expose the Model field.
  $data['silverpop_transact_log']['model'] = array(
    'title' => t('Model'),
    'help' => t('The API module used (XML or SMTP).'),
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
  );
  // Expose the Origin field.
  $data['silverpop_transact_log']['origin'] = array(
    'title' => t('Origin'),
    'help' => t('Origin of the log record (module or rule).'),
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
  );
  // Expose the Origin field.
  $data['silverpop_transact_log']['created'] = array(
    'title' => t('Created'),
    'help' => t('Created date/time.'),
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
  // Expose the Status field.
  // @TODO Integer doesn't seem like the right type.
  $data['silverpop_transact_log']['status'] = array(
    'title' => t('Status'),
    'help' => t('Success/Failure.'),
    'field' => array(
      'handler' => 'silverpop_transact_handler_status_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  // Expose the Silverpop Message field.
  $data['silverpop_transact_log']['silverpop_message'] = array(
    'title' => t('Silverpop Message'),
    'help' => t('Message returned from Silverpop on XML submission. XML model only.'),
    'field' => array(
      'handler' => 'silverpop_transact_handler_silverpop_message_field',
      'click sortable' => TRUE,

    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  // Expose the Silverpop Message field.
  $data['silverpop_transact_log']['filename'] = array(
    'title' => t('Filename'),
    'help' => t('Filename of XML generated and sent to Silverpop.  XML model only.'),
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
  );
  // Expose the Last Retry field.
  $data['silverpop_transact_log']['created'] = array(
    'title' => t('Last Retry'),
    'help' => t('Last retry date/time. XML model only.'),
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
  return $data;
}
