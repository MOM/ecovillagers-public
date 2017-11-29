<?php
/**
 * @file
 * Provides default view configurations.
 */

/**
 * Implements hook_views_default_views().
 */
function springboard_dw_views_default_views() {
  $views = array();



  // springboard_dw_donation_stats_report
  $view = new view();
  $view->name = 'springboard_dw_donation_stats_report';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'sp_dw_donation_stats_psudo';
  $view->human_name = 'Springboard DW Donation Statistics';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Lifetime Performance';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer springboard';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'Performance statistics are unavailable at this time.';
  $handler->display->display_options['empty']['area']['format'] = 'raw_html';
  /* Field: Springboard DW Donation Stats: Total Amount Donated */
  $handler->display->display_options['fields']['raised']['id'] = 'raised';
  $handler->display->display_options['fields']['raised']['table'] = 'sp_dw_donation_stats_psudo';
  $handler->display->display_options['fields']['raised']['field'] = 'raised';
  $handler->display->display_options['fields']['raised']['label'] = 'raised *';
  $handler->display->display_options['fields']['raised']['element_label_colon'] = FALSE;
  /* Field: Springboard DW Donation Stats: Total Donations */
  $handler->display->display_options['fields']['gifts']['id'] = 'gifts';
  $handler->display->display_options['fields']['gifts']['table'] = 'sp_dw_donation_stats_psudo';
  $handler->display->display_options['fields']['gifts']['field'] = 'gifts';
  $handler->display->display_options['fields']['gifts']['label'] = 'donations received *';
  $handler->display->display_options['fields']['gifts']['element_label_colon'] = FALSE;
  /* Field: Springboard DW Donation Stats: Total Recurring Donations */
  $handler->display->display_options['fields']['sustainers']['id'] = 'sustainers';
  $handler->display->display_options['fields']['sustainers']['table'] = 'sp_dw_donation_stats_psudo';
  $handler->display->display_options['fields']['sustainers']['field'] = 'sustainers';
  $handler->display->display_options['fields']['sustainers']['label'] = 'sustainers generated **';
  $handler->display->display_options['fields']['sustainers']['element_label_colon'] = FALSE;
  /* Field: Springboard DW Donation Stats: Total First Time Donations */
  $handler->display->display_options['fields']['first_time_donors']['id'] = 'first_time_donors';
  $handler->display->display_options['fields']['first_time_donors']['table'] = 'sp_dw_donation_stats_psudo';
  $handler->display->display_options['fields']['first_time_donors']['field'] = 'first_time_donors';
  $handler->display->display_options['fields']['first_time_donors']['label'] = 'first time Springboard donors';
  $handler->display->display_options['fields']['first_time_donors']['element_label_colon'] = FALSE;
  /* Field: Springboard DW Donation Stats: First Donation ID */
  $handler->display->display_options['fields']['first_donation_id']['id'] = 'first_donation_id';
  $handler->display->display_options['fields']['first_donation_id']['table'] = 'sp_dw_donation_stats_psudo';
  $handler->display->display_options['fields']['first_donation_id']['field'] = 'first_donation_id';
  $handler->display->display_options['fields']['first_donation_id']['label'] = '';
  $handler->display->display_options['fields']['first_donation_id']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['first_donation_id']['alter']['text'] = 'First submission received';
  $handler->display->display_options['fields']['first_donation_id']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['first_donation_id']['alter']['path'] = 'warehouse/reports/donations/[first_donation_id]';
  $handler->display->display_options['fields']['first_donation_id']['element_label_colon'] = FALSE;
  /* Field: Springboard DW Donation Stats: Latest Donation ID */
  $handler->display->display_options['fields']['latest_donation_id']['id'] = 'latest_donation_id';
  $handler->display->display_options['fields']['latest_donation_id']['table'] = 'sp_dw_donation_stats_psudo';
  $handler->display->display_options['fields']['latest_donation_id']['field'] = 'latest_donation_id';
  $handler->display->display_options['fields']['latest_donation_id']['label'] = '';
  $handler->display->display_options['fields']['latest_donation_id']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['latest_donation_id']['alter']['text'] = 'Latest submission received';
  $handler->display->display_options['fields']['latest_donation_id']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['latest_donation_id']['alter']['path'] = 'warehouse/reports/donations/[latest_donation_id]';
  $handler->display->display_options['fields']['latest_donation_id']['element_label_colon'] = FALSE;
  /* Field: Springboard DW Donation Stats: Latest fetch */
  $handler->display->display_options['fields']['latest_fetch']['id'] = 'latest_fetch';
  $handler->display->display_options['fields']['latest_fetch']['table'] = 'sp_dw_donation_stats_psudo';
  $handler->display->display_options['fields']['latest_fetch']['field'] = 'latest_fetch';
  $handler->display->display_options['fields']['latest_fetch']['label'] = '';
  $handler->display->display_options['fields']['latest_fetch']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['latest_fetch']['alter']['text'] = 'updated [latest_fetch] ago';
  $handler->display->display_options['fields']['latest_fetch']['element_label_colon'] = FALSE;
  /* Field: Springboard DW Donation Stats: Node Status */
  $handler->display->display_options['fields']['node_status']['id'] = 'node_status';
  $handler->display->display_options['fields']['node_status']['table'] = 'sp_dw_donation_stats_psudo';
  $handler->display->display_options['fields']['node_status']['field'] = 'node_status';
  $handler->display->display_options['fields']['node_status']['label'] = '';
  $handler->display->display_options['fields']['node_status']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['node_status']['alter']['text'] = '<div id="dw-stats-node-status-inner-wrapper">Current status: [node_status]</div>
    <div id="dw-stats-lower-help-text">
      * successful one-time donations & initial sustainer payments<br />
      ** including upsell donations
    </div>';
  $handler->display->display_options['fields']['node_status']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['node_status']['hide_empty'] = TRUE;
  /* Contextual filter: Springboard DW Donation Stats: Donation ID */
  $handler->display->display_options['arguments']['donation_id']['id'] = 'donation_id';
  $handler->display->display_options['arguments']['donation_id']['table'] = 'sp_dw_donation_stats_psudo';
  $handler->display->display_options['arguments']['donation_id']['field'] = 'donation_id';
  $handler->display->display_options['arguments']['donation_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['donation_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['donation_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['donation_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['donation_id']['summary_options']['items_per_page'] = '25';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');

  $views[$view->name] = $view;
  // end springboard_dw_donation_stats_report


  // springboard_dw_action_stats_report
  $view = new view();
  $view->name = 'springboard_dw_action_stats_report';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'sp_dw_advocacy_stats_psudo';
  $view->human_name = 'Springboard DW Action Statistics';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Lifetime Performance';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Springboard DW Advocacy Stats: First Action ID */
  $handler->display->display_options['fields']['first_action_id']['id'] = 'first_action_id';
  $handler->display->display_options['fields']['first_action_id']['table'] = 'sp_dw_advocacy_stats_psudo';
  $handler->display->display_options['fields']['first_action_id']['field'] = 'first_action_id';
  $handler->display->display_options['fields']['first_action_id']['exclude'] = TRUE;
  /* Field: Springboard DW Advocacy Stats: Latest Action ID */
  $handler->display->display_options['fields']['latest_action_id']['id'] = 'latest_action_id';
  $handler->display->display_options['fields']['latest_action_id']['table'] = 'sp_dw_advocacy_stats_psudo';
  $handler->display->display_options['fields']['latest_action_id']['field'] = 'latest_action_id';
  $handler->display->display_options['fields']['latest_action_id']['exclude'] = TRUE;
  /* Field: Springboard DW Advocacy Stats: Actions Count */
  $handler->display->display_options['fields']['actions_count']['id'] = 'actions_count';
  $handler->display->display_options['fields']['actions_count']['table'] = 'sp_dw_advocacy_stats_psudo';
  $handler->display->display_options['fields']['actions_count']['field'] = 'actions_count';
  $handler->display->display_options['fields']['actions_count']['label'] = 'actions taken';
  $handler->display->display_options['fields']['actions_count']['element_label_colon'] = FALSE;
  /* Field: Springboard DW Advocacy Stats: Messages Count */
  $handler->display->display_options['fields']['messages_count']['id'] = 'messages_count';
  $handler->display->display_options['fields']['messages_count']['table'] = 'sp_dw_advocacy_stats_psudo';
  $handler->display->display_options['fields']['messages_count']['field'] = 'messages_count';
  $handler->display->display_options['fields']['messages_count']['label'] = 'messages generated';
  $handler->display->display_options['fields']['messages_count']['element_label_colon'] = FALSE;
  /* Field: Springboard DW Advocacy Stats: New Contacts */
  $handler->display->display_options['fields']['new_contacts']['id'] = 'new_contacts';
  $handler->display->display_options['fields']['new_contacts']['table'] = 'sp_dw_advocacy_stats_psudo';
  $handler->display->display_options['fields']['new_contacts']['field'] = 'new_contacts';
  $handler->display->display_options['fields']['new_contacts']['label'] = 'new Springboard contacts';
  $handler->display->display_options['fields']['new_contacts']['element_label_colon'] = FALSE;
  /* Contextual filter: Springboard DW Advocacy Stats: Form ID */
  $handler->display->display_options['arguments']['form_id']['id'] = 'form_id';
  $handler->display->display_options['arguments']['form_id']['table'] = 'sp_dw_advocacy_stats_psudo';
  $handler->display->display_options['arguments']['form_id']['field'] = 'form_id';
  $handler->display->display_options['arguments']['form_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['form_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['form_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['form_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['form_id']['summary_options']['items_per_page'] = '25';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');

  $views[$view->name] = $view;
  // end springboard_dw_action_stats_report

  // springboard_dw_donations_report:
  $view = new view();
  $view->name = 'springboard_dw_donations_report';
  $view->description = 'Fetches donation reports from the external data warehouse.';
  $view->tag = 'default';
  $view->base_table = 'sp_dw_donations_psudo';
  $view->human_name = 'Springboard DW Donations Report';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'All-Time Donations';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer fundraiser';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Go';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'lite';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '3';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '20, 50, 100';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'donation_id' => 'donation_id',
    'created_at' => 'created_at',
    'amount' => 'amount',
    'status' => 'status',
    'gateway' => 'gateway',
    'first_name' => 'first_name',
    'last_name' => 'last_name',
    'email' => 'email',
    'form_name' => 'form_name',
    'form_url' => 'form_url',
    'recurs_monthly' => 'recurs_monthly',
    'payment_link' => 'payment_link',
  );
  $handler->display->display_options['style_options']['default'] = 'created_at';
  $handler->display->display_options['style_options']['info'] = array(
    'donation_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created_at' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'amount' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'gateway' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'first_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'email' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'form_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'form_url' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'recurs_monthly' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'payment_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<div id="dw-directions-blurb">Review and search all donation data in the Springboard Data Warehouse. Click the columns to sort. To filter, enter criteria and click Go. It may take a few minutes for donation data to appear.</div>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No donations were returned for your search.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Field: Springboard DW Donations: Donation ID */
  $handler->display->display_options['fields']['donation_id']['id'] = 'donation_id';
  $handler->display->display_options['fields']['donation_id']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['donation_id']['field'] = 'donation_id';
  $handler->display->display_options['fields']['donation_id']['label'] = 'Order ID';
  $handler->display->display_options['fields']['donation_id']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['donation_id']['alter']['path'] = 'warehouse/reports/donations/[donation_id]';
  /* Field: Springboard DW Donations: Created At */
  $handler->display->display_options['fields']['created_at']['id'] = 'created_at';
  $handler->display->display_options['fields']['created_at']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['created_at']['field'] = 'created_at';
  $handler->display->display_options['fields']['created_at']['label'] = 'Date';
  $handler->display->display_options['fields']['created_at']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created_at']['custom_date_format'] = 'n/j/Y - G:ia';
  $handler->display->display_options['fields']['created_at']['second_date_format'] = 'long';
  /* Field: Springboard DW Donations: Donation Amount */
  $handler->display->display_options['fields']['amount']['id'] = 'amount';
  $handler->display->display_options['fields']['amount']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['amount']['field'] = 'amount';
  $handler->display->display_options['fields']['amount']['label'] = 'Amount';
  /* Field: Springboard DW Donations: Transaction Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Order Status';
  /* Field: Springboard DW Donations: Gateway */
  $handler->display->display_options['fields']['gateway']['id'] = 'gateway';
  $handler->display->display_options['fields']['gateway']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['gateway']['field'] = 'gateway';
  /* Field: Springboard DW Donations: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['exclude'] = TRUE;
  /* Field: Springboard DW Donations: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['label'] = 'Name';
  $handler->display->display_options['fields']['last_name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['last_name']['alter']['text'] = '[first_name] [last_name]';
  $handler->display->display_options['fields']['last_name']['alter']['trim_whitespace'] = TRUE;
  /* Field: Springboard DW Donations: Email Address */
  $handler->display->display_options['fields']['email']['id'] = 'email';
  $handler->display->display_options['fields']['email']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['email']['field'] = 'email';
  $handler->display->display_options['fields']['email']['label'] = 'Email';
  $handler->display->display_options['fields']['email']['alter']['path'] = 'springboard/reports/dw/donations/[donation_id]';
  /* Field: Springboard DW Donations: Form Name */
  $handler->display->display_options['fields']['form_name']['id'] = 'form_name';
  $handler->display->display_options['fields']['form_name']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['form_name']['field'] = 'form_name';
  $handler->display->display_options['fields']['form_name']['label'] = '';
  $handler->display->display_options['fields']['form_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['form_name']['element_label_colon'] = FALSE;
  /* Field: Springboard DW Donations: Form URL */
  $handler->display->display_options['fields']['form_url']['id'] = 'form_url';
  $handler->display->display_options['fields']['form_url']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['form_url']['field'] = 'form_url';
  $handler->display->display_options['fields']['form_url']['label'] = 'Form';
  $handler->display->display_options['fields']['form_url']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['form_url']['alter']['text'] = '<a href="[form_url]" class="webform-link">[form_name]</a>';
  $handler->display->display_options['fields']['form_url']['empty'] = '[form_name]';
  /* Field: Springboard DW Donations: Recurs Monthly */
  $handler->display->display_options['fields']['recurs_monthly']['id'] = 'recurs_monthly';
  $handler->display->display_options['fields']['recurs_monthly']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['recurs_monthly']['field'] = 'recurs_monthly';
  $handler->display->display_options['fields']['recurs_monthly']['label'] = 'Recurs';
  /* Field: Springboard DW Donations: Payment */
  $handler->display->display_options['fields']['payment_link']['id'] = 'payment_link';
  $handler->display->display_options['fields']['payment_link']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['payment_link']['field'] = 'payment_link';
  /* Sort criterion: Springboard DW Donations: Transaction ID */
  $handler->display->display_options['sorts']['transaction_id']['id'] = 'transaction_id';
  $handler->display->display_options['sorts']['transaction_id']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['sorts']['transaction_id']['field'] = 'transaction_id';
  /* Filter criterion: Springboard DW Donations: Transaction Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['group'] = 1;
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
    6 => 0,
  );
  /* Filter criterion: Springboard DW Donations: Donation Amount */
  $handler->display->display_options['filters']['amount']['id'] = 'amount';
  $handler->display->display_options['filters']['amount']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['filters']['amount']['field'] = 'amount';
  $handler->display->display_options['filters']['amount']['group'] = 1;
  $handler->display->display_options['filters']['amount']['exposed'] = TRUE;
  $handler->display->display_options['filters']['amount']['expose']['operator_id'] = 'amount_op';
  $handler->display->display_options['filters']['amount']['expose']['label'] = 'Donation Amount';
  $handler->display->display_options['filters']['amount']['expose']['operator'] = 'amount_op';
  $handler->display->display_options['filters']['amount']['expose']['identifier'] = 'amount';
  $handler->display->display_options['filters']['amount']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Springboard DW Donations: Gateway */
  $handler->display->display_options['filters']['gateway']['id'] = 'gateway';
  $handler->display->display_options['filters']['gateway']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['filters']['gateway']['field'] = 'gateway';
  $handler->display->display_options['filters']['gateway']['operator'] = 'contains';
  $handler->display->display_options['filters']['gateway']['group'] = 1;
  $handler->display->display_options['filters']['gateway']['exposed'] = TRUE;
  $handler->display->display_options['filters']['gateway']['expose']['operator_id'] = 'gateway_op';
  $handler->display->display_options['filters']['gateway']['expose']['label'] = 'Gateway';
  $handler->display->display_options['filters']['gateway']['expose']['operator'] = 'gateway_op';
  $handler->display->display_options['filters']['gateway']['expose']['identifier'] = 'gateway';
  $handler->display->display_options['filters']['gateway']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Springboard DW Donations: First Name */
  $handler->display->display_options['filters']['first_name']['id'] = 'first_name';
  $handler->display->display_options['filters']['first_name']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['filters']['first_name']['field'] = 'first_name';
  $handler->display->display_options['filters']['first_name']['operator'] = 'contains';
  $handler->display->display_options['filters']['first_name']['group'] = 1;
  $handler->display->display_options['filters']['first_name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['first_name']['expose']['operator_id'] = 'first_name_op';
  $handler->display->display_options['filters']['first_name']['expose']['label'] = 'First Name';
  $handler->display->display_options['filters']['first_name']['expose']['operator'] = 'first_name_op';
  $handler->display->display_options['filters']['first_name']['expose']['identifier'] = 'first_name';
  $handler->display->display_options['filters']['first_name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Springboard DW Donations: Last Name */
  $handler->display->display_options['filters']['last_name']['id'] = 'last_name';
  $handler->display->display_options['filters']['last_name']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['filters']['last_name']['field'] = 'last_name';
  $handler->display->display_options['filters']['last_name']['operator'] = 'contains';
  $handler->display->display_options['filters']['last_name']['group'] = 1;
  $handler->display->display_options['filters']['last_name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['last_name']['expose']['operator_id'] = 'last_name_op';
  $handler->display->display_options['filters']['last_name']['expose']['label'] = 'Last Name';
  $handler->display->display_options['filters']['last_name']['expose']['operator'] = 'last_name_op';
  $handler->display->display_options['filters']['last_name']['expose']['identifier'] = 'last_name';
  $handler->display->display_options['filters']['last_name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Springboard DW Donations: Form Name */
  $handler->display->display_options['filters']['form_name']['id'] = 'form_name';
  $handler->display->display_options['filters']['form_name']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['filters']['form_name']['field'] = 'form_name';
  $handler->display->display_options['filters']['form_name']['operator'] = 'contains';
  $handler->display->display_options['filters']['form_name']['group'] = 1;
  $handler->display->display_options['filters']['form_name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['form_name']['expose']['operator_id'] = 'form_name_op';
  $handler->display->display_options['filters']['form_name']['expose']['label'] = 'Form Name';
  $handler->display->display_options['filters']['form_name']['expose']['operator'] = 'form_name_op';
  $handler->display->display_options['filters']['form_name']['expose']['identifier'] = 'form_name';
  $handler->display->display_options['filters']['form_name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Springboard DW Donations: Donation ID */
  $handler->display->display_options['filters']['donation_id']['id'] = 'donation_id';
  $handler->display->display_options['filters']['donation_id']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['filters']['donation_id']['field'] = 'donation_id';
  $handler->display->display_options['filters']['donation_id']['group'] = 1;
  $handler->display->display_options['filters']['donation_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['donation_id']['expose']['operator_id'] = 'donation_id_op';
  $handler->display->display_options['filters']['donation_id']['expose']['label'] = 'Order ID';
  $handler->display->display_options['filters']['donation_id']['expose']['operator'] = 'donation_id_op';
  $handler->display->display_options['filters']['donation_id']['expose']['identifier'] = 'donation_id';
  $handler->display->display_options['filters']['donation_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Springboard DW Donations: Email Address */
  $handler->display->display_options['filters']['email']['id'] = 'email';
  $handler->display->display_options['filters']['email']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['filters']['email']['field'] = 'email';
  $handler->display->display_options['filters']['email']['operator'] = 'contains';
  $handler->display->display_options['filters']['email']['group'] = 1;
  $handler->display->display_options['filters']['email']['exposed'] = TRUE;
  $handler->display->display_options['filters']['email']['expose']['operator_id'] = 'email_op';
  $handler->display->display_options['filters']['email']['expose']['label'] = 'Email Address';
  $handler->display->display_options['filters']['email']['expose']['operator'] = 'email_op';
  $handler->display->display_options['filters']['email']['expose']['identifier'] = 'email';
  $handler->display->display_options['filters']['email']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Springboard DW Donations: Transaction Date */
  $handler->display->display_options['filters']['transaction_date']['id'] = 'transaction_date';
  $handler->display->display_options['filters']['transaction_date']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['filters']['transaction_date']['field'] = 'transaction_date';
  $handler->display->display_options['filters']['transaction_date']['operator'] = 'between';
  $handler->display->display_options['filters']['transaction_date']['group'] = 1;
  $handler->display->display_options['filters']['transaction_date']['exposed'] = TRUE;
  $handler->display->display_options['filters']['transaction_date']['expose']['operator_id'] = 'transaction_date_op';
  $handler->display->display_options['filters']['transaction_date']['expose']['label'] = 'Donation date between:';
  $handler->display->display_options['filters']['transaction_date']['expose']['operator'] = 'transaction_date_op';
  $handler->display->display_options['filters']['transaction_date']['expose']['identifier'] = 'transaction_date';
  $handler->display->display_options['filters']['transaction_date']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['transaction_date']['form_type'] = 'date_popup';
  $handler->display->display_options['filters']['transaction_date']['year_range'] = '-100:+100';
  $handler->display->display_options['filters']['transaction_date']['date_fields'] = array(
    'transaction_date' => 'transaction_date',
  );

  /* Display: Donations List */
  $handler = $view->new_display('page', 'Donations List', 'page');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '20, 50, 100';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹‹';
  $handler->display->display_options['pager']['options']['tags']['next'] = '››';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Springboard DW Donations: Created At */
  $handler->display->display_options['sorts']['created_at']['id'] = 'created_at';
  $handler->display->display_options['sorts']['created_at']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['sorts']['created_at']['field'] = 'created_at';
  $handler->display->display_options['sorts']['created_at']['order'] = 'DESC';
  $handler->display->display_options['path'] = 'warehouse/reports/donations';
  $handler->display->display_options['menu']['title'] = 'All-Time Donations';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'springboard_admin_menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: Donation Details */
  $handler = $view->new_display('page', 'Donation Details', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Donation Details';
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'dw-donation-detail';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Transaction';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing']['element_wrapper_class'] = 'section-label';
  /* Field: Springboard DW Donations: Donation Amount */
  $handler->display->display_options['fields']['amount']['id'] = 'amount';
  $handler->display->display_options['fields']['amount']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['amount']['field'] = 'amount';
  $handler->display->display_options['fields']['amount']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: Donation ID */
  $handler->display->display_options['fields']['donation_id']['id'] = 'donation_id';
  $handler->display->display_options['fields']['donation_id']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['donation_id']['field'] = 'donation_id';
  $handler->display->display_options['fields']['donation_id']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: Transaction ID */
  $handler->display->display_options['fields']['transaction_id']['id'] = 'transaction_id';
  $handler->display->display_options['fields']['transaction_id']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['transaction_id']['field'] = 'transaction_id';
  $handler->display->display_options['fields']['transaction_id']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: Created At */
  $handler->display->display_options['fields']['created_at']['id'] = 'created_at';
  $handler->display->display_options['fields']['created_at']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['created_at']['field'] = 'created_at';
  $handler->display->display_options['fields']['created_at']['label'] = 'Donation Date';
  $handler->display->display_options['fields']['created_at']['empty'] = '<span class="no-result-returned">N/A</span>';
  $handler->display->display_options['fields']['created_at']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created_at']['custom_date_format'] = 'n/j/Y - G:i';
  $handler->display->display_options['fields']['created_at']['second_date_format'] = 'long';
  /* Field: Springboard DW Donations: Donation Form ID */
  $handler->display->display_options['fields']['donation_form_id']['id'] = 'donation_form_id';
  $handler->display->display_options['fields']['donation_form_id']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['donation_form_id']['field'] = 'donation_form_id';
  $handler->display->display_options['fields']['donation_form_id']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: Recurs Monthly */
  $handler->display->display_options['fields']['recurs_monthly']['id'] = 'recurs_monthly';
  $handler->display->display_options['fields']['recurs_monthly']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['recurs_monthly']['field'] = 'recurs_monthly';
  $handler->display->display_options['fields']['recurs_monthly']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['label'] = 'Contact';
  $handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing_1']['element_wrapper_class'] = 'section-label';
  /* Field: Springboard DW Donations: Contact ID */
  $handler->display->display_options['fields']['contact_id']['id'] = 'contact_id';
  $handler->display->display_options['fields']['contact_id']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['contact_id']['field'] = 'contact_id';
  $handler->display->display_options['fields']['contact_id']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: Email Address */
  $handler->display->display_options['fields']['email']['id'] = 'email';
  $handler->display->display_options['fields']['email']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['email']['field'] = 'email';
  $handler->display->display_options['fields']['email']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: Mailing Address */
  $handler->display->display_options['fields']['address']['id'] = 'address';
  $handler->display->display_options['fields']['address']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['address']['field'] = 'address';
  $handler->display->display_options['fields']['address']['label'] = 'Address';
  $handler->display->display_options['fields']['address']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: Mailing Address - Line 2 */
  $handler->display->display_options['fields']['address_line_2']['id'] = 'address_line_2';
  $handler->display->display_options['fields']['address_line_2']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['address_line_2']['field'] = 'address_line_2';
  $handler->display->display_options['fields']['address_line_2']['label'] = 'Address 2';
  $handler->display->display_options['fields']['address_line_2']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: City */
  $handler->display->display_options['fields']['city']['id'] = 'city';
  $handler->display->display_options['fields']['city']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['city']['field'] = 'city';
  $handler->display->display_options['fields']['city']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: State */
  $handler->display->display_options['fields']['state']['id'] = 'state';
  $handler->display->display_options['fields']['state']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['state']['field'] = 'state';
  $handler->display->display_options['fields']['state']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: Zip/Postal Code */
  $handler->display->display_options['fields']['zip']['id'] = 'zip';
  $handler->display->display_options['fields']['zip']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['zip']['field'] = 'zip';
  $handler->display->display_options['fields']['zip']['label'] = 'Postal Code';
  $handler->display->display_options['fields']['zip']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: Country */
  $handler->display->display_options['fields']['country']['id'] = 'country';
  $handler->display->display_options['fields']['country']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['country']['field'] = 'country';
  $handler->display->display_options['fields']['country']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_2']['id'] = 'nothing_2';
  $handler->display->display_options['fields']['nothing_2']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_2']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_2']['label'] = 'Payment';
  $handler->display->display_options['fields']['nothing_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing_2']['element_wrapper_class'] = 'section-label';
  /* Field: Springboard DW Donations: Gateway */
  $handler->display->display_options['fields']['gateway']['id'] = 'gateway';
  $handler->display->display_options['fields']['gateway']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['gateway']['field'] = 'gateway';
  $handler->display->display_options['fields']['gateway']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: Payment Method */
  $handler->display->display_options['fields']['payment_method']['id'] = 'payment_method';
  $handler->display->display_options['fields']['payment_method']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['payment_method']['field'] = 'payment_method';
  $handler->display->display_options['fields']['payment_method']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: Card Last 4 */
  $handler->display->display_options['fields']['card_last_4']['id'] = 'card_last_4';
  $handler->display->display_options['fields']['card_last_4']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['card_last_4']['field'] = 'card_last_4';
  $handler->display->display_options['fields']['card_last_4']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: Credit Card Type */
  $handler->display->display_options['fields']['card_type']['id'] = 'card_type';
  $handler->display->display_options['fields']['card_type']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['card_type']['field'] = 'card_type';
  $handler->display->display_options['fields']['card_type']['label'] = 'Card Type';
  $handler->display->display_options['fields']['card_type']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: Card Expiration Month */
  $handler->display->display_options['fields']['card_expiration_month']['id'] = 'card_expiration_month';
  $handler->display->display_options['fields']['card_expiration_month']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['card_expiration_month']['field'] = 'card_expiration_month';
  $handler->display->display_options['fields']['card_expiration_month']['label'] = 'Card Exp. Month';
  $handler->display->display_options['fields']['card_expiration_month']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: Card Expiration Year */
  $handler->display->display_options['fields']['card_expiration_year']['id'] = 'card_expiration_year';
  $handler->display->display_options['fields']['card_expiration_year']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['card_expiration_year']['field'] = 'card_expiration_year';
  $handler->display->display_options['fields']['card_expiration_year']['label'] = 'Card Exp. Year';
  $handler->display->display_options['fields']['card_expiration_year']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: Bank Account Mask */
  $handler->display->display_options['fields']['bank_account_mask']['id'] = 'bank_account_mask';
  $handler->display->display_options['fields']['bank_account_mask']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['bank_account_mask']['field'] = 'bank_account_mask';
  $handler->display->display_options['fields']['bank_account_mask']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_3']['id'] = 'nothing_3';
  $handler->display->display_options['fields']['nothing_3']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_3']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_3']['label'] = 'Additional Information';
  $handler->display->display_options['fields']['nothing_3']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing_3']['element_wrapper_class'] = 'section-label';
  /* Field: Springboard DW Donations: MS */
  $handler->display->display_options['fields']['ms']['id'] = 'ms';
  $handler->display->display_options['fields']['ms']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['ms']['field'] = 'ms';
  $handler->display->display_options['fields']['ms']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: Extra Props Data */
  $handler->display->display_options['fields']['extra_props']['id'] = 'extra_props';
  $handler->display->display_options['fields']['extra_props']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['extra_props']['field'] = 'extra_props';
  $handler->display->display_options['fields']['extra_props']['label'] = 'Extra Props';
  $handler->display->display_options['fields']['extra_props']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: Currency */
  $handler->display->display_options['fields']['currency']['id'] = 'currency';
  $handler->display->display_options['fields']['currency']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['currency']['field'] = 'currency';
  $handler->display->display_options['fields']['currency']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: IP Address */
  $handler->display->display_options['fields']['ip_address']['id'] = 'ip_address';
  $handler->display->display_options['fields']['ip_address']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['ip_address']['field'] = 'ip_address';
  $handler->display->display_options['fields']['ip_address']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: Click Submit */
  $handler->display->display_options['fields']['click_submit']['id'] = 'click_submit';
  $handler->display->display_options['fields']['click_submit']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['click_submit']['field'] = 'click_submit';
  $handler->display->display_options['fields']['click_submit']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: Initial Referred URL */
  $handler->display->display_options['fields']['initial_referrer']['id'] = 'initial_referrer';
  $handler->display->display_options['fields']['initial_referrer']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['initial_referrer']['field'] = 'initial_referrer';
  $handler->display->display_options['fields']['initial_referrer']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: cid */
  $handler->display->display_options['fields']['cid']['id'] = 'cid';
  $handler->display->display_options['fields']['cid']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['cid']['field'] = 'cid';
  $handler->display->display_options['fields']['cid']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: Unique ID */
  $handler->display->display_options['fields']['unique_id']['id'] = 'unique_id';
  $handler->display->display_options['fields']['unique_id']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['unique_id']['field'] = 'unique_id';
  $handler->display->display_options['fields']['unique_id']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: Device Browser */
  $handler->display->display_options['fields']['device_browser']['id'] = 'device_browser';
  $handler->display->display_options['fields']['device_browser']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['device_browser']['field'] = 'device_browser';
  $handler->display->display_options['fields']['device_browser']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: Device Name */
  $handler->display->display_options['fields']['device_name']['id'] = 'device_name';
  $handler->display->display_options['fields']['device_name']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['device_name']['field'] = 'device_name';
  $handler->display->display_options['fields']['device_name']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: Device OS */
  $handler->display->display_options['fields']['device_os']['id'] = 'device_os';
  $handler->display->display_options['fields']['device_os']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['device_os']['field'] = 'device_os';
  $handler->display->display_options['fields']['device_os']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: Device Type */
  $handler->display->display_options['fields']['device_type']['id'] = 'device_type';
  $handler->display->display_options['fields']['device_type']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['device_type']['field'] = 'device_type';
  $handler->display->display_options['fields']['device_type']['empty'] = '<span class="no-result-returned">N/A</span>';
  /* Field: Springboard DW Donations: User Agent */
  $handler->display->display_options['fields']['user_agent']['id'] = 'user_agent';
  $handler->display->display_options['fields']['user_agent']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['fields']['user_agent']['field'] = 'user_agent';
  $handler->display->display_options['fields']['user_agent']['empty'] = '<span class="no-result-returned">N/A</span>';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Springboard DW Donations: Donation ID */
  $handler->display->display_options['arguments']['donation_id']['id'] = 'donation_id';
  $handler->display->display_options['arguments']['donation_id']['table'] = 'sp_dw_donations_psudo';
  $handler->display->display_options['arguments']['donation_id']['field'] = 'donation_id';
  $handler->display->display_options['arguments']['donation_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['donation_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['donation_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['donation_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['donation_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  $handler->display->display_options['path'] = 'warehouse/reports/donations/%';

  $views[$view->name] = $view;
  // End springboard_dw_donations_report view.

  return $views;
}
