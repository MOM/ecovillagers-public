<?php

/**
 * @file
 * Views definition.
 */

/**
 * Implements hook_views_data().
 */
function fundraiser_sustainers_views_data() {
  // Fundraiser sustainers log table.
  $data['fundraiser_sustainers_log']['table']['group']  = t('Fundraiser sustainers log');

  // Advertise this table as a possible base table.
  $data['fundraiser_sustainers_log']['table']['base'] = array(
    'field' => 'lid',
    'title' => t('Fundraiser sustainer log entries'),
    'help' => t("Log of sustainer donations."),
  );

  // Fields.
  // ----------------------------------------------------------------
  // Field log id.
  $data['fundraiser_sustainers_log']['lid'] = array(
    'title' => t('Sustainer Log ID'),
    'help' => t('The unique ID of the log entry.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Field did.
  $data['fundraiser_sustainers_log']['did'] = array(
    'title' => t('Donation ID'),
    'help' => t('The ID of the donation sustainer record.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'title' => t('Order'),
      'help' => t("Relate this log to its full order"),
      'handler' => 'views_handler_relationship',
      'base' => 'commerce_order',
      'base field' => 'order_id',
      'field' => 'did',
      'label' => t('Order'),
    ),
  );

  $data['fundraiser_sustainers_log']['timestamp'] = array(
    'title' => t('Activity Date'),
    'help' => t('The time that the activity occurred.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'date_views_filter_handler_simple',
    ),
    'argument' => array(
      'handler' => 'date_views_argument_handler_simple',
    ),
  );

  $data['fundraiser_sustainers_log']['lock_id'] = array(
    'title' => t('Lock ID'),
    'help' => t('The lock that was placed on the record during processing.'),
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

  $data['fundraiser_sustainers_log']['next_charge'] = array(
    'title' => t('Next Charge Date'),
    'help' => t('The next charge date of the sustainer at the time this log entry was created.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'date_views_filter_handler_simple',
    ),
    'argument' => array(
      'handler' => 'date_views_argument_handler_simple',
    ),
  );

  $data['fundraiser_sustainers_log']['old_state'] = array(
    'title' => t('Old state'),
    'help' => t('The gateway response (if any) of the sustainer before this log entry was recorded.'),
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

  $data['fundraiser_sustainers_log']['new_state'] = array(
    'title' => t('New state'),
    'help' => t('The new state of the sustainer when theis entry was logged.'),
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

  $data['fundraiser_sustainers_log']['attempts'] = array(
    'title' => t('Attempts'),
    'help' => t('The number of attempts against the sustainer as of this log entry.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['fundraiser_sustainers_log']['cancellation_reason'] = array(
    'title' => t('Cancellation reason'),
    'help' => t('Reason why the sustainer was canceled.'),
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

  return $data;
}
