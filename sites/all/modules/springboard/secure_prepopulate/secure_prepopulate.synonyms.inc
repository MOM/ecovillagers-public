<?php
/**
 * @file
 * CRUD and UI for managing secure prepopulate synonyms.
 */

/**
 * Synonym admin configuration form.
 */
function secure_prepopulate_synonyms($form, $form_state) {

  $records = secure_prepopulate_load_synonyms();

  $variables['header'] = array(
    'Token key',
    'Synonyms',
    'Actions',
  );
  $variables['rows'] = array();
  $variables['attributes'] = array();
  $variables['caption'] = '';
  $variables['colgroups'] = array();
  $variables['sticky'] = array();
  $variables['empty'] = '';

  if (is_array($records)) {
    foreach ($records as $token_key => $synonyms) {
      $actions = _secure_prepopulate_synonym_actions($token_key);
      $row = array($token_key, implode(',', $synonyms), $actions);
      $variables['rows'][] = $row;
    }
  }
  $form['table'] = array(
    '#type' => 'markup',
    '#markup' => theme('table', $variables),
  );
  $form['synonyms'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add synonyms'),
  );
  $form['synonyms']['token_key'] = array(
    '#type' => 'textfield',
    '#title' => t('token key'),
    '#size' => 20,
    '#required' => TRUE,
  );
  $form['synonyms']['synonyms'] = array(
    '#type' => 'textfield',
    '#title' => t('synonyms'),
    '#description' => t('a comma-separated list of webform component form keys that are synonymous with this token key.'),
    '#required' => TRUE,
  );
  $form['synonyms']['add'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
  );
  $form['#validate'][] = 'secure_prepopulate_validate_synonym';
  $form['#submit'][] = 'secure_prepopulate_submit_synonym';

  return $form;
}

/**
 * Validate function for the add synonym form and edit synonym form.
 */
function secure_prepopulate_validate_synonym(&$form, $form_state) {
  $records = secure_prepopulate_load_synonyms();
  $form_keys = array();
  foreach ($records as $token_key => $synonyms) {
    // Ignore edited synonym cluster when validating the edit form.
    if (empty($form_state['values']['synonym_edit']) || $token_key != $form_state['values']['token_key']) {
      $token_keys[] = $token_key;
      $form_keys = array_merge($synonyms, $form_keys);
    }
  }
  if (!empty($token_keys) && in_array($form_state['values']['token_key'], $token_keys)) {
    form_set_error('token_key', t('This token key is already in use.'));
  }
  if (!empty($form_keys) && in_array($form_state['values']['token_key'], $form_keys)) {
    form_set_error('token_key', t('This token key is already in use as a synonym.'));
  }

  $submitted_form_keys = explode(',', $form_state['values']['synonyms']);
  $submitted_keys = array();
  foreach ($submitted_form_keys as $form_key) {
    $submitted_keys[] = trim($form_key);
  }

  foreach ($submitted_keys as $submitted_key) {
    if (!empty($token_keys) && in_array($submitted_key, $token_keys)) {
      form_set_error('synonyms', t('The following synonym is already in use as a token key: %key', array('%key' => $submitted_key)));
    }
    if (!empty($form_keys) && in_array($submitted_key, $form_keys)) {
      form_set_error('synonyms', t('The following synonym is already in use: %key', array('%key' => $submitted_key)));
    }
  }
}

/**
 * Submit handler for the add synonym form.
 */
function secure_prepopulate_submit_synonym($form, $form_state) {
  $settings = array(
    'token_key' => $form_state['values']['token_key'],
    'synonyms' => $form_state['values']['synonyms'],
  );
  secure_prepopulate_save_synonym($settings);
}

/**
 * The edit form for synonyms.
 */
