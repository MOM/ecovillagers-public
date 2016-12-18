<?php

/**
 * @file
 * Utility functions for the salesforce queue module.
 */

/**
 * Builds a form for testing Salesforce object exports.
 */
function salesforce_queue_object_verification_form() {
  $form['operation'] = array(
    '#type' => 'select',
    '#title' => 'Operation',
    '#options' => drupal_map_assoc(array('CREATE', 'UPSERT', 'UPDATE')),
  );

  $form['object'] = array(
    '#type' => 'textarea',
    '#title' => 'Object',
    '#description' => 'Salesforce object serialized in json format.',
    '#required' => TRUE,
  );

  $form['dedupe_field'] = array(
    '#type' => 'textfield',
    '#title' => 'Dedupe field',
    '#description' => 'Required for UPSERT operations.',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Export',
  );

  return $form;
}

/**
 * Validates salesforce_queue_object_verification_form.
 */
function salesforce_queue_object_verification_form_validate($form, &$form_state) {
  if (is_null(json_decode($form_state['values']['object']))) {
    form_set_error('object', 'Object must be a valid json string.');
  }

  if ($form_state['values']['operation'] == 'UPSERT' && empty($form_state['values']['dedupe_field'])) {
    form_set_error('dedupe_field', 'Dedupe field required for UPSERT operations.');
  }
}

/**
 * Submits salesforce_queue_object_verification_form.
 */
function salesforce_queue_object_verification_form_submit($form, &$form_state) {
  $sobject = json_decode($form_state['values']['object']);
  $item = array(
    'object_type' => $sobject->type,
    'operation' => $form_state['values']['operation'],
    'dedupe_field' => $form_state['values']['dedupe_field'],
    'sobject' => $sobject,
  );
  $item = (object) $item;
  $sync = new SalesforceSync();
  $results = $sync->sendItem($item);
  drupal_set_message(print_r($results, TRUE));
}
