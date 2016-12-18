<?php

/**
 * @file
 * Commerce based hook for commerce_sagepay_direct.
 */

/**
 * Implements hook_fundraiser_commerce_fundraiser_gateway_info().
 */
function commerce_sagepay_direct_fundraiser_commerce_fundraiser_gateway_info() {
  return array(
    'payment_method' => array('credit'),
    'form callback' => 'commerce_sagepay_direct_fundraiser_commerce_form',
    'cleanup callback' => 'commerce_sagepay_direct_fundraiser_commerce_cleanup',
    'scrub callback' => 'commerce_sagepay_direct_fundraiser_commerce_scrub',
    'expire callback' => 'commerce_sagepay_direct_fundraiser_commerce_expire',
    'charge callback' => 'commerce_sagepay_direct_fundraiser_commerce_charge',
  );
}

/**
 * Callback function, use this form for the given gateway.
 */
function commerce_sagepay_direct_fundraiser_commerce_form($payment_method) {
  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
  return _fundraiser_commerce_credit_card_form();
}

/**
 * Callback function, clean up the submission results after submission before they are returned to fundraiser.
 */
function commerce_sagepay_direct_fundraiser_commerce_cleanup($submission_fields) {
  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
  return _fundraiser_commerce_credit_card_cleanup($submission_fields);
}

/**
 * Callback function, scrubs the fields for a given payment method.
 */
function commerce_sagepay_direct_fundraiser_commerce_scrub($submission_fields) {
  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
  return _fundraiser_commerce_credit_card_scrub($submission_fields);
}

/**
 * Callback function, return the user entered experation dates for this submission.
 */
function commerce_sagepay_direct_fundraiser_commerce_expire($submission_fields) {
  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
  return _fundraiser_commerce_credit_card_expire($submission_fields);
}

/**
 * Callback function, charge the gateway.
 */
function commerce_sagepay_direct_fundraiser_commerce_charge($payment_method, $donation) {
  // Translate from donation settings to the correct values for the plugin.
  $order = commerce_order_load($donation->did);
  $charge = $order->commerce_order_total[LANGUAGE_NONE][0];
  $pane_form = array(); // Spare, no values here used during submission. Ignore.
  $pane_values = array(
    'credit_card' => array(
      'number' => $donation->donation['payment_fields']['credit']['card_number'],
      'exp_month' => $donation->donation['payment_fields']['credit']['card_expiration_month'],
      'exp_year' => $donation->donation['payment_fields']['credit']['card_expiration_year'],
      'start_month' => '',
      'start_year' => '',
      'issue' => '',
      'code' => $donation->donation['payment_fields']['credit']['card_cvv'],
      'type' => '',
    ),
  );

  // Customer data for charge pulls from the customer profile given on the order, so we can ignore that.
  // If the charge fails, returns false, else nothing.
  $result = commerce_sagepay_direct_submit_form_submit($payment_method, $pane_form, $pane_values, $order, $charge);
  // No false result returned, we need to use the order status to check for success.
  // ALERT: The submission process here includes a drupal_goto. (whhhhhy!)
  // So we need to copy and paste some work over from the regular module, to avoid that.
  // THIS IS NOT READY FOR PRIMETIME.
  $success = FALSE;
  if ($result !== FALSE) {
    $success = TRUE;
  }
  return $success;
}
