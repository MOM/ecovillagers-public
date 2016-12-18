<?php
/**
 * @file
 * Provides default View of log data.
 */

/**
 * Implements hook_views_default_views().
 */
function silverpop_transact_views_default_views() {
  $view = new view();
  $view->name = 'springboard_transact_log';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'silverpop_transact_log';
  $view->human_name = 'Springboard Transact Log';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Silverpop Transact Log';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access springboard dashboard';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'id' => 'id',
    'filename' => 'filename',
    'created' => 'created',
    'model' => 'model',
    'status' => 'status',
    'origin' => 'origin',
    'silverpop_message' => 'silverpop_message',
    'submission_duration' => 'submission_duration',
  );
  $handler->display->display_options['style_options']['default'] = 'id';
  $handler->display->display_options['style_options']['info'] = array(
    'id' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'filename' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'model' => array(
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
    'origin' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'silverpop_message' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'submission_duration' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Bulk operations: Silverpop Transact */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'silverpop_transact_log';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '1';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['row_clickable'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::silverpop_transact_resubmit_xml' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Silverpop Transact: ID */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'silverpop_transact_log';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  /* Field: Silverpop Transact: Filename */
  $handler->display->display_options['fields']['filename']['id'] = 'filename';
  $handler->display->display_options['fields']['filename']['table'] = 'silverpop_transact_log';
  $handler->display->display_options['fields']['filename']['field'] = 'filename';
  /* Field: Silverpop Transact: Last Retry */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'silverpop_transact_log';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Field: Silverpop Transact: Model */
  $handler->display->display_options['fields']['model']['id'] = 'model';
  $handler->display->display_options['fields']['model']['table'] = 'silverpop_transact_log';
  $handler->display->display_options['fields']['model']['field'] = 'model';
  /* Field: Silverpop Transact: Origin */
  $handler->display->display_options['fields']['origin']['id'] = 'origin';
  $handler->display->display_options['fields']['origin']['table'] = 'silverpop_transact_log';
  $handler->display->display_options['fields']['origin']['field'] = 'origin';
  /* Field: Silverpop Transact: Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'silverpop_transact_log';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Submit Status';
  /* Field: Silverpop Transact: Silverpop Message */
  $handler->display->display_options['fields']['silverpop_message']['id'] = 'silverpop_message';
  $handler->display->display_options['fields']['silverpop_message']['table'] = 'silverpop_transact_log';
  $handler->display->display_options['fields']['silverpop_message']['field'] = 'silverpop_message';
  /* Filter criterion: Silverpop Transact: Filename */
  $handler->display->display_options['filters']['filename']['id'] = 'filename';
  $handler->display->display_options['filters']['filename']['table'] = 'silverpop_transact_log';
  $handler->display->display_options['filters']['filename']['field'] = 'filename';
  $handler->display->display_options['filters']['filename']['operator'] = 'contains';
  $handler->display->display_options['filters']['filename']['exposed'] = TRUE;
  $handler->display->display_options['filters']['filename']['expose']['operator_id'] = 'filename_op';
  $handler->display->display_options['filters']['filename']['expose']['label'] = 'Filename';
  $handler->display->display_options['filters']['filename']['expose']['operator'] = 'filename_op';
  $handler->display->display_options['filters']['filename']['expose']['identifier'] = 'filename';
  $handler->display->display_options['filters']['filename']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: Silverpop Transact: ID */
  $handler->display->display_options['filters']['id']['id'] = 'id';
  $handler->display->display_options['filters']['id']['table'] = 'silverpop_transact_log';
  $handler->display->display_options['filters']['id']['field'] = 'id';
  $handler->display->display_options['filters']['id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['id']['expose']['operator_id'] = 'id_op';
  $handler->display->display_options['filters']['id']['expose']['label'] = 'ID';
  $handler->display->display_options['filters']['id']['expose']['operator'] = 'id_op';
  $handler->display->display_options['filters']['id']['expose']['identifier'] = 'id';
  $handler->display->display_options['filters']['id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: Silverpop Transact: Model */
  $handler->display->display_options['filters']['model']['id'] = 'model';
  $handler->display->display_options['filters']['model']['table'] = 'silverpop_transact_log';
  $handler->display->display_options['filters']['model']['field'] = 'model';
  $handler->display->display_options['filters']['model']['exposed'] = TRUE;
  $handler->display->display_options['filters']['model']['expose']['operator_id'] = 'model_op';
  $handler->display->display_options['filters']['model']['expose']['label'] = 'Model';
  $handler->display->display_options['filters']['model']['expose']['operator'] = 'model_op';
  $handler->display->display_options['filters']['model']['expose']['identifier'] = 'model';
  $handler->display->display_options['filters']['model']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: Silverpop Transact: Origin */
  $handler->display->display_options['filters']['origin']['id'] = 'origin';
  $handler->display->display_options['filters']['origin']['table'] = 'silverpop_transact_log';
  $handler->display->display_options['filters']['origin']['field'] = 'origin';
  $handler->display->display_options['filters']['origin']['exposed'] = TRUE;
  $handler->display->display_options['filters']['origin']['expose']['operator_id'] = 'origin_op';
  $handler->display->display_options['filters']['origin']['expose']['label'] = 'Origin';
  $handler->display->display_options['filters']['origin']['expose']['operator'] = 'origin_op';
  $handler->display->display_options['filters']['origin']['expose']['identifier'] = 'origin';
  $handler->display->display_options['filters']['origin']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: Silverpop Transact: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'silverpop_transact_log';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Status';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: Silverpop Transact: Silverpop Message */
  $handler->display->display_options['filters']['silverpop_message']['id'] = 'silverpop_message';
  $handler->display->display_options['filters']['silverpop_message']['table'] = 'silverpop_transact_log';
  $handler->display->display_options['filters']['silverpop_message']['field'] = 'silverpop_message';
  $handler->display->display_options['filters']['silverpop_message']['exposed'] = TRUE;
  $handler->display->display_options['filters']['silverpop_message']['expose']['operator_id'] = 'silverpop_message_op';
  $handler->display->display_options['filters']['silverpop_message']['expose']['label'] = 'Silverpop Message';
  $handler->display->display_options['filters']['silverpop_message']['expose']['operator'] = 'silverpop_message_op';
  $handler->display->display_options['filters']['silverpop_message']['expose']['identifier'] = 'silverpop_message';
  $handler->display->display_options['filters']['silverpop_message']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/springboard/reports/silverpop-transact-log';
  $handler->display->display_options['menu']['title'] = 'Silverpop Transact Log';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  $views[$view->name] = $view;
  return $views;
}
