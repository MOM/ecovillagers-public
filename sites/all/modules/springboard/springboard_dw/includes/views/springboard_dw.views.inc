<?php

/**
 * @file
 * Defines Springboard Data Warehouse Views.
 */

/**
 * Implements hook_views_data().
 *
 * Defines pseudo-DB tables for creating views that fetch their data from the remote data warehouse.
 */
function springboard_dw_views_data() {
  // Define a view type which displays advocacy lifetime performance data fetched from the warehouse:
  $data['sp_dw_advocacy_stats_psudo']['table'] = array(
    'group' => t('Springboard DW Advocacy Stats'),
    'base' => array(
      'title' => t('Springboard DW Advocacy Stats'),
      'help' => t('Fetches lifetime performance statistics from the data warehouse for a single advocacy form.'),
      'query class' => 'springboard_dw_advocacy_stats_views_plugin_query',
    ),
  );
  // Define the fields:
  $data['sp_dw_advocacy_stats_psudo']['actions_count'] = array(
    'title' => t('Actions Count'),
    'help' => t('Fetches the total number of actions taken for this advocacy form.'),
    'field' => array(
      'handler' => 'springboard_dw_views_handler_field',
    ),
  );
  $data['sp_dw_advocacy_stats_psudo']['messages_count'] = array(
    'title' => t('Messages Count'),
    'help' => t('Fetches the total number of messages generated for this advocacy form.'),
    'field' => array(
      'handler' => 'springboard_dw_views_handler_field',
    ),
  );
  $data['sp_dw_advocacy_stats_psudo']['new_contacts'] = array(
    'title' => t('New Contacts'),
    'help' => t('Fetches the total number of new contacts for this advocacy form.'),
    'field' => array(
      'handler' => 'springboard_dw_views_handler_field',
    ),
  );
  $data['sp_dw_advocacy_stats_psudo']['first_action_date'] = array(
    'title' => t('First Action Date'),
    'help' => t('Fetches the date of the first submission for this advocacy form.'),
    'field' => array(
      'handler' => 'springboard_dw_views_handler_field',
    ),
  );
  $data['sp_dw_advocacy_stats_psudo']['latest_action_date'] = array(
    'title' => t('Latest Action Date'),
    'help' => t('Fetches the date of the most recent submission for this advocacy form.'),
    'field' => array(
      'handler' => 'springboard_dw_views_handler_field',
    ),
  );
  $data['sp_dw_advocacy_stats_psudo']['first_action_id'] = array(
    'title' => t('First Action ID'),
    'help' => t('Fetches the id of the first action for this advocacy form.'),
    'field' => array(
      'handler' => 'springboard_dw_views_handler_field',
    ),
  );
  $data['sp_dw_advocacy_stats_psudo']['latest_action_id'] = array(
    'title' => t('Latest Action ID'),
    'help' => t('Fetches the id of the most recent action for this advocacy form.'),
    'field' => array(
      'handler' => 'springboard_dw_views_handler_field',
    ),
  );
  $data['sp_dw_advocacy_stats_psudo']['node_status'] = array(
    'title' => t('Node Status'),
    'help' => t('The current webform\'s node status.'),
    'field' => array(
      'handler' => 'springboard_dw_views_handler_field',
    ),
  );
  $data['sp_dw_advocacy_stats_psudo']['form_id'] = array(
    'title' => t('Form ID'),
    'help' => t('The Form ID of the form from which action statistics will be fetched.'),
    'field' => array(
      'handler' => 'springboard_dw_views_handler_field',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  // End advocacy lifetime stats view type

  // Defines a view type which displays lifetime performance of a given donation form from the warehouse:
  $data['sp_dw_donation_stats_psudo']['table'] = array(
    'group' => t('Springboard DW Donation Stats'),
    'base' => array(
      'title' => t('Springboard DW Donation Stats'),
      'help' => t('Fetches lifetime performance statistic from the data warehouse for a single, contextually filtered donation form.'),
      'query class' => 'springboard_dw_donation_stats_views_plugin_query', 
    ),
  );
  // Define the fields:
  $data['sp_dw_donation_stats_psudo']['raised'] = array(
    'title' => t('Total Amount Donated'),
    'help' => t('Fetches the total amount donated from this donation form.'),
    'field' => array(
      'handler' => 'springboard_dw_views_handler_field',
    ),
  );
  $data['sp_dw_donation_stats_psudo']['gifts'] = array(
    'title' => t('Total Donations'),
    'help' => t('Fetches the total number of donations submitted from this donation form.'),
    'field' => array(
      'handler' => 'springboard_dw_views_handler_field',
    ),
  );
  $data['sp_dw_donation_stats_psudo']['sustainers'] = array(
    'title' => t('Total Recurring Donations'),
    'help' => t('Fetches the total number of recurring donations submitted from this donation form.'),
    'field' => array(
      'handler' => 'springboard_dw_views_handler_field',
    ),
  );
  $data['sp_dw_donation_stats_psudo']['first_time_donors'] = array(
    'title' => t('Total First Time Donations'),
    'help' => t('Fetches the total number of first-time donations submitted from this donation form.'),
    'field' => array(
      'handler' => 'springboard_dw_views_handler_field',
    ),
  );
  $data['sp_dw_donation_stats_psudo']['first_donation_id'] = array(
    'title' => t('First Donation ID'),
    'help' => t('Fetches the Donation ID of the oldest donation submitted to the DW from this form.'),
    'field' => array(
      'handler' => 'springboard_dw_views_handler_field',
    ),
  );
  $data['sp_dw_donation_stats_psudo']['latest_donation_id'] = array(
    'title' => t('Latest Donation ID'),
    'help' => t('Fetches the Donation ID of the most recent donation submitted to the DW from this form.'),
    'field' => array(
      'handler' => 'springboard_dw_views_handler_field',
    ),
  );
  $data['sp_dw_donation_stats_psudo']['first_submission_date'] = array(
    'title' => t('First Donation Date'),
    'help' => t('Fetches the date when the oldest donation to this form was submitted.'),
    'field' => array(
      'handler' => 'springboard_dw_views_handler_field',
    ),
  );
  $data['sp_dw_donation_stats_psudo']['latest_submission_date'] = array(
    'title' => t('Latest Donation Date'),
    'help' => t('Fetches the date when the most recent donation to this form was submitted.'),
    'field' => array(
      'handler' => 'springboard_dw_views_handler_field',
    ),
  );
  $data['sp_dw_donation_stats_psudo']['donation_id'] = array(
    'title' => t('Donation ID'),
    'help' => t('The ID of the donation form from which statistics will be fetched.'),
    'field' => array(
      'handler' => 'springboard_dw_views_handler_field',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  $data['sp_dw_donation_stats_psudo']['latest_fetch'] = array(
    'title' => t('Latest fetch'),
    'help' => t('Displays a message detailing how long ago this data was fetched from the warehouse.'),
    'field' => array(
      'handler' => 'springboard_dw_views_handler_field',
    ),    
  );
  $data['sp_dw_donation_stats_psudo']['node_status'] = array(
    'title' => t('Node Status'),
    'help' => t('The current donation form\'s node status.'),
    'field' => array(
      'handler' => 'springboard_dw_views_handler_field',
    ),
  );
  // End DW Life Donation Stats view type

  // Defines a view type which displays donations data from the warehouse:
  $data['sp_dw_donations_psudo']['table'] = array(
    'group' => t('Springboard DW Donations'),
    'base' => array(
      'title' => t('Springboard DW Donations'),
      'help' => t('Fetches archived donation data from the Data Warehouse rather than the Drupal database.'),
      'query class' => 'springboard_dw_donations_views_plugin_query',
    ),
  );

  // Fields:
  $field_keys = _springboard_dw_get_donation_data_keys_labels();
  foreach ($field_keys as $field_key => $field_label) {
    // form_id is a bit generic in Drupal:
    if ($field_key == 'form_id') {
      $field_key == 'donation_form_id';
    }
    
    $data['sp_dw_donations_psudo'][$field_key] = array(
      'title' => $field_label,
      'help' => t('Data warehouse value for key "' . $field_key . '"'),
      'field' => array(
        'handler' => 'springboard_dw_views_handler_field',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    );
  }

  // Add exposed filter support to the donation_id field:
  if (isset($data['sp_dw_donations_psudo']['donation_id'])) {
    $data['sp_dw_donations_psudo']['donation_id']['argument'] = array(
      'title' => t('Donation ID'),
      'help' => t('Fetches a single donation record by Donation ID.'),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
      ), 
    );
  }

  // Add field-agnostic data warehouse search filter:
  $data['sp_dw_donations_psudo']['dw_global_search'] = array(
    'title' => t('Data Warehouse Search'),
    'help' => t('Keyword search across all donation fields.'),
    'filter' => array(
      'handler' => 'springboard_dw_views_handler_filter',
    ),
  );

  // Add date field support:
  $date_fields = array('transaction_date', 'created_at', 'updated_at');
  foreach ($date_fields as $date_field) {
    $data['sp_dw_donations_psudo'][$date_field]['field'] = array(
      'handler' => 'springboard_dw_views_handler_date_field',
      'click sortable' => TRUE,
      'is_date' => TRUE,
    );
    $data['sp_dw_donations_psudo'][$date_field]['filter'] = array(
      'handler' => 'springboard_dw_views_handler_date_filter',
      'empty_field_name' => 'Undated',
      'is_date' => TRUE,
    );
  }

  // Add "Payment" link:
  $data['sp_dw_donations_psudo']['payment_link'] = array(
    'title' => t('Payment'),
    'help' => t('Provides a link to a payment, if it currently exists in the Drupal DB.'),
    'field' => array(
      'handler' => 'springboard_dw_views_handler_field',
      'click sortable' => FALSE,
    ),
  );
  // End DW donations view type

  return $data;
}

/**
 * Implements hook_views_plugins().
 *
 * Declare a query plugin to fetch data from the data warehouse vs DB queries.
 */
function springboard_dw_views_plugins() {
  $plugins = array(
    // The query plugin replaces DB queries with API queries:
    'query' => array(
      'springboard_dw_donations_views_plugin_query' => array(
        'title' => t('Springboard Data Warehouse Donations API Request'),
        'help' => t('Uses Guzzle for querying remote donation data'),
        'handler' => 'springboard_dw_donations_views_plugin_query',
        'path' => drupal_get_path('module', 'springboard_dw') . '/includes/views/plugins',
      ),
      'springboard_dw_donation_stats_views_plugin_query' => array(
        'title' => t('Springboard Data Warehouse Donation Statistics API Request'),
        'help' => t('Uses Guzzle for querying remote donation data'),
        'handler' => 'springboard_dw_donation_stats_views_plugin_query',
        'path' => drupal_get_path('module', 'springboard_dw') . '/includes/views/plugins',
      ),
      'springboard_dw_advocacy_stats_views_plugin_query' => array(
        'title' => t('Springboard Data Warehouse Advocacy Statistics API Request'),
        'help' => t('Uses Guzzle for querying remote advocacy data'),
        'handler' => 'springboard_dw_advocacy_stats_views_plugin_query',
        'path' => drupal_get_path('module', 'springboard_dw') . '/includes/views/plugins',
      ),
    ),
  );
  return $plugins;
}

/**
 * Implements hook_views_handlers().
 *
 * Declare custom data warehouse handlers.
 */
function springboard_dw_views_handlers() {
  $handlers = array(
    'info' => array(
      'path' => drupal_get_path('module', 'springboard_dw') . '/includes/views/handlers',
    ),
    'handlers' => array(
      'springboard_dw_views_handler_filter' => array('parent' => 'views_handler_filter'),
    ),
  );
  return $handlers;
}

/**
 * Implements hook_form_alter()
 */
function springboard_dw_form_views_exposed_form_alter(&$form, &$form_state) {

  if (!isset($form['#id']) || $form['#id'] != 'views-exposed-form-springboard-dw-donations-report-page') {
    return;
  }
  // Group filters into basic and advanced fieldsets:
  $filter_groups_form = array();
  $filter_groups = array(
    '#type' => 'container',
    '#weight' => -9999,
    '#attributes' => array('class' => array('dw-filters-fieldsets')),
  );
  $filter_groups['basic_filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Search All-Time Donations'),
    '#attributes' => array('class' => array('dw-basic-filters',)),
  ); 

  // Display the advanced filters fieldset as expanded if any of its values are populated:
  $advanced_filters_classes = array('dw-advanced-filters', 'collapsible', 'collapsed');
  if (isset($_GET) && is_array($_GET)) {
    foreach(array('first_name', 'last_name', 'gateway', 'amount', 'form_name') as $filter_key) {
      if (isset($_GET[$filter_key]) && !empty($_GET[$filter_key])) {
        $advanced_filters_classes = array('dw-advanced-filters', 'collapsible');
        break;
      }
    }
  }

  $filter_groups['advanced_filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced Filters'),
    '#attributes' => array('class' => $advanced_filters_classes),
  );
  $filter_groups_form['filter_groups'] = $filter_groups;

  $form['#prefix'] = drupal_render($filter_groups_form);
  $form['#attached']['js'][] = 'misc/collapse.js';
  $form['#attached']['js'][] = 'misc/form.js';

  // Attached CSS and jQuery related to the exposed filters unless this is view preview output:
  $current_path = isset($_SERVER['REQUEST_URI']) ? $_SERVER['REQUEST_URI'] : ''; // (drupal_get_path() returns nothing during view preview.)
  if (strpos($current_path, 'admin/structure/views') === FALSE) {
    // Attach filtering and sorting values for jQuery csv export button to send back to Drupal to be queued for export:
    $view_data = array('source_view' => 'springboard_dw_donations_report');
    if (isset($form_state['input']) && is_array($form_state['input'])) {
      foreach ($form_state['input'] as $key => $value) {
        if (empty($value)) {
          continue;
        }
        switch ($key) {
          case 'sort':
            $view_data['sort'] = $value;
            break;
          case 'order':
            $view_data['order'] = $value;
            break;
          default:
            $view_data[$key] = $value;
            break;
        }
      }
    }   
    $form['#attached']['js'][] = array(
      'type' => 'setting',
      'data' => array('sbDWExportDonationsData' => $view_data),
    );
    $form['#attached']['css'][] = drupal_get_path('module', 'springboard_dw') . '/css/springboard_dw.css';
    $form['#attached']['js'][] = drupal_get_path('module', 'springboard_dw') . '/js/springboard_dw.js';
  }

  // Alter date filter value format:
  if (isset($form['transaction_date']['min']['#date_format'])) {
    $form['transaction_date']['min']['#date_format'] = 'm/d/Y';
  }
  if (isset($form['transaction_date']['max']['#date_format'])) {
    $form['transaction_date']['max']['#date_format'] = 'm/d/Y';
  }

  // Convert status and gateway fields into dynamically-populated drop-downs:
  _springboard_dw_exposed_form_selectify($form, 'gateway', 'donations/gateway/distinct', 'Gateway'); 
  _springboard_dw_exposed_form_selectify($form, 'status', 'donations/status/distinct', 'Status'); 
}

/**
 * Helper function to covert a text field into a dw-based, dynamically populated select:
 */
function _springboard_dw_exposed_form_selectify(&$form, $field_name, $endpoint, $label) {
  if (!isset($form[$field_name]) || !isset($form[$field_name]['#type'])) {
    return;
  }

  $method = 'GET';
  $response = springboard_dw_api_call($endpoint, array(), $method);
  if (!is_object($response) || !method_exists($response, 'getBody')) {
    return;
  }
  $response_data = json_decode((string) $response->getBody());
  global $user;
  if ($user->uid == 1 && isset($_GET['debug']) && $_GET['debug'] == 1) {
    drupal_set_message('Endpoint: ' . $endpoint);
    drupal_set_message('D/w ' . $label . ' drop-down request params: <pre>' . print_r($params, 1) . '</pre>');
    drupal_set_message('DEBUG: Data fetched just now from the warehouse:<pre>' . print_r($response_data, 1) . '</div>');
  }
  $options = array('' => '- ' . $label . ' -');
  $object_target = substr($field_name, -1) == 's' ? $field_name . 'es' : $field_name . 's';
  if (isset($response_data->{$object_target}) && is_array($response_data->{$object_target})) {
    $response_options = $response_data->{$object_target};
    foreach ($response_options as $key => $option) {
      $options[$option] = $option; 
    }
  }
  else {
    return;
  }

  // Make statuses human-readable in the drop-down:
  if ($field_name == 'status') {
    foreach ($options as $key => $option) {
      $options[$key] = ucwords(str_replace('_', ' ', $option));
    }
  }


  $form[$field_name]['#type'] = 'select';
  $form[$field_name]['#size'] = 1;
  $form[$field_name]['#required'] = FALSE;
  $form[$field_name]['#options'] = $options;
  unset($form[$field_name]['#default_value']);
}



/**
 * Implements hook_views_post_render().
 *
 * Add CSS and JS includes for the single donation detail display.
 */
function springboard_dw_views_post_render(&$view, &$output, &$cache) {
  if ($view->name != 'springboard_dw_donations_report') {
    return;
  }
  drupal_add_css(drupal_get_path('module', 'springboard_dw') . '/css/springboard_dw_detail.css',
    array('type' => 'file')); 
  drupal_add_js(drupal_get_path('module', 'springboard_dw') . '/js/springboard_dw_detail.js',
    array('type' => 'file'));  
}


function _springboard_dw_get_donation_data_keys_labels() {
  return array(
    'unique_id' => t('Unique ID'),
    'donation_id' => t('Donation ID'),
    'parent_id' => t('Parent ID'),
    'group_id' => t('Group ID'),
    'amount' => t('Donation Amount'),
    'currency' => t('Currency'),
    'quantity' => t('Quantity'),
    'quick_submit' => t('Quick Submit'),
    'click_submit' => t('Click Submit'),
    'ms' => t('MS'),
    'cid' => t('cid'),
    'first_name' => t('First Name'),
    'last_name' => t('Last Name'),
    'email' => t('Email Address'),
    'address' => t('Mailing Address'),
    'address_line_2' => t('Mailing Address - Line 2'),
    'city' => t('City'),
    'state' => t('State'),
    'country' => t('Country'),
    'zip' => t('Zip/Postal Code'),
    'referrer' => t('Referred URL'),
    'initial_referrer' => t('Initial Referred URL'),
    'payment_method' => t('Payment Method'),
    'recurs_monthly' => t('Recurs Monthly'),
    'search_engine' => t('Search Engine'),
    'search_string' => t('Search String'),
    'user_agent' => t('User Agent'),
    'device_type' => t('Device Type'),
    'device_name' => t('Device Name'),
    'device_os' => t('Device OS'),
    'device_browser' => t('Device Browser'),
    'donation_form_id' => t('Donation Form ID'),
    'contact_id' => t('Contact ID'),
    'submission_id' => t('Submission ID'),
    'status' => t('Transaction Status'),
    'transaction_id' => t('Transaction ID'),
    'gateway' => t('Gateway'),
    'card_type' => t('Credit Card Type'),
    'card_last_4' => t('Card Last 4'),
    'card_expiration_month' => t('Card Expiration Month'),
    'card_expiration_year' => t('Card Expiration Year'),
    'bank_account_mask' => t('Bank Account Mask'),
    'ip_address' => t('IP Address'),
    'created_at' => t('Created At'),
    'updated_at' => t('Updated At'),
    'transaction_date' => t('Transaction Date'),
    'extra_props' => t('Extra Props Data'),
    'form_name' => t('Form Name'),
    'form_url' => t('Form URL'),
  ); 
}
