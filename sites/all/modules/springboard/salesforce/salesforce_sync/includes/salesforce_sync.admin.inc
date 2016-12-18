<?php

/**
 * @file
 * Administration page callbacks for the salesforce sync module.
 */

/**
 * Page callback for the admin form.
 */
function salesforce_sync_admin_page() {
  $build = array();
  $build['content'] = array(
    'page_description' => array(
      '#id' => 'salesforce-sync-admin-helptext-page',
      '#type' => 'markup',
      '#markup' => '<p>' . t('Configure settings syncing with Salesforce.') . '</p>',
      '#prefix' => '<div class="salesforce-sync-admin-helptext">',
      '#suffix' => '</div>',
    ),
    'salesforce_sync_admin_form' => drupal_get_form('salesforce_sync_admin_form'),
  );
  return $build;
}

/**
 * Configuration form for handling queues.
 */
function salesforce_sync_admin_form($form, &$form_state) {
  $form = array();

  // Variable salesforce_sync_max_batch_size.
  $form['max_batch_size'] = array(
    '#id' => 'salesforce-sync-salesforce-max-batch-size',
    '#title' => t('Maximum Salesforce Batch Size'),
    '#description' => t('The maximum number of items that can be sent to
      Salesforce in a single batch.'),
    '#type' => 'textfield',
    '#size' => 6,
    '#default_value' => _sfs_get_value('max_batch_size', $form_state),
  );

  // Variable salesforce_sync_max_retrieve_size.
  $form['max_retrieve_size'] = array(
    '#id' => 'salesforce-sync-salesforce-max-retrieve-size',
    '#title' => t('Maximum Salesforce Retrieve Size'),
    '#description' => t('The maximum number of records that can be fetched from Salesforce in a single call.'),
    '#type' => 'textfield',
    '#size' => 6,
    '#default_value' => _sfs_get_value('max_retrieve_size', $form_state),
  );

  // Variable salesforce_sync_query_limit.
  $form['query_limit'] = array(
    '#id' => 'salesforce-sync-salesforce-query-limit',
    '#title' => t('Query Limit'),
    '#description' => t('The maximum quantity of records that can be retrieved
      from Salesforce in a single process.  This prevents bad queries from
      trying to select all records.'),
    '#type' => 'textfield',
    '#size' => 6,
    '#default_value' => _sfs_get_value('query_limit', $form_state),
  );

  // Variable salesforce_sync_max_query_length.
  $form['max_query_length'] = array(
    '#id' => 'salesforce-sync-salesforce-max-query-length',
    '#title' => t('Maximum length of a Salesforce Query'),
    '#description' => t('The maximum number of characters a query to Salesforce can be.  If a query exceeds this limit it will be automatically broken up into multiple smaller lengthed queries.'),
    '#type' => 'textfield',
    '#size' => 6,
    '#default_value' => _sfs_get_value('max_query_length', $form_state),
  );

  // Variable to turn on automatic truncation of long strings.
  $form['salesforce_sync_truncate_long_strings'] = array(
    '#id' => 'salesforce-sync-truncate-long-strings',
    '#title' => t('Truncate Long Strings'),
    '#description' => t('Use this setting to automatically truncate a field\'s value to its max length property in Salesforce. This will prevent STRING_TOO_LONG errors on string based fields.'),
    '#type' => 'checkbox',
    '#default_value' => _sfs_get_value('salesforce_sync_truncate_long_strings', $form_state),
  );

  // Save.
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );
  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel',
  );
  return $form;
}

/**
 * Validation callback for configuration form.
 */
function salesforce_sync_admin_form_validate($form, &$form_state) {
  foreach ($form_state['input'] as $var => $value) {
    switch ($var) {
      case 'max_batch_size':
      case 'max_retrieve_size':
      case 'max_query_length':
      case 'query_limit':
        $title = $form[$var]['#title'];
        if (!is_numeric($value)) {
          form_set_error($var, 'Value for "' . $title . '" must be numeric.');
        }
        if ($value < 0) {
          form_set_error($var, 'Value for "' . $title . '" must be a positive number.');
        }
        break;
    }
  }
}

/**
 * Submit callback for the configuration form.
 */
function salesforce_sync_admin_form_submit($form, &$form_state) {
  if ($form_state['input']['op'] == 'Cancel') {
    drupal_set_message(t('The form has been reset to its original values.'));
    return;
  }
  elseif ($form_state['input']['op'] != 'Save') {
    drupal_set_message(t('The form was submitted unexpectedly.  No action was taken, nothing was saved.'), 'error');
    return;
  }

  foreach ($form_state['input'] as $var => $value) {
    switch ($var) {
      case 'max_batch_size':
      case 'max_retrieve_size':
      case 'max_query_length':
      case 'query_limit':
        $converted_value = _sfs_get_value($var, $form_state);
        variable_set('salesforce_sync_' . $var, $converted_value);
        break;
    }
  }

  variable_set('salesforce_sync_truncate_long_strings', $form_state['input']['salesforce_sync_truncate_long_strings']);
  drupal_set_message(t('Your settings have been saved.'));
}

/**
 * Helper function to find the value for the given field for the current state.
 */
function _sfs_get_value($field, $form_state) {
  $value = NULL;
  if (isset($form_state['input'][$field])) {
    $value = $form_state['input'][$field];
  }
  else {
    // Use current configured value, or default value.
    switch ($field) {
      case 'max_batch_size':
        $value = variable_get('salesforce_sync_max_batch_size', SALESFORCE_SYNC_MAX_BATCH_SIZE_DEFAULT);
        break;

      case 'max_retrieve_size':
        $value = variable_get('salesforce_sync_max_retrieve_size', SALESFORCE_SYNC_MAX_RETRIEVE_SIZE_DEFAULT);
        break;

      case 'max_query_length':
        $value = variable_get('salesforce_sync_max_query_length', SALESFORCE_SYNC_MAX_QUERY_LENGTH_DEFAULT);
        break;

      case 'query_limit':
        $value = variable_get('salesforce_sync_query_limit', SALESFORCE_SYNC_QUERY_LIMIT_DEFAULT);
        break;

      case 'salesforce_sync_truncate_long_strings':
        $value = variable_get('salesforce_sync_truncate_long_strings', SALESFORCE_SYNC_TRUNCATE_LONG_STRINGS_DEFAULT);
    }
  }
  return $value;
}