function secure_prepopulate_edit_synonym($form, $form_state, $synonym = NULL) {

  $form['original_token_key'] = array(
    '#type' => 'value',
    '#value' => $synonym['token_key'],
  );
  $form['synonym_edit'] = array(
    '#type' => 'value',
    '#value' => 1,
  );
  $form['token_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Token key'),
    '#size' => 10,
    '#default_value' => $synonym['token_key'],
  );
  $form['synonyms'] = array(
    '#type' => 'textfield',
    '#title' => t('Synonyms'),
    '#default_value' => $synonym['synonyms'],
  );
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#submit' => array('_secure_prepopulate_synonym_form_cancel'),
    '#limit_validation_errors' => array(),
  );
  $form['#validate'][] = 'secure_prepopulate_validate_synonym';
  $form['#submit'][] = 'secure_prepopulate_submit_edit_synonym';

  return $form;
}

/**
 * Synonym edit form submit handler.
 */
function secure_prepopulate_submit_edit_synonym($form, &$form_state) {
  secure_prepopulate_delete_synonym($form_state['values']['original_token_key']);
  $settings = array(
    'token_key' => $form_state['values']['token_key'],
    'synonyms' => $form_state['values']['synonyms'],
  );
  secure_prepopulate_save_synonym($settings);
  $form_state['redirect'] = array('admin/config/system/secure-prepopulate/synonyms');
}

/**
 * Delete synonym form.
 */
function secure_prepopulate_delete_synonym_form($form, $form_state, $synonym = NULL) {

  $form['token_key'] = array(
    '#type' => 'value',
    '#value' => $synonym['token_key'],
  );
  $form['warning'] = array(
    '#type' => 'markup',
    '#prefix' => '<p>',
    '#suffix' => '</p>',
    '#markup' => t('Are you sure you want to delete this synonym group?'),
  );
  $form['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
  );
  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#submit' => array('_secure_prepopulate_synonym_form_cancel'),
    '#limit_validation_errors' => array(),
  );
  $form['#submit'][] = 'secure_prepopulate_delete_synonym_form_submit';
  return $form;
}

/**
 * Submit form handler for deleting a synonym.
 */
function secure_prepopulate_delete_synonym_form_submit($form, &$form_state) {
  secure_prepopulate_delete_synonym($form_state['values']['token_key']);
  drupal_set_message('Synonym group has been deleted.');
  $form_state['redirect'] = array('admin/config/system/secure-prepopulate/synonyms');
}

/**
 * DB Function, load all available synonyms.
 */
function secure_prepopulate_load_synonyms() {
  static $synonyms = array();
  if (empty($synonyms)) {
    $results = db_query('SELECT * FROM {secure_prepopulate_synonyms}');
    while ($synonym = $results->fetchAssoc()) {
      $synonyms[$synonym['token_key']] = explode(',', $synonym['synonyms']);
    }
  }
  return $synonyms;
}

/**
 * DB Function, load single synonym.
 */
function secure_prepopulate_synonym_load($token_key) {
  return db_query('
    SELECT *
    FROM {secure_prepopulate_synonyms}
    WHERE token_key = :token_key
  ', array(':token_key' => $token_key))->fetchAssoc();
}

/**
 * DB function, save synonym.
 */
function secure_prepopulate_save_synonym($settings, $update = array()) {
  drupal_write_record('secure_prepopulate_synonyms', $settings, $update);
}

/**
 * DB Function, delete synonym.
 */
function secure_prepopulate_delete_synonym($token_key) {
  db_delete('secure_prepopulate_synonyms')
    ->condition('token_key', $token_key)
    ->execute();
}

/**
 * Helper function, generate edit & delete links for a synonym group.
 */
function _secure_prepopulate_synonym_actions($token_key) {
  $actions = l(t('edit'), "admin/config/system/secure-prepopulate/synonyms/$token_key/edit");
  $actions .= ' &nbsp; ' . l(t('delete'), "admin/config/system/secure-prepopulate/synonyms/$token_key/delete");
  return $actions;
}

/**
 * Helper function, form bailout.
 */
function _secure_prepopulate_synonym_form_cancel($form, $form_state) {
  drupal_goto('admin/config/system/secure-prepopulate/synonyms');
}
