<?php

/**
 * Implements hook_views_data.
 */
function commerce_litle_views_data() {

  $data['commerce_litle_fraud']['table']['group'] = t('Commerce Litle Fraud Log');

  $data['commerce_litle_fraud']['table']['base'] = array(
    'field' => 'order_id',
    'title' => t('Fraud Log'),
    'weight' => -10,
    'help' => t('Table for fraud log data'),
  );


  $data['commerce_litle_fraud']['order_id'] = array(
    'title' => t('Order ID'),
    'help' => t('OrderId'),
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
    'relationship' => array(
      'title' => t('Order'),
      'help' => t("Relate this log to its full order"),
      'handler' => 'views_handler_relationship',
      'base' => 'commerce_order',
      'base field' => 'order_id',
      'field' => 'order_id',
      'label' => t('Order'),
    ),
  );

  $data['commerce_litle_fraud']['litle_txn_id'] = array(
    'title' => t('Transaction ID'),
    'help' => t('The litle transaction ID'),
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

  $data['commerce_litle_fraud']['response_time'] = array(
    'title' => t('Response Time'),
    'help' => t('Response timestamp'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['commerce_litle_fraud']['avs_result'] = array(
    'title' => t('AVS result'),
    'help' => t('Credit card security code validation field'),
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

  $data['commerce_litle_fraud']['message'] = array(
    'title' => t('Response Message'),
    'help' => t('Approved, declined, etc.'),
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

  $data['commerce_litle_fraud']['device_review_status'] = array(
    'title' => t('Device Review Status'),
    'help' => t('Pass, Fail, statuses.'),
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

  $data['commerce_litle_fraud']['device_reputation_score'] = array(
    'title' => t('Device Reputation Score'),
    'help' => t('The reputation score returned by Litle advanced fraud detection.'),
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

  $data['commerce_litle_fraud']['mark_reviewed'] = array(
    'title' => t('Mark reviewed'),
    'help' => t('Checkbox to mark items as reviewed.'),
    'field' => array(
      'title' => t('Mark Reviewed'),
      'help' => t('Adds a checkbox to mark reviewed'),
      'handler' => 'commerce_litle_handler_field_mark_reviewed',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  return $data;
}