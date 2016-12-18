<?php

/**
 * @file
 * Commerce based hook for commerce_ogone.
 */

/**
 * Implements hook_fundraiser_commerce_fundraiser_gateway_info().
 */
function commerce_ogone_fundraiser_commerce_fundraiser_gateway_info() {
  return array(
    'payment_method' => array('credit', 'paypal'),
    'offsite_processing' => array('paypal'),
    'form callback' => 'commerce_ogone_fundraiser_commerce_form',
    'cleanup callback' => 'commerce_ogone_fundraiser_commerce_cleanup',
    'scrub callback' => 'commerce_ogone_fundraiser_commerce_scrub',
    'expire callback' => 'commerce_ogone_fundraiser_commerce_expire',
    'redirect callback' => 'commerce_ogone_fundraiser_commerce_redirect',
    // Validation call is commerce_ogone_fundraiser_commerce_redirect_validate
    // Submit call is commerce_ogone_fundraiser_commerce_redirect_submit
  );
}

/**
 * Callback function, use this form for the given gateway.
 */
function commerce_ogone_fundraiser_commerce_form($payment_method) {
  switch ($payment_method) {
    case 'paypal':
      $form['paypal_email'] = array(
        '#type' => 'textfield',
        '#title' => t('Paypal email'),
      );
      break;
    case 'credit':
    default:
      module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
      $form = _fundraiser_commerce_credit_card_form();
      break;
  }
  return $form;
}

/**
 * Callback function, clean up the submission results after submission before they are returned to fundraiser.
 */
function commerce_ogone_fundraiser_commerce_cleanup($submission_fields) {
  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
  return _fundraiser_commerce_credit_card_cleanup($submission_fields);
}

/**
 * Callback function, scrub data.
 */
function commerce_ogone_fundraiser_commerce_scrub($submission_fields, $payment_method) {
  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
  return _fundraiser_commerce_credit_card_scrub($submission_fields);
}

/**
 * Callback function, return the user entered experation dates for this submission.
 */
function commerce_ogone_fundraiser_commerce_expire($submission_fields) {
  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
  return _fundraiser_commerce_credit_card_expire($submission_fields);
}

/**
 * Callback function, redirection form.
 */
function commerce_ogone_fundraiser_commerce_redirect($payment_method, $donation, $order, $settings) {
  return drupal_get_form('commerce_ogone_build_redirect_form', $order, $payment_method['settings'] + $settings);
}

/**
 * Callback function, validate results on return from redirection form.
 */
function commerce_ogone_fundraiser_commerce_redirect_validate($method_instance, $donation, $order) {
  $result = FALSE;// commerce_paypal_wps_redirect_form_validate($order, $method_instance);
  $success = FALSE;
  if ($result !== FALSE) {
    $success = TRUE;
  }
  return $success;
}

/**
 * Callback function, submit results on return from redirection form.
 */
function commerce_ogone_fundraiser_commerce_redirect_submit($method_instance, $donation, $order) {
  // IMPORTANT: Transaction handling for Paypal is handled on a differnt URL, when Paypal returns the IPN tracsaction ID.
  // Therefore no additional transaction work occurs here.
  return TRUE;
}
