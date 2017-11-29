<?php
/**
 * @file
 * Admin functions for Springboard advocacy.
 */

/**
 * Page callback for the admin form.
 */
function springboard_taxonomy_settings_page($vocab) {

  $build = array();
  if ($vocab->machine_name == 'sba_organization_issues') {
    $build['content'] = array(
      'page_description' => array(
        '#id' => 'springboard-taxonomy-settings-page',
        '#type' => 'markup',
        '#markup' => "The Organization's Issues taxonomy can be used to generate feeds and lists of related content throughout your website.",
        '#prefix' => '<div class="springboard-taxonomy-settings-page"><p>',
        '#suffix' => '</p></div>',
      ),
      'springboard_taxonomy_org_issues_settings_form' => drupal_get_form('springboard_taxonomy_settings_form', $vocab),
    );
  }
  if ($vocab->machine_name == 'sb_node_extras') {
    $build['content'] = array(
      'page_description' => array(
        '#id' => 'springboard-taxonomy-settings-page',
        '#type' => 'markup',
        '#markup' => "The Node Extras taxonomy can be used to filter node listing.",
        '#prefix' => '<div class="springboard-taxonomy-settings-page"><p>',
        '#suffix' => '</p></div>',
      ),
      'springboard_taxonomy_node_extra_settings_form' => drupal_get_form('springboard_taxonomy_settings_form', $vocab),
    );

    $build['content'][] = array(
      'page_views' => array(
        '#id' => 'springboard-taxonomy-settings-page-views',
        '#type' => 'markup',
        '#markup' => "",
        '#prefix' => '<div class="springboard-taxonomy-settings-page"><p>',
        '#suffix' => '</p></div>',
      ),
      'springboard_taxonomy_settings_views_form' => drupal_get_form('springboard_taxonomy_node_extra_views_settings_form'),
    );
  }
  return $build;
}

/**
 * Configuration settings form for Springboard taxonomy.
 */
function springboard_taxonomy_settings_form($form, &$form_state, $vocab) {
  $form = array();

  if (!isset($form_state['storage']['step'])) {
    $form_state['storage']['step'] = 'step_1';
  }

  $form['#submit'][] = 'springboard_taxonomy_settings_submit';

  switch ($form_state['storage']['step']) {
    case 'step_1':

      if ($vocab->machine_name == 'sba_organization_issues') {
        springboard_taxonomy_org_issues_step_one($form, $vocab);
      }
      else {
        springboard_taxonomy_node_extras_step_one($form, $vocab);
      }
      break;

    case 'step_2':

      if ($vocab->machine_name == 'sba_organization_issues') {
        $changes = springboard_taxonomy_org_issues_step_two($form_state);
      }
      else {
        $changes = springboard_taxonomy_node_extras_step_two($form_state);
      }

      $messages = theme('springboard_taxonomy_confirm_message', array('changes' => $changes, 'vocab' => $vocab->name));

      $form['#submit'][] = 'system_settings_form_submit';
      $form = confirm_form(
        $form,
        t('Are you sure you want to do this?'),
        'admin/config/content/springboard-taxonomy',
        $messages,
        t('Confirm'),
        t('Cancel')
      );
      break;
  }
  return $form;
}

/**
 * Build the organization issues step one form.
 */
