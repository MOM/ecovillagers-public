<?php
/**
 * @file
 * Enables modules and site configuration for a standard site installation.
 */

/**
 * Implements hook_install_tasks().
 */
function sbsetup_install_tasks(&$install_state) {
  $tasks = array();
  $tasks['sbsetup_setup'] = array(
    'display_name' => st('Setup Springboard'),
    'display' => TRUE,
    'type' => 'normal',
    'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
    'function' => 'sbsetup_setup',
  );
  return $tasks;
}

/**
 * Install task callback.
 */
function sbsetup_setup(&$install_state) {
  module_load_include('admin.inc', 'springboard');
  $form = array();
  $form_state = array(
    'values' => array(
      'order_handling' => 'commerce',
      'sf_enable' => TRUE,
      'sf_donation' => TRUE,
      'sf_npsp' => TRUE,
      'sf_key' => '',
      'sf_secret' => '',
    ),
  );
  springboard_admin_config($form, $form_state);
}
