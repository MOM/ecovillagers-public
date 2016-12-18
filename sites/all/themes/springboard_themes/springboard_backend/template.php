<?php

/**
 * Implements template_preprocess_html().
 */
function springboard_backend_preprocess_html(&$vars) {

// Add to head <meta http-equiv="X-UA-Compatible" content="IE=edge" /> for proper IE rendering.
  $http_equiv = array(
    '#tag' => 'meta',
    '#attributes' => array(
      'http-equiv' => 'X-UA-Compatible',
      'content' => 'IE=edge',
    ),
  );
  drupal_add_html_head($http_equiv, 'http_equiv');

  // Define the URL path.
 $path = request_uri();

  // Add body classes to various pages for better theming.

  // General springboard page.
  if (preg_match('|^/springboard((?:/[a-zA-Z0-9_\-]*)*)?|', $path, $matches)) {
    $vars['classes_array'][] = 'page-springboard';
  }

  if (arg(0) == "node" && arg(2) == "submission" && arg(4) == 'edit') {
    $vars['classes_array'][] = 'webform-submission-edit';
  }

  if (arg(0) == "node" && arg(2) == "submission" && arg(4) == NULL) {
    $vars['classes_array'][] = 'webform-submission-view';
  }

  if (arg(0) == "node" && arg(2) == "webform-results" && arg(3) == 'table') {
    $vars['classes_array'][] = 'webform-results-table';
  }

  if (arg(0) == "node" && arg(2) == "webform-results" && arg(3) == 'download') {
    $vars['classes_array'][] = 'webform-results-download';
  }

  if (arg(0) == "springboard" && arg(1) == "templates") {
    $vars['classes_array'][] = 'springboard-templates';
  }

  if (arg(1) == "springboard" && arg(2) == NULL) {
    $vars['classes_array'][] = 'springboard-dashboard';
  }

  // Not any kind of node add or edit page.
  if (!(arg(1) == 'add' || arg(1) == 'edit' || arg(2) == 'edit' || arg(3) == 'edit' || arg(4) == 'edit' || arg(4) == 'fundraiser_upsell')) {
    $vars['classes_array'][] = 'page-springboard-view';
  }

}

/**
 * Implements template_preprocess_page().
 */
function springboard_backend_preprocess_page(&$vars) {
  // Override menu settings and display the springboard admin menu as the main menu

  if (module_exists('springboard_admin')) {
    $menu_links = menu_tree('springboard_admin_menu');

    // Get rid of third level menu items
    foreach ($menu_links as $key => $items) {
      if(isset($items['#below'])) {
        foreach($items['#below'] as $key2 => $item) {
          if(isset($menu_links[$key]['#below'][$key2]['#below'])) {
            unset($menu_links[$key]['#below'][$key2]['#below']);
          }
        }
      }
    }

    $vars['main_menu'] = $menu_links;

    // menu_tree() is the best available option for rendering menu links, but
    // isn't flexible for changing the HTML/Classes in different contexts.
    // So, use a regex to change the classes on the menu for the footer.
    $vars['footer_menu'] = drupal_render($vars['main_menu']);
    // change the wrapping ul's class so drop-down js isn't applied
    $vars['footer_menu'] = preg_replace('/class="nav nav-tabs"/', '/class="nav nav-footer"/', $vars['footer_menu']);
    // change sub-ul's class so drop-down styling isn't applied
    $vars['footer_menu'] = preg_replace('/class="dropdown-menu "/', '/class="child-menu"/', $vars['footer_menu']);
    // change sub li's class so drop-down styling isn't applied
    $vars['footer_menu'] = preg_replace('/dropdown/', '', $vars['footer_menu']);
    $vars['footer_menu'] = preg_replace('/id="/', '/id="fm-', $vars['footer_menu']);
  }

  // Open sans font.
  // Usage: font-family: 'Open Sans', sans-serif;
  drupal_add_css('//fonts.googleapis.com/css?family=Open+Sans:300italic,400italic,600italic,700italic,800italic,400,300,600,700,800',
    array(
      'type' => 'external',
    )
  );

// Set a var for springboard home page.
  if (arg(0) == "springboard" && arg(1) == NULL) {
    $vars['sb_dashboard'] = '';
  }

// Set vars for the logged in user and id / not logged in.
  global $user;
  if ($user->uid) {
    $vars['is_loggedin'] = '';
    $vars['the_user'] = $user->name;
    $vars['user_id'] = '/user/' . $user->uid;
  }
  else {
    $vars['not_loggedin'] = '';
  }
  // Remove local task tabs from some admin pages.
  $t1 = preg_match('|^admin/springboard$|', $_GET['q']); // Springboard dashboard.
  $t2 = preg_match('|^node/([0-9]*)/clone$|', $_GET['q']); // Node clone confirmation page.
  $t3 = preg_match('|^node/([0-9]*)/delete$|', $_GET['q']); // Node delete confirmation page.
  $t4 = preg_match('|^admin/springboard/settings$|', $_GET['q']); // Springboard settings page.
  $t5 = preg_match('|^admin/config/content/webform_goals$|', $_GET['q']); // Webform Goals page (purposefully remove access to child pages).
  $t6 = preg_match('|^admin/config/services/springboard_social$|', $_GET['q']); // Springboard Social page (purposefully remove access to child pages).

  if ($t1 || $t2 || $t3 || $t4 || $t5 || $t6) {
    unset($vars['tabs']);
  }
}
/**
 * Overrides theme_menu_tree();
 */
