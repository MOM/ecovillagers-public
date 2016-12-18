<?php

/**
 * @file
 * Admin functions for springboard_honeypot module.
 */

/**
 * Admin settings for springboard_honeypot.
 */
function springboard_honeypot_admin_form($form, &$form_state) {
  $form['springboard_honeypot_count_threshold'] = array(
    '#type' => 'textfield',
    '#title' => t('Honeypot blacklist count threshold'),
    '#description' => t('Maximum number of Honeypot validation failures tolerated before adding IP to the system blacklist.'),
    '#default_value' => variable_get('springboard_honeypot_count_threshold', 50),
    '#required' => TRUE,
    '#size' => 5,
  );

  $form['springboard_honeypot_timer_blacklist'] = array(
    '#type' => 'textarea',
    '#title' => t('Honeypot timer blacklist'),
    '#description' => t('Forms that should not use Honeypot\'s timer validation. Use this setting to turn off the timer on specfic forms without turning it off globally. Enter one form id per line.'),
    '#default_value' => variable_get('springboard_honeypot_timer_blacklist', ''),
  );

  return system_settings_form($form);
}
