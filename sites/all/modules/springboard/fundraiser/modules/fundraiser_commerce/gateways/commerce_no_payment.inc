<?php

/**
 * @file
 * Commerce based hook for commerce_cheque.
 */

/**
 * Implements hook_fundraiser_commerce_fundraiser_gateway_info().
 */
function commerce_no_payment_fundraiser_commerce_fundraiser_gateway_info() {
  return array(
    'payment_method' => array('none'),
    'form callback' => 'commerce_no_payment_fundraiser_commerce_form',
    'charge callback' => 'commerce_no_payment_fundraiser_commerce_charge',
  );
}

/**
 * Callback function, use this form for the given gateway.
 */
function commerce_no_payment_fundraiser_commerce_form($payment_method) {
  $form['check_message'] = array(
    '#markup' => '<div class="payment-method-message">' .
      t('Enjoy your free stuff.') .
      '</div>',
  );
  return $form;
}

/**
 * Callback function, charge the gateway.
 */
function commerce_no_payment_fundraiser_commerce_charge($payment_method, $donation) {
  // Translate from donation settings to the correct values for the plugin.
  $order = commerce_order_load($donation->did);
  $charge = $order->commerce_order_total[LANGUAGE_NONE][0];
  $name = $donation->donation['first_name'] . ' ' . $donation->donation['last_name'];
  $success = FALSE;
  if ($charge['amount'] <= 0) {
    $result = commerce_no_payment_transaction($payment_method, $order, $charge, $name);
  }
  return TRUE;
}
