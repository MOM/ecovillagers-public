<?php

/**
 * @file
 * Views definition.
 */

/**
 * Implements hook_views_data().
 */
function fundraiser_commerce_views_data() {
  // Fundraiser sustainers log table.
  $data['fundraiser_commerce_gateway_settings_log']['table']['group']  = t('Fundraiser commerce gateway settings log');

  // Advertise this table as a possible base table.
  $data['fundraiser_commerce_gateway_settings_log']['table']['base'] = array(
    'field' => 'lid',
    'title' => t('Fundraiser commerce gateway settings log'),
    'help' => t("Log changes to the gateway settings"),
  );

  // Fields.
  // ----------------------------------------------------------------
  // Field log id.
  $data['fundraiser_commerce_gateway_settings_log']['lid'] = array(
    'title' => t('Gateway Log ID'),
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

  // Field gateway.
  $data['fundraiser_commerce_gateway_settings_log']['gateway_id'] = array(
    'title' => t('Gateway'),
    'help' => t('The gateway used to process the donation.'),
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

  $data['fundraiser_commerce_gateway_settings_log']['value'] = array(
    'title' => t('Changed Values'),
    'help' => t('The values which were changed'),
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

  // Field date_processed.
  $data['fundraiser_commerce_gateway_settings_log']['time'] = array(
    'title' => t('Time changed'),
    'help' => t('Timestamp of when the donation was processed.'),
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
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );

  // Field lock_id.
  $data['fundraiser_commerce_gateway_settings_log']['uid'] = array(
    'title' => t('User ID'),
    'help' => t('The user Id of the user who made the change'),
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
    'relationship' => array(
      'title' => t('User'),
      'help' => t("Relate this uid to a full user"),
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'base field' => 'uid',
      'field' => 'uid',
      'label' => t('User'),
    ),
  );

  return $data;
}
