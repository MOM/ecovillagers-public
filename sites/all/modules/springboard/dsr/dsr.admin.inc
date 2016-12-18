<?php
/**
 * @file
 * Admin functions for the DSR module.
 */

/**
 * DSR settings form.
 */
function dsr_settings() {
  $form['email_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Email report settings'),
    '#collapsible' => TRUE,
  );
  $form['email_settings']['dsr_reconciliation_summary_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Reconciliation summary report email'),
    '#description' => t('Enter the email address where the DSR reconciliation summary report should be sent.'),
    '#default_value' => variable_get('dsr_reconciliation_summary_email', ''),
    '#weight' => -3,
    '#maxlength' => 256,
  );

  // Starting default values for SOQL queries are defined in dsr_install()
  // and dsr_update_6001().
  $form['soql_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Report SOQL settings'),
    '#collapsible' => TRUE,
  );

  // Selects.
  $form['soql_settings']['selects'] = array(
    '#type' => 'fieldset',
    '#title' => t('SOQL selects'),
    '#collapsible' => TRUE,
  );
  $form['soql_settings']['selects']['dsr_posted_select_s'] = array(
    '#type' => 'textarea',
    '#title' => t('Posted donations'),
    '#default_value' => variable_get('dsr_posted_select_s', DSR_DEFAULT_SELECT_SOQL),
  );
  $form['soql_settings']['selects']['dsr_refunded_select_s'] = array(
    '#type' => 'textarea',
    '#title' => t('Refunded donations'),
    '#default_value' => variable_get('dsr_refunded_select_s', DSR_DEFAULT_SELECT_SOQL),
  );
  $form['soql_settings']['selects']['dsr_partially_refunded_select_s'] = array(
    '#type' => 'textarea',
    '#title' => t('Refunded donations'),
    '#default_value' => variable_get('dsr_partially_refunded_select_s', DSR_DEFAULT_SELECT_SOQL),
  );

  // Aggregates.
  $form['soql_settings']['aggregates'] = array(
    '#type' => 'fieldset',
    '#title' => t('SOQL aggregates'),
    '#collapsible' => TRUE,
  );
  $form['soql_settings']['aggregates']['dsr_posted_aggregate_s'] = array(
    '#type' => 'textarea',
    '#title' => t('Posted aggregate'),
    '#default_value' => variable_get('dsr_posted_aggregate_s', DSR_DEFAULT_AGGREGATE_SOQL),
  );
  $form['soql_settings']['aggregates']['dsr_refunded_aggregate_s'] = array(
    '#type' => 'textarea',
    '#title' => t('Refunded aggregate'),
    '#default_value' => variable_get('dsr_refunded_aggregate_s', DSR_DEFAULT_AGGREGATE_SOQL),
  );
  $form['soql_settings']['aggregates']['dsr_partially_refunded_aggregate_s'] = array(
    '#type' => 'textarea',
    '#title' => t('Partially refunded aggregate'),
    '#default_value' => variable_get('dsr_partially_refunded_aggregate_s', DSR_DEFAULT_AGGREGATE_SOQL),
  );

  /*
     */
  return system_settings_form($form);
}
