<?php
// TODO NONE OF THIS IS READY TO GO. DO NOT USE THIS GATEWAY.

/**
 * @file
 * Commerce based hook for commerce_paypal.
 */

/**
 * Implements hook_fundraiser_commerce_fundraiser_gateway_info().
 */
function commerce_paypal_wpp_fundraiser_commerce_fundraiser_gateway_info() {
  return array(
    'payment_method' => array('paypal'),
    'form callback' => 'commerce_paypal_wpp_fundraiser_commerce_form',
    'charge callback' => 'commerce_paypal_fundraiser_commerce_charge',
  );
}

/**
 * Callback function, use this form for the given gateway.
 */
function commerce_paypal_wpp_fundraiser_commerce_form($payment_method) {
  $form['paypal_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Paypal email'),
  );
  return $form;
}

/**
 * Callback function, charge the gateway.
 */
function commerce_paypal_fundraiser_commerce_charge($payment_method, $donation) {
  // Paypal has two payment methods and one of them is a outsource and redirect. This is more complicated, and needs work.
}
