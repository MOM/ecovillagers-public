<?php

/**
 * @file
 * Admin form.
 */

/**
 * Silverpop Sendmail admin form.
 */
function silverpop_transact_admin() {

  $form = array();
  $form['silverpop_transact_model'] = array(
    '#type' => 'radios',
    '#title' => t('Silverpop Transact API mode'),
    '#options' => array(
      'SMTP' => t('SMTP'),
      'XML' => t('XML'),
    ),
    '#default_value' => variable_get('silverpop_transact_model', 'SMTP'),
    '#description' => 'See module documentation for more information about these two options.',
    '#required' => TRUE,
  );
  $form['silverpop_transact_apihost'] = array(
    '#type' => 'select',
    '#title' => t('Silverpop API host'),
    '#options' => array(
      '1' => '1',
      '2' => '2',
      '3' => '3',
      '4' => '4',
      '5' => '5',
    ),
    '#default_value' => variable_get('silverpop_transact_apihost'),
    '#description' => 'Your API host is typically your engage pod number (e.g.
        Pod 5 would use api5.silverpop.com).',
    '#required' => TRUE,
  );
  $form['silverpop_transact_xheader_value'] = array(
    '#type' => 'textfield',
    '#title' => t('Default X Header value'),
    '#default_value' => variable_get('silverpop_transact_xheader_value'),
    '#description' => 'The site-wide default value of the X-SP-Transact-Id X Header that is used to match a message to a Transaction Group.',
    '#states' => array(
      'visible' => array(
        ':input[name="silverpop_transact_model"]' => array('value' => 'SMTP'),
      ),
    ),
  );
  $form['silverpop_transact_api'] = array(
    '#type' => 'fieldset',
    '#title' => t('Silverpop API Credentials'),
    '#states' => array(
      'visible' => array(
        ':input[name="silverpop_transact_model"]' => array('value' => 'XML'),
      ),
    ),
  );
  $form['silverpop_transact_api']['silverpop_transact_mailing_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Default Silverpop Mailing ID'),
    '#default_value' => variable_get('silverpop_transact_mailing_id'),
    '#states' => array(
      'required' => array(
        ':input[name="silverpop_transact_model"]' => array('value' => 'XML'),
      ),
    ),
  );
  $form['silverpop_transact_api']['silverpop_transact_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Silverpop Transact username'),
    '#default_value' => variable_get('silverpop_transact_username', ''),
    '#size' => 60,
    '#maxlength' => 255,
    '#description' => 'The username you use to log into the Silverpop
        administrative portal.',
    '#states' => array(
      'required' => array(
        ':input[name="silverpop_transact_model"]' => array('value' => 'XML'),
      ),
    ),
  );
  $form['silverpop_transact_api']['silverpop_transact_password'] = array(
    '#type' => 'password',
    '#title' => t('Silverpop Transact password'),
    '#size' => 60,
    '#maxlength' => 255,
    '#description' => 'The password you use to log into the Silverpop
        administrative portal.',
    '#states' => array(
      'required' => array(
        ':input[name="silverpop_transact_model"]' => array('value' => 'XML'),
      ),
    ),
  );
  $form['silverpop_transact_api']['silverpop_transact_submit_on_cron'] = array(
    '#type' => 'checkbox',
    '#title' => t('Send messages on cron'),
    '#default_value' => variable_get('silverpop_transact_submit_on_cron', ''),
    '#description' => 'Queue messages for cron run rather than sending immediately.',
  );
  $form['silverpop_transact_row_limit'] = array(
    '#type' => 'select',
    '#title' => t('Log retention'),
    '#default_value' => variable_get('silverpop_transact_row_limit', 10000),
    '#options' => array(0 => t('All')) + drupal_map_assoc(array(10000, 100000, 1000000)),
    '#description' => t('The maximum number of messages to keep in the silverpop transact log. Requires a <a href="@cron">cron maintenance task</a>. Set high enough so that pending messages are not deleted before they can be submitted to Silverpop', array('@cron' => url('admin/reports/status')))
  );
  $form['#submit'] = array(
    'silverpop_transact_encrypt_password',
    'sliverpop_transact_admin_form_submit',
  );
  $form = system_settings_form($form);
  return $form;
}

/**
 * Encrypt password (if necessary).
 *
 * Function borrowed from http://drupal.org/project/silverpop.
 */
function silverpop_transact_encrypt_password($form, &$form_state) {

  // Encrypt the API password.
  if (!empty($form_state['values']['silverpop_transact_password'])) {
    $password = $form_state['values']['silverpop_transact_password'];
    $form_state['values']['silverpop_transact_password'] = silverpop_transact_set_password($password);
  }
  else {
    $form_state['values']['silverpop_transact_password'] = silverpop_transact_get_password(FALSE);
  }
}

/**
 * Implements hook_form_submit().
 */
function sliverpop_transact_admin_form_submit($form_id, &$form_state) {
  // Check if XML/SMTP model has been changed. When SMTP is enabled, switch to
  // use the mailsystem provided by the smtp module.
  if ($form_state['input']['silverpop_transact_model'] != variable_get('silverpop_transact_model')) {
    $mail_modes = variable_get('mail_system');
    // SMTP on.
    if ($form_state['input']['silverpop_transact_model'] == 'SMTP') {
      $mail_modes['email_wrappers'] = 'SmtpMailSystem';
      $mail_modes['default-system'] = 'SmtpMailSystem';
      variable_set('mail_system', $mail_modes);
    }
    // SMTP off.
    else {
      $mail_modes['email_wrappers'] = 'EmailWrappersMailSystemInterface';
      $mail_modes['default-system'] = 'DefaultMailSystem';
      variable_set('mail_system', $mail_modes);
    }
  }

  // Check if API host has changed. If so, change the smtp host to match
  // e.g. transact5.silverpop.com.
  if ($form_state['input']['silverpop_transact_apihost'] != variable_get('silverpop_transact_apihost')) {
    $smtp_host = str_replace('%', $form_state['input']['silverpop_transact_apihost'], SILVERPOP_TRANSACT_SMTP_ADDRESS);
    variable_set('smtp_host', $smtp_host);
  }

  // Test XML credentials.
  if ($form_state['input']['silverpop_transact_model'] == 'XML') {
    if (!silverpop_transact_connect($form_state['input']['silverpop_transact_apihost'], $form_state['input']['silverpop_transact_username'], $form_state['input']['silverpop_transact_password'])) {
      drupal_set_message(t('Unable to connect to the Silverpop Transact API. Please check the credientials and API Host and try again.'), 'error');
    }
    else {
      drupal_set_message(t('Successfully connected to the Silverpop Transact API.'), 'status');
    }
  }

}
