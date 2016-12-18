<?php

/**
 * @file
 * Logs validation errors in J. River environment.
 */

/**
 * Check a webform. Unfortunately we can't predict the names of forms
 * on any particular installation - so must check all vs. webform.
 * On a custom module, if you know your form name - use hook_form_FORM_ID_alter().
 */
function validation_log_form_alter(&$form, $form_state, $form_id) {
  // If our form name stars with 'webform_', good bet it's a webform to monitor.
  if (strpos($form_id, 'webform_') === 0 &&
    isset($form['#parameters'][2]->type) && $form['#parameters'][2]->type == 'donation_form') {
    $form['#validate'][] = '_validation_log_validate_webform';
  }
}

/**
 * Additional validation check, does not actually change validation.
 * This just grabs results from errors and logs it.
 * So long as this is called last, it'll grab everything.
 */
function _validation_log_validate_webform($form, &$form_state) {
  $errors = form_get_errors();
  // Loop only once.
  $component_set = array();
  // Checking in case someone names a form 'webform_' something and this isn't a webform_ form.
  // They *shouldn't* but that's no reason to not account for it, esp since non-set vars will throw errs.
  if (isset($form['#node']->webform['components'])) {
    foreach ($form['#node']->webform['components'] as $component) {
      $component_set[$component['form_key']] = $component;
    }
  }
  foreach ($errors as $element => $message) {
    $element_path = explode('][', $element);
    $form_key = array_pop($element_path);
    $nid = '';
    if (isset($form['#node']->webform['nid'])) {
      $nid = $form['#node']->webform['nid'];
    }
    // Could be a non-webform element blew up, so check that a cid exists.
    $cid = '';
    if (isset($component_set[$form_key]['cid'])) {
      $cid = $component_set[$form_key]['cid'];
    }
    // And log it.
    validation_log($message, $form_key, $nid, $cid);
  }
}

/**
 * Implements hook_fundraiser_order_decline().
 */
function validation_log_fundraiser_order_decline($order_id, $message) {
  $order = module_invoke_all('fundraiser_get_order', $order_id);
  $nid = $order->products[0]->nid;
  $form_key = 'gateway_failure';
  validation_log($message, $form_key, $nid);
}
