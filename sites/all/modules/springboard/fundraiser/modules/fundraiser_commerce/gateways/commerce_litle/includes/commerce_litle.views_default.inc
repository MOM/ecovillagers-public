<?php
function commerce_litle_views_default_views() {
$view = new view();
$view->name = 'litle_fraud_log';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'commerce_litle_fraud';
$view->human_name = 'Litle Fraud Log';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Litle Fraud Log';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'administer commerce_order entities';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '10';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'order_id' => 'order_id',
  'message' => 'message',
  'avs_result' => 'avs_result',
  'litle_txn_id' => 'litle_txn_id',
  'device_review_status' => 'device_review_status',
  'device_reputation_score' => 'device_reputation_score',
  'status' => 'status',
  'mail' => 'mail',
  'commerce_order_total' => 'commerce_order_total',
);
$handler->display->display_options['style_options']['default'] = 'order_id';
$handler->display->display_options['style_options']['info'] = array(
  'order_id' => array(
    'sortable' => 1,
    'default_sort_order' => 'desc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'message' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'avs_result' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'litle_txn_id' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'device_review_status' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'device_reputation_score' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'status' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'mail' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'commerce_order_total' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
);
/* No results behavior: Global: Text area */
$handler->display->display_options['empty']['area']['id'] = 'area';
$handler->display->display_options['empty']['area']['table'] = 'views';
$handler->display->display_options['empty']['area']['field'] = 'area';
$handler->display->display_options['empty']['area']['label'] = 'No results';
$handler->display->display_options['empty']['area']['empty'] = TRUE;
$handler->display->display_options['empty']['area']['content'] = 'There are no items for this report. A Litle account with Advanced Fraud Protection is required.';
$handler->display->display_options['empty']['area']['format'] = 'filtered_html';
/* Relationship: Commerce Litle Fraud Log: Order */
$handler->display->display_options['relationships']['order_id']['id'] = 'order_id';
$handler->display->display_options['relationships']['order_id']['table'] = 'commerce_litle_fraud';
$handler->display->display_options['relationships']['order_id']['field'] = 'order_id';
/* Field: Commerce Litle Fraud Log: Order ID */
$handler->display->display_options['fields']['order_id']['id'] = 'order_id';
$handler->display->display_options['fields']['order_id']['table'] = 'commerce_litle_fraud';
$handler->display->display_options['fields']['order_id']['field'] = 'order_id';
$handler->display->display_options['fields']['order_id']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['order_id']['alter']['path'] = 'admin/commerce/orders/[order_id]';
/* Field: Commerce Litle Fraud Log: Response Message */
$handler->display->display_options['fields']['message']['id'] = 'message';
$handler->display->display_options['fields']['message']['table'] = 'commerce_litle_fraud';
$handler->display->display_options['fields']['message']['field'] = 'message';
$handler->display->display_options['fields']['message']['label'] = 'Message';
/* Field: Commerce Litle Fraud Log: AVS result */
$handler->display->display_options['fields']['avs_result']['id'] = 'avs_result';
$handler->display->display_options['fields']['avs_result']['table'] = 'commerce_litle_fraud';
$handler->display->display_options['fields']['avs_result']['field'] = 'avs_result';
$handler->display->display_options['fields']['avs_result']['separator'] = '';
/* Field: Commerce Litle Fraud Log: Transaction ID */
$handler->display->display_options['fields']['litle_txn_id']['id'] = 'litle_txn_id';
$handler->display->display_options['fields']['litle_txn_id']['table'] = 'commerce_litle_fraud';
$handler->display->display_options['fields']['litle_txn_id']['field'] = 'litle_txn_id';
/* Field: Commerce Litle Fraud Log: Device Review Status */
$handler->display->display_options['fields']['device_review_status']['id'] = 'device_review_status';
$handler->display->display_options['fields']['device_review_status']['table'] = 'commerce_litle_fraud';
$handler->display->display_options['fields']['device_review_status']['field'] = 'device_review_status';
/* Field: Commerce Litle Fraud Log: Device Reputation Score */
$handler->display->display_options['fields']['device_reputation_score']['id'] = 'device_reputation_score';
$handler->display->display_options['fields']['device_reputation_score']['table'] = 'commerce_litle_fraud';
$handler->display->display_options['fields']['device_reputation_score']['field'] = 'device_reputation_score';
$handler->display->display_options['fields']['device_reputation_score']['separator'] = '';
/* Field: Commerce Order: Order status */
$handler->display->display_options['fields']['status']['id'] = 'status';
$handler->display->display_options['fields']['status']['table'] = 'commerce_order';
$handler->display->display_options['fields']['status']['field'] = 'status';
$handler->display->display_options['fields']['status']['relationship'] = 'order_id';
/* Field: Commerce Order: E-mail */
$handler->display->display_options['fields']['mail']['id'] = 'mail';
$handler->display->display_options['fields']['mail']['table'] = 'commerce_order';
$handler->display->display_options['fields']['mail']['field'] = 'mail';
$handler->display->display_options['fields']['mail']['relationship'] = 'order_id';
$handler->display->display_options['fields']['mail']['render_as_link'] = 0;
/* Field: Commerce Order: Order total */
$handler->display->display_options['fields']['commerce_order_total']['id'] = 'commerce_order_total';
$handler->display->display_options['fields']['commerce_order_total']['table'] = 'field_data_commerce_order_total';
$handler->display->display_options['fields']['commerce_order_total']['field'] = 'commerce_order_total';
$handler->display->display_options['fields']['commerce_order_total']['relationship'] = 'order_id';
$handler->display->display_options['fields']['commerce_order_total']['click_sort_column'] = 'amount';
$handler->display->display_options['fields']['commerce_order_total']['settings'] = array(
  'calculation' => FALSE,
);
/* Sort criterion: Commerce Litle Fraud Log: Order ID */
$handler->display->display_options['sorts']['order_id']['id'] = 'order_id';
$handler->display->display_options['sorts']['order_id']['table'] = 'commerce_litle_fraud';
$handler->display->display_options['sorts']['order_id']['field'] = 'order_id';
$handler->display->display_options['sorts']['order_id']['order'] = 'DESC';
/* Filter criterion: Commerce Litle Fraud Log: Response Message */
$handler->display->display_options['filters']['message']['id'] = 'message';
$handler->display->display_options['filters']['message']['table'] = 'commerce_litle_fraud';
$handler->display->display_options['filters']['message']['field'] = 'message';
$handler->display->display_options['filters']['message']['operator'] = 'contains';
$handler->display->display_options['filters']['message']['exposed'] = TRUE;
$handler->display->display_options['filters']['message']['expose']['operator_id'] = 'message_op';
$handler->display->display_options['filters']['message']['expose']['label'] = 'Response Message';
$handler->display->display_options['filters']['message']['expose']['use_operator'] = TRUE;
$handler->display->display_options['filters']['message']['expose']['operator'] = 'message_op';
$handler->display->display_options['filters']['message']['expose']['identifier'] = 'message';
$handler->display->display_options['filters']['message']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
  5 => 0,
);
$handler->display->display_options['filters']['message']['group_info']['label'] = 'Response Message';
$handler->display->display_options['filters']['message']['group_info']['identifier'] = 'message';
$handler->display->display_options['filters']['message']['group_info']['group_items'] = array(
  1 => array(
    'title' => 'Approved',
    'operator' => '=',
    'value' => 'Approved',
  ),
  2 => array(
    'title' => 'Declined',
    'operator' => '=',
    'value' => 'Declined',
  ),
  3 => array(
    'title' => 'Failed',
    'operator' => '=',
    'value' => 'Failed',
  ),
);
/* Filter criterion: Commerce Litle Fraud Log: Device Review Status */
$handler->display->display_options['filters']['device_review_status']['id'] = 'device_review_status';
$handler->display->display_options['filters']['device_review_status']['table'] = 'commerce_litle_fraud';
$handler->display->display_options['filters']['device_review_status']['field'] = 'device_review_status';
$handler->display->display_options['filters']['device_review_status']['exposed'] = TRUE;
$handler->display->display_options['filters']['device_review_status']['expose']['operator_id'] = 'device_review_status_op';
$handler->display->display_options['filters']['device_review_status']['expose']['label'] = 'Device Review Status';
$handler->display->display_options['filters']['device_review_status']['expose']['operator'] = 'device_review_status_op';
$handler->display->display_options['filters']['device_review_status']['expose']['identifier'] = 'device_review_status';
$handler->display->display_options['filters']['device_review_status']['is_grouped'] = TRUE;
$handler->display->display_options['filters']['device_review_status']['group_info']['label'] = 'Device Review Status';
$handler->display->display_options['filters']['device_review_status']['group_info']['identifier'] = 'device_review_status';
$handler->display->display_options['filters']['device_review_status']['group_info']['group_items'] = array(
  1 => array(
    'title' => 'pass',
    'operator' => '=',
    'value' => 'pass',
  ),
  2 => array(
    'title' => 'fail',
    'operator' => '=',
    'value' => 'fail',
  ),
  3 => array(
    'title' => 'review',
    'operator' => '=',
    'value' => 'review',
  ),
  4 => array(
    'title' => 'unavailable',
    'operator' => '=',
    'value' => 'unavailable',
  ),
  5 => array(
    'title' => 'invalid_session',
    'operator' => '=',
    'value' => 'invalid_session',
  ),
  6 => array(
    'title' => 'unknown_session',
    'operator' => '=',
    'value' => 'unknown_session',
  ),
);

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'springboard/reports/litle-fraud-log';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'Advanced Fraud Log';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['name'] = 'management';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;

  $views['commerce_litle_fraud'] = $view;

   return $views;
  }