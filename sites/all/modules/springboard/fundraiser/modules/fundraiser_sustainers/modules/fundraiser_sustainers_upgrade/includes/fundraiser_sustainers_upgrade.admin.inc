<?php

/**
 * @file
 * Sustainer upgrade admin functions.
 */

/**
 * Upgrade link generator form.
 */
function fundraiser_sustainers_upgrade_token_generator($form, $form_state) {

  $key = springboard_hmac_get_key();
  if (empty($key)) {
    drupal_set_message(t('Secure Prepopulate key and initialization vector are not set. Upgrade links will not work.'), 'error');
  }

  $uid = '';
  $amount = '';
  $did = '';
  $nid = '';
  $rollback = '';
  if (isset($_SESSION['fsu_token_generate'])) {
    $uid = $_SESSION['fsu_token_generate']['uid'];
    $amount = $_SESSION['fsu_token_generate']['amount'];
    $did = $_SESSION['fsu_token_generate']['did'];
    $nid = $_SESSION['fsu_token_generate']['nid'];
    $rollback = $_SESSION['fsu_token_generate']['rollback'];
  }

  $form['fundraiser_sustainers_upgrade'] = array(
    '#type' => 'fieldset',
    '#title' => t('Sustainers Upgrade Token'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('If you want to test a successful upgrade, a numeric, whole number value is required for every field except rollback, with real, actually-existing values for UID and Donation ID. If you want to force a failure, leave any field blank or non-numerical, or use invalid values for user or donation.'),
  );

  $form['fundraiser_sustainers_upgrade']['uid'] = array(
    '#type' => 'textfield',
    '#title' => t('User ID'),
    '#size' => 20,
    '#default_value' => $uid,
    '#description' => t('Must match the donation UID if you wish to succeed.'),
  );

  $form['fundraiser_sustainers_upgrade']['amount'] = array(
    '#type' => 'textfield',
    '#title' => t('Upgrade Amount'),
    '#description' => t('The new donation amount in cents. $20 = 2000'),
    '#default_value' => $amount,
  );

  $form['fundraiser_sustainers_upgrade']['did'] = array(
    '#type' => 'textfield',
    '#title' => t('Donation ID'),
    '#default_value' => $did,
    '#description' => t('Must belong to the UID specified above if you wish to succeed.'),
  );

  $form['fundraiser_sustainers_upgrade']['nid'] = array(
    '#type' => 'textfield',
    '#title' => t('Upgrade Form Node ID'),
    '#default_value' => $nid,
    '#description' => t('Invalid node IDs will cause a fallback to the default upgrade form.'),
  );

  $form['fundraiser_sustainers_upgrade']['rollback'] = array(
    '#type' => 'checkbox',
    '#title' => 'Rollback',
    '#default_value' => $rollback,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Generate Upgrade Link'),
  );

  $form['#submit'][] = 'fundraiser_sustainers_upgrade_token_generator_validate';
  $form['#submit'][] = 'fundraiser_sustainers_upgrade_token_generator_submit';

  return $form;
}

/**
 * Store temporary upgrade link values in session.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function fundraiser_sustainers_upgrade_token_generator_validate($form, $form_state) {
  $_SESSION['fsu_token_generate'] = $form_state['values'];
}

/**
 * Create an upgrade link.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function fundraiser_sustainers_upgrade_token_generator_submit($form, $form_state) {

  $rollback = FALSE;
  $_SESSION['next_donation'] = array();

  $payload = array(
    'uid' => $form_state['values']['uid'],
    'amount' => $form_state['values']['amount'],
    'did' => $form_state['values']['did'],
    'nid' => $form_state['values']['nid'],
  );

  if ($form_state['values']['rollback'] == 1) {
    $rollback = TRUE;
    $_SESSION['next_donation']['master_did'] = $payload['did'];
    $_SESSION['next_donation']['amount'] = $payload['amount'];
  }

  $link = fundraiser_sustainers_upgrade_create_link($payload, $rollback);

  drupal_set_message('<textarea style="width:90%;padding:10px">' . $link . '</textarea>');

  if (!empty($_SESSION['next_donation'])) {
    unset($_SESSION['next_donation']);
  }
}
