<?php

/**
 * @file Admin settings for cleaning up the webform_confirmations_submissions table during cron.
 */

/**
 * Admin settings form.
 */
function webform_confirmations_admin_settings() {
  $form['webform_confirmations_submissions_purge_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Purge old confirmation permission records when cron is run.'),
    '#default_value' => variable_get('webform_confirmations_submissions_purge_enabled', FALSE),
  );
  $form['webform_confirmations_submissions_clear_date'] = array(
    '#type' => 'textfield',
    '#title' => t('Clear out confirmation permission records after this many days'),
    '#size' => 4,
    '#default_value' => variable_get('webform_confirmations_submissions_clear_date', 90),
    '#description' => t('Confirmation permission records are what prevent users from
      seeing each other\'s confirmation pages. This table can grow quickly thus degrading
      the site\'s performance.'),
  );

  return system_settings_form($form);
}