function springboard_backend_menu_tree($vars) {
  // Add tab-style class to menus
  return '<ul class="nav nav-tabs">' . $vars['tree'] . '</ul>';
}

/**
 * Implements hook_css_alter().
 */
function springboard_backend_css_alter(&$css) {
  $path_system = drupal_get_path('module', 'system');
  $path_views = drupal_get_path('module', 'views');
  $path_webform = drupal_get_path('module', 'webform');

  // Remove misc styles that get in the way rather than having to override them.
  $remove = array(
    $path_system . '/system.theme.css',
    $path_system . '/system.menus.css',
    $path_system . '/system.messages.css',
    $path_views . '/css/views.css',
    $path_webform .  '/css/webform.css',
  );

// Remove stylesheets which match our remove array.
  foreach ($css as $stylesheet => $options) {
    if (in_array($stylesheet, $remove)) {
      unset($css[$stylesheet]);
    }
  }
}


/**
 * Theme the results table displaying all the submissions for a particular node.
 *
 * @param $node
 *   The node whose results are being displayed.
 * @param $components
 *   An associative array of the components for this webform.
 * @param $submissions
 *   An array of all submissions for this webform.
 * @param $total_count
 *   The total number of submissions to this webform.
 * @param $pager_count
 *   The number of results to be shown per page.
 */
function springboard_backend_webform_results_table($vars) {
  drupal_add_library('webform', 'admin');

  $node = $vars['node'];
  $components = $vars['components'];
  $submissions = $vars['submissions'];
  $total_count = $vars['total_count'];
  $pager_count = $vars['pager_count'];

  $header = array();
  $rows = array();
  $cell = array();

  // This header has to be generated separately so we can add the SQL necessary.
  // to sort the results.
  $header = theme('webform_results_table_header', array('node' => $node));

  // Generate a row for each submission.
  foreach ($submissions as $sid => $submission) {
    $cell[] = l($sid, 'node/' . $node->nid . '/submission/' . $sid);
    $cell[] = format_date($submission->submitted, 'short');
    $cell[] = theme('username', array('account' => $submission));
    $cell[] = $submission->remote_addr;
    $component_headers = array();

    // Generate a cell for each component.
    foreach ($node->webform['components'] as $component) {
      $data = isset($submission->data[$component['cid']]['value']) ? $submission->data[$component['cid']]['value'] : NULL;
      $submission_output = webform_component_invoke($component['type'], 'table', $component, $data);
      if ($submission_output !== NULL) {
        $component_headers[] = check_plain($component['name']);
        $cell[] = $submission_output;
      }
    }

    $rows[] = $cell;
    unset($cell);
  }
  if (!empty($component_headers)) {
    $header = array_merge($header, $component_headers);
  }

  if (count($rows) == 0) {
    $rows[] = array(array('data' => t('There are no submissions for this form. <a href="!url">View this form</a>.', array('!url' => url('node/' . $node->nid))), 'colspan' => 4));
  }

  $output = '';
  // Add custom classes for better theming.
  $output .= '<div class="webform-results-wrapper">';
  $output .= '<div class="webform-results-inner">';
  $output .= theme('webform_results_per_page', array('total_count' => $total_count, 'pager_count' => $pager_count));
  $output .= theme('table', array('header' => $header, 'rows' => $rows));
  $output .= '</div>';
  $output .= '</div>';
  return $output;
}