function springboard_taxonomy_org_issues_step_one(&$form, $vocab) {

  // Get all webform node types.
  $types = node_type_get_names();
  $webform_types = variable_get('webform_node_types', array());
  unset($webform_types['webform']);
  $webform_types = array_flip($webform_types);
  $options = array_intersect_key($types, $webform_types);
  $form['springboard_taxonomy_node_types'] = array(
    '#title' => t('Add or remove the @name taxonomy for the following form types:', array('@name' => $vocab->name)),
    '#description' => t('Unchecking any checked items will permanently remove all @name data from that content type.', array('@name' => $vocab->name)),
    '#type' => 'checkboxes',
    '#options' => $options,
    '#default_value' => variable_get('springboard_taxonomy_node_types', array()),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
}

/**
 * Build the organization issues step two form.
 */
function springboard_taxonomy_org_issues_step_two($form_state) {
  $current_settings = variable_get('springboard_taxonomy_node_types', array());
  $new_settings = $form_state['values']['springboard_taxonomy_node_types'];
  $changes = array_diff_assoc($new_settings, $current_settings);

  foreach ($changes as $key => $value) {
    // This is a new content type so don't create a warning message
    // about deleting data.
    if (!isset($current_settings[$key]) && $value === 0) {
      unset($changes[$key]);
    }
  }
  return $changes;
}

/**
 * Build the node extras step one form.
 */
function springboard_taxonomy_node_extras_step_one(&$form, $vocab) {
  $options = node_type_get_names();

  $form['stax'] = array(
    '#type' => 'fieldset',
    '#title' => 'Node Types',
    '#description' => "",
    '#collapsible' => TRUE,
  );

  $form['stax']['springboard_taxonomy_node_extras_types'] = array(
    '#title' => t('Add or remove the @name taxonomy for the following node types:', array('@name' => $vocab->name)),
    '#description' => t('Unchecking any checked items will permanently remove all @name data from that content type.', array('@name' => $vocab->name)),
    '#type' => 'checkboxes',
    '#options' => $options,
    '#default_value' => variable_get('springboard_taxonomy_node_extras_types', array()),
  );

  $form['stax']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
}

/**
 * Build the node extras step two form.
 */
function springboard_taxonomy_node_extras_step_two($form_state) {
  $current_settings = variable_get('springboard_taxonomy_node_extras_types', array());
  $new_settings = $form_state['values']['springboard_taxonomy_node_extras_types'];
  $changes = array_diff_assoc($new_settings, $current_settings);

  foreach ($changes as $key => $value) {
    // This is a new content type so don't create a
    // warning message about deleting data.
    if (!isset($current_settings[$key]) && $value === 0) {
      unset($changes[$key]);
    }
  }
  return $changes;
}


/**
 * Configuration settings form for Springboard taxonomy.
 */
function springboard_taxonomy_node_extra_views_settings_form($form, &$form_state) {

  if (isset($form_state['input']['springboard_taxonomy_node_extras_types'])) {
    // Don't show this form if we're on the confirm page for the node type
    // form.
    return array();
  }

  $form = array();
  $all_views = views_get_all_views();
  $omit = array(
    'og_all_user_group_content',
    'og_nodes',
    'springboard_group',
    'donation_content',
    'og_nodes',
    'glossary',
    'archive',
    'frontpage',
    'taxonomy_term',
    'webform_ab_tests',
    'webform_ab',
    'donation_forms',
    'p2p_campaign',
    'p2p_campaign_landing_slideshow',
    'p2p_categories',
    'p2p_suggested_donation',
    'personal_campaign_donor_dashboard',
    'p2p_personal_campaigns_admin',
    'p2p_personal_campaigns_by_campaign',
    'p2p_personal_campaigns_by_campaigner',
    'p2p_personal_campaigns_by_category',
    'p2p_top_personal_campaigns_by_category',
    'p2p_search_for_a_campaign',
  );

  foreach ($all_views as $key => $view) {
    if ($view->base_table != 'node') {
      unset($all_views[$key]);
    }
    if (in_array($view->name, $omit)) {
      unset($all_views[$key]);
    }
    if ($view->disabled) {
      unset($all_views[$key]);
    }
  }

  $extras_filter_views = array('' => 'None');
  foreach ($all_views as $key => $opt) {
    foreach ($opt->display as $display_name => $display) {
      if (strpos($display_name, 'entityrefer') === FALSE && strpos($display_name, 'pane') === FALSE) {
        $extras_filter_views[$key][$key . '|' . $display_name] = !empty($display->display_title) ? $display->display_title . ' (' . $display_name . ')' : $display_name;
      }
    }
  }

  $form['altered_views']['extras_filter'] = array(
    '#type' => 'fieldset',
    '#title' => 'Filtered views',
    '#description' => t("Add the node extras filter to the following views"),
    '#collapsible' => TRUE,
  );
  $form['altered_views']['extras_filter']['extras_filter_views'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#options' => $extras_filter_views,
    '#default_value' => variable_get('extras_filter_views', array()),
    '#size' => 20,
    '#tree' => TRUE,
  );
  $form['altered_views']['extras_filter']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  $form['#submit'][] = 'system_settings_form_submit';
  $form['#submit'][] = 'springboard_taxonomy_views_settings_submit';


  return $form;
}

/**
 * Clear the views cache after updating taxonomy views config.
 */
function springboard_taxonomy_views_settings_submit($form, $form_state) {
  cache_clear_all('*', 'cache_views', TRUE);
}

/**
 * Submit Function.
 *
 * Create or delete field instances.
 *
 * @param array $form
 * @param array $form_state
 */
function springboard_taxonomy_settings_submit($form, &$form_state) {

  switch ($form_state['storage']['step']) {
    case 'step_2':

      $form_state['values'] = $form_state['storage']['step_values']['step_1'];
      if (isset($form_state['values']['springboard_taxonomy_node_types'])) {
        $types = $form_state['values']['springboard_taxonomy_node_types'];
        $name = 'organization';
      }
      else {
        $types = $form_state['values']['springboard_taxonomy_node_extras_types'];
        $name = 'extras';
      }
      foreach ($types as $type => $status) {
        if ($status === 0) {
          _springboard_taxonomy_delete_instances($type, $name);
        }
        else {
          _springboard_taxonomy_create_instances($type, $name);
        }
      }
      break;

    case 'step_1':
      $form_state['storage']['step_values']['step_1'] = $form_state['values'];
      $form_state['storage']['step'] = 'step_2';
      $form_state['rebuild'] = TRUE;
      break;
  }

}



/**
 * Create taxonomy fields.
 */
function _springboard_taxonomy_create_instances($type, $name) {
  module_load_include('inc', 'field', 'field.crud');
  module_load_include('inc', 'field', 'field.info');
  module_load_include('install', 'springboard_taxonomy');
  foreach (_springboard_taxonomy_field_instance($type, $name) as $field_name => $field) {

    // If somehow the base field was deleted, recreate it.
    if (!field_info_field($field['field_instance']['field_name'])) {
      $base = _springboard_taxonomy_field_base();

      field_create_field($base[$field_name]['field_config']);
    }

    // Create the instance.
    if (!field_info_instance('node', $field['field_instance']['field_name'], $type)) {
      field_create_instance($field['field_instance']);
    }
  }
}

/**
 * Delete taxonomy fields.
 */
function _springboard_taxonomy_delete_instances($type, $name) {
  module_load_include('inc', 'field', 'field.crud');
  module_load_include('inc', 'field', 'field.info');
  module_load_include('install', 'springboard_taxonomy');
  foreach (_springboard_taxonomy_field_instance($type, $name) as $field_name => $field) {
    if ($instance = field_info_instance('node', $field['field_instance']['field_name'], $type)) {
      // Set false to avoid deleting base field if no more instances exist.
      field_delete_instance($instance, FALSE);
    }
  }
}

/**
 * Theme the confirmation message for the settings page.
 */
function theme_springboard_taxonomy_confirm_message($vars) {
  $changes = $vars['changes'];
  $messages = array();
  if (empty($changes)) {
    $messages[] = t("Settings have not been changed. No updates will occur.");
  }
  else {
    foreach ($changes as $key => $change) {
      if (empty($change)) {
        $messages[] = '<span class = "warning">'
          . t(
            "You are permanently removing all @vocab data from the @type content type!",
            array('@type' => $key, '@vocab' => $vars['vocab'])
          )
          . '</span>';
      }
      else {
        $messages[] = t(
          "You are adding an @vocab taxonomy field to the @type content type.",
          array('@type' => $key, '@vocab' => $vars['vocab'])
        );
      }
    }
  }

  $list = theme('item_list', array('items' => $messages));
  return $list;
}