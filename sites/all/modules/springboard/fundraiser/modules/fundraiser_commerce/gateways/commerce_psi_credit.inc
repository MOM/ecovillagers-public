<?php

/**
 * @file
 * Commerce based hook for commerce_psi Credit.
 */

/**
 * Implements hook_fundraiser_commerce_fundraiser_gateway_info().
 */
function commerce_psi_credit_fundraiser_commerce_fundraiser_gateway_info() {
  return array(
    'payment_method' => array('credit'),
    'allow_recurring' => array('credit'),
    'offsite_recurring' => array('credit'),
    'form callback' => 'commerce_psi_credit_fundraiser_commerce_submit_form',
    'cleanup callback' => 'commerce_psi_credit_fundraiser_commerce_cleanup',
    'scrub callback' => 'commerce_psi_credit_fundraiser_commerce_scrub',
    'validate callback' => 'commerce_psi_credit_fundraiser_commerce_validate',
    'expire callback' => 'commerce_psi_credit_fundraiser_commerce_expire',
    'charge callback' => 'commerce_psi_credit_fundraiser_commerce_charge',
  );
}

/**
 * Implements hook_fundraiser_donation_form_config_check().
 */
function commerce_psi_credit_fundraiser_donation_form_config_check($node) {
  foreach ($node->gateways as $method => $gateway) {
    if (!empty($gateway['id']) && !empty($gateway['status'])) {
      $gateway_config = _fundraiser_gateway_info($gateway['id']);
      if ($gateway_config['gateway_details']['method_id'] == 'commerce_psi_credit' &&
        $gateway_config['gateway_details']['settings']['txn_mode'] != COMMERCE_PSI_MODE_LIVE) {
        return array(t('The PSI credit payment gateway is currently in !mode mode and will not process live transactions.', array('!mode' => $gateway_config['gateway_details']['settings']['txn_mode'])));
      }
    }
  }
}

function commerce_psi_credit_fundraiser_gateway_status_cron_check($details) {
  if ($details['method_id'] == 'commerce_psi_credit') { 
    if ($details['settings']['txn_mode'] != COMMERCE_PSI_MODE_LIVE) {
      return $details['settings']['txn_mode'];
    }
    else {
      return 'live';
    }
  } 
}

/**
 * Returns the form fields for this method.
 */
function commerce_psi_credit_fundraiser_commerce_submit_form($payment_method, $config) {
  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
  return _fundraiser_commerce_credit_card_form();
}

/**
 * Convert values to ones that Fundraiser Commerce is looking for.
 */
function commerce_psi_credit_fundraiser_commerce_cleanup($submission_fields) {
  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
  return _fundraiser_commerce_credit_card_cleanup($submission_fields);
}

/**
 * Expiration callback function.
 *
 * Return the user entered expiration date for this submission.
 */
function commerce_psi_credit_fundraiser_commerce_expire($submission_fields) {
  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
  return _fundraiser_commerce_credit_card_expire($submission_fields);
}

/**
 * Callback function, scrub the data before saving.
 */
function commerce_psi_credit_fundraiser_commerce_scrub($submission_fields) {
  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
  return _fundraiser_commerce_credit_card_scrub($submission_fields);
}

/**
 * Validate the submitted values with the commerce validate function.
 */
function commerce_psi_credit_fundraiser_commerce_validate($submission_fields, $payment_fields) {
  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
  $form_parents = array_merge($payment_fields['#parents'], array('credit'));
  _fundraiser_commerce_credit_card_validate($submission_fields, $form_parents);
  return $submission_fields;
}

/**
 * Submit the donation values to the PSI credit charge handler.
 *
 * @param array $method_instance
 *   Commerce loaded method instance.
 * @param object $donation
 *   The donation to charge.
 *
 * @return bool
 *   Whether the charge was successful.
 */
function commerce_psi_credit_fundraiser_commerce_charge($method_instance, $donation) {
  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
  // Translate from donation settings to the correct values for the plugin.
  $order = commerce_order_load($donation->did);
  $wrapper = entity_metadata_wrapper('commerce_order', $order);
  $charge = $wrapper->commerce_order_total->value();

  // See if we have an upsell master donation and if so call the SendUpsell
  // API call instead of the usual charging.
  // This will initiate an immediate charge as well as an offsite
  // recurring series.
  if (isset($donation->fundraiser_upsell->type) && $donation->fundraiser_upsell->type == 'master_donation') {
    module_load_include('inc', 'fundraiser_commerce', 'gateways/commerce_psi_common');
    return commerce_psi_common_master_donation_upsell_charge($method_instance, $donation, $order, $charge);
  }

  // Not actually used anywhere in this system, so ignore it.
  $pane_form = array();

  $pane_values = _fundraiser_commerce_credit_card_pane_values($donation);
  $pane_values['frequency'] = $donation->donation['recurs_monthly'] == TRUE ? 'Monthly' : NULL;

  // Execute call to PSI, only returns FALSE if the payment failed,
  // returns nothing if successful.
  $result = commerce_psi_credit_submit_form_submit($method_instance, $pane_form, $pane_values, $order, $charge);
  $success = FALSE;
  if ($result !== FALSE) {
    $success = TRUE;
  }
  return $success;
}