function springboard_backend_preprocess_views_exposed_form(&$vars, $hook) {

  // Change the apply button in views exposed filters to "go".
    $vars['form']['submit']['#value'] = t('Go');
    unset($vars['form']['submit']['#printed']);
    $vars['button'] = drupal_render($vars['form']['submit']);
}

function springboard_backend_preprocess_views_view_field(&$vars) {
   $field = $vars['field'];
   $view = $vars['view'];
   switch ($view->name) {
    case 'sbv_contacts':
      // Conditionally add link to view recurring donations if user is a sustainer.
      if($field->real_field == 'edit_node') {
        $donations = _fundraiser_sustainers_get_donation_sets_recurr_by_uid($field->last_tokens['[uid]']);
        if($donations) {
          $vars['output'] .= ' | ' . l(t('Recurring Gifts'), 'user/'. $field->last_tokens['[uid]'] . '/recurring_overview');
        }
      }
    break;
    case 'sbv_sf_batch_items':
      $field = $vars['field'];
      switch($field->field_alias) {
        case 'salesforce_log_item_sobject':
        case 'salesforce_log_item_message':
          if($vars['output'] != '') {
            $vars['output'] = '<div class="sb-collapsible-td collapsed"><a class="control"><span class="control-show">Show</span><span class="control-hide">Hide</span></a><div class="sb-collapsible-td-content">' . $vars['output'] . '</div></div>';
          }
        break;
        case 'salesforce_log_item_drupal_id':
        break;
        case 'salesforce_queue_salesforce_log_item_queue':
          if ($field->last_render == 'Removed from queue') {
            $vars['output'] = t('Removed');
          }
        break;
      }
    break;
  }
}

/**
 * Implements hook_preprocess_views().
 *
 */
function springboard_backend_preprocess_views_view(&$vars) {

  // Preprocess views.
  $view = $vars['view'];

  // Set a var for the argument on sbv_assets.
  if ($view->name == 'sbv_assets') {
    // Get the views argument.
    $view = views_get_current_view();
    $vars['arg0'] = $view->args[0];
  }

}

/**
 * Theme callback for the export complete page.
 *
 * Override this function for better theming and ux on the data export file download page.
 */
function springboard_backend_views_data_export_complete_page($variables) {
  extract($variables, EXTR_SKIP);
  drupal_set_title(t('Data export successful'));
  drupal_add_html_head(array('#tag' => 'meta', '#attributes' => array('http-equiv' =>"Refresh", 'content' => '3;url='. $file)), 'views_data_export_download');
  $output = '';
  $output .= '<h3 class="data-file-download">';
  $output .= t('Your export has been created. View/download the file <a href="@link">here</a> (will automatically download in 3 seconds.)', array('@link' => $file));
  $output .= '</h3>';

  if (!empty($return_url)) {
    $output .= '<h3>';
    $output .= l(t('Return to previous page'), $return_url);
    $output .= '</h3>';
  }
  return $output;
}

/**
 * Implements hook_form_node_form_alter_alter().
 */
function springboard_backend_form_node_form_alter(&$form, &$form_state) {
  // Set the backend and frontend themes as default values for the page wrapper theme settings field.
  if ($form['#node']->type == 'page_wrapper') {
    if (empty($form['#node']->nid) && !empty($form['page_wrappers_theme_css'])) {
      $language = $form['page_wrappers_theme_css']['#language'];
      $form['page_wrappers_theme_css'][ $language ]['#default_value'] = array(
        'springboard_backend',
        'springboard_frontend'
      );
    }

    if (!empty($form['page_wrappers_theme_css'])) {
      $language = $form['page_wrappers_theme_css']['#language'];
      $form['page_wrappers_theme_css'][ $language ]['#description'] .= t(' For best compatibility include the Springboard Frontend and Backend theme CSS on your Page Wrapper.');
    }
  }
}
