<?php

/**
 * @file
 * Admin settings form and associated functions.
 */

/**
 * Admin settings form.
 */
function fundraiser_date_mode_admin() {
  $form['fundraiser_date_mode_set_date_mode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Set date mode'),
    '#default_value' => variable_get('fundraiser_date_mode_set_date_mode', FALSE),
    '#description' => t('Process all sustainer charges on a set date each month.
      If this checkbox is left unchecked, sustainers will instead be processed
      on the date of their anniversary. NOTE: Turning this feature on will convert
      current sustainers to the new date for all future (and only future) charges.
      Turning this feature off thereafter will revert future charges to anniversary.'),
  );
  // Date capped at 28 because of Feb.
  $dates = array_combine(range(1, 28), range(1, 28));
  $form['fundraiser_date_mode_set_dates'] = array(
    '#type' => 'select',
    '#title' => t('Process date'),
    '#description' => t('Select the day of each month to process sustainers.'),
    '#options' => $dates,
    '#multiple' => FALSE,
    '#default_value' => variable_get('fundraiser_date_mode_set_dates', '15'),
  );
  $form['cron_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Sustainer processing'),
  );
  $form['cron_settings']['fundraiser_date_mode_batch_record_count'] = array(
    '#type' => 'textfield',
    '#size' => 6,
    '#title' => t('# of records to batch per run'),
    '#default_value' => variable_get('fundraiser_date_mode_batch_record_count', 1000),
  );
  $form['cron_settings']['fundraiser_date_mode_skip_on_cron'] = array(
    '#type' => 'checkbox',
    '#title' => t('Skip sustainer processing queue on cron'),
    '#description' => t('If this is checked the sustainer order queue will not be processed when cron is run.'),
    '#default_value' => variable_get('fundraiser_date_mode_skip_on_cron', TRUE),
  );
  $seconds = array_combine(range(1, 60), range(1, 60));
  $form['cron_settings']['fundraiser_date_mode_set_seconds'] = array(
    '#type' => 'select',
    '#title' => t('Seconds spent'),
    '#description' => t('Set how many seconds for each drupal queue run to spend on the queue processing sustainer charges.
      If drupal queue is running as part of drupal cron, leave this at about 30 seconds or less so it won\'t time out.
      If drupal queue is running standalone through drush then this can be higher to process more sustainers in a single run.'),
    '#options' => $seconds,
    '#default_value' => variable_get('fundraiser_date_mode_set_seconds', 30),
  );

  $form['batch_warning'] = array(
    '#type' => 'markup',
    '#markup' => '<div><p><strong>Warning:</strong>  Changing the settings ' .
      'will start off a batch process that needs to be completed. About ' .
      fundraiser_date_mode_max_records() .
      ' records will need to be updated.  These changes will affect future scheduled charges. ' .
      'However this will not include any scheduled charges in the current month ' .
      'to prevent charges from being rescheduled into the past. ' .
      'Beware that changing these settings repeatedly could have side effects.</p></div>',
  );
  $form['#submit'][] = 'fundraiser_date_mode_admin_submit';
  return system_settings_form($form);
}

/**
 * Additional submit handler for admin settings form.
 *
 * Generates batch and performs batch operations as needed when date mode
 * settings call for updating next_charge dates.
 */
function fundraiser_date_mode_admin_submit($form, $form_state) {
  $date_mode_setting = variable_get('fundraiser_date_mode_set_date_mode', FALSE);
  $date_setting = variable_get('fundraiser_date_mode_set_dates', '15');

  $mode_changed = !($date_mode_setting == $form_state['values']['fundraiser_date_mode_set_date_mode']);
  $date_changed = !($date_setting == $form_state['values']['fundraiser_date_mode_set_dates']);
  if ($mode_changed && $form_state['values']['fundraiser_date_mode_set_date_mode']) {
    $op = 'date_mode_enabled';
  }
  elseif ($mode_changed && !$form_state['values']['fundraiser_date_mode_set_date_mode']) {
    $op = 'date_mode_disabled';
  }
  elseif ($date_changed && $form_state['values']['fundraiser_date_mode_set_date_mode']) {
    $op = 'date_mode_date_changed';
  }
  // Date mode setting has changed or date mode is enabled and the process date
  // has changed.
  if ($mode_changed || ($form_state['values']['fundraiser_date_mode_set_date_mode'] && $date_changed)) {
    $batch = fundraiser_date_mode_update_date_mode_batch($op, $form_state['values']['fundraiser_date_mode_set_dates']);
    batch_set($batch);
  }
}

/**
 * Creates a batch of sustainer series that need next_charge dates updated.
 */
function fundraiser_date_mode_update_date_mode_batch($op, $date) {
  // TODO: do we need $time for anything?
  $time = '01:01:01';
  $operations = array();
  $now = time();
  $series_data = fundraiser_date_mode_get_sustainer_series_data();
  $master_ids = array_keys($series_data);
  $max = count($master_ids);
  foreach ($master_ids as $master_id) {
    // We pass mode, date, and time to every operation call even though they
    // don't change.
    $params = array(
      $op,
      $date,
      $time,
      $master_id,
      $max,
      $series_data[$master_id],
    );
    $operations[] = array('fundraiser_date_mode_update_date_mode_operation', $params);
  }

  $batch = array(
    'operations' => $operations,
    'finished' => 'fundraiser_date_mode_update_date_mode_finished',
    'title' => t('Processing sustainers for date mode update'),
    'init_message' => t('Date mode update is starting.'),
    'progress_message' => t('Processed @current sustainer sets out of @total.'),
    'error_message' => t('The date mode update has encountered an error.'),
  );
  return $batch;
}
