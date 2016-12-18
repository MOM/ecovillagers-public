<?php
/**
 * @file API example code for module developers.
 */

/**
 * Implements hook_webform_goals_list_context().
 *
 * Provides "example single" context.
 *
 * Context array options:
 *   'id' (required) unique id of the context you're supplying.
 *   'name' (required) human-readable name of context.
 *   'settings_callback' (optional) callback function to add form fields to capture
 *    any custom settings required by this context.
 *   'description' => (optional) a short description of this context and what it applies to.
 */
function example_webform_goals_list_context() {
  $context['example_single'] = array(
    'id' => 'example_single',
    'name' => t('Single example'),
    'settings_callback' => 'example_single_context_fields',
    'description' => t('This goal will be applied to all webforms.'),
  );
  return $context;
}


/**
 * Implements hook_webform_goals_list_context().
 *
 * Provide "global" and "single webform" contexts.
 */
function webform_goals_webform_goals_list_context() {
  $context['global'] = array(
    'id' => 'global',
    'name' => t('Global'),
    'settings_callback' => '',
    'description' => t('This goal will be applied to all webforms.'),
  );
  $context['single'] = array(
    'id' => 'single',
    'name' => t('Single'),
    'settings_callback' => 'webform_goals_single_context_fields',
    'description' => t('This goal will only be applied to a single webform you select.'),
  );
  return $context;
}

/**
 * Implements hook_webform_goals_list_metrics().
 *
 * Add "example field" metric.
 *
 * @param $elected context
 * An array containing details of the currently selected context.
 *
 * @param $form_state
 * $form_state from the goal add/edit form.
 *
 * @param $goal
 * Current goal being edited (only present if the form is being used to edit an existing goal)
 *
 * TODO: finish this up.
 */
function example_webform_goals_list_metrics($selected_context, $form_state, $goal = array()) {

  switch ($selected_context['id']) {
    case 'example_single':
      $options = array(0 => '- You must select a form for this context to be valid -');
      if (!empty($form_state['values']['selected_form_id'])) {
        $options = _webform_goals_field_list($form_state['values']['selected_form_id']);
      }
      elseif (!empty($goal['extra']['selected_form_id'])) {
        $options = _webform_goals_field_list($goal['extra']['selected_form_id']);
      }
      $elements['custom_field_selection'] = array(
        '#type' => 'select',
        '#options' => $options,
        '#default_value' => !empty($goal['extra']['custom_field_selection']) ? $goal['extra']['custom_field_selection'] : '',
      );

      $metrics['example_field'] = array(
        'id' => 'example_field',
        'name' => t('Example field'),
        'description' => t('Goal progress will be calculated based on the sum of entries in the selected field.'),
        'progress_callback' => '',
        'settings_callback' => 'webform_goals_single_custom_fields',
        'threshold_prefix' => t('Do not display the goal progress until the selected field has a total of'),
        'threshold_suffix' => t(' values.'),
        'seed_prefix' => t('Add an initial '),
        'seed_suffix' => t(' to the goal'),
        'child_elements' => $elements,
      );

  }
  return $metrics;
}
