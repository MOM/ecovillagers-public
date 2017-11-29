<?php

/**
 * @file
 * Commerce based hook for commerce_psi EFT.
 */

/**
 * Implements hook_fundraiser_commerce_fundraiser_gateway_info().
 */
function commerce_psi_eft_fundraiser_commerce_fundraiser_gateway_info() {
  return array(
    'payment_method' => array('bank account'),
    'allow_recurring' => array('bank account'),
    'offsite_recurring' => array('bank account'),
    'offsite_recurring_external' => array('bank account'),
    'form callback' => 'commerce_psi_eft_fundraiser_commerce_submit_form',
    'cleanup callback' => 'commerce_psi_eft_fundraiser_commerce_cleanup',
    'scrub callback' => 'commerce_psi_eft_fundraiser_commerce_scrub',
    'validate callback' => 'commerce_psi_eft_fundraiser_commerce_validate',
    'charge callback' => 'commerce_psi_eft_fundraiser_commerce_charge',
  );
}

/**
 * Implements hook_fundraiser_donation_form_config_check().
 */
function commerce_psi_eft_fundraiser_donation_form_config_check($node) {
  foreach ($node->gateways as $method => $gateway) {
    if (!empty($gateway['id']) && !empty($gateway['status'])) {
      $gateway_config = _fundraiser_gateway_info($gateway['id']);
      if ($gateway_config['gateway_details']['method_id'] == 'commerce_psi_eft' &&
        $gateway_config['gateway_details']['settings']['txn_mode'] != COMMERCE_PSI_MODE_LIVE) {
        return array(t('The PSI EFT payment gateway is currently in !mode mode and will not process live transactions.', array('!mode' => $gateway_config['gateway_details']['settings']['txn_mode'])));
      }
    }
  }
}

function commerce_psi_eft_fundraiser_gateway_status_cron_check($details) {
  if ($details['method_id'] == 'commerce_psi_eft') { 
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
 *
 * @param string $payment_method
 *   Credit, bank account, paypal, etc.
 * @param array $config
 *   Configuration options for this field.
 */
function commerce_psi_eft_fundraiser_commerce_submit_form($payment_method, $config) {
  $method_instance = commerce_payment_method_instance_load($config['id']);
  $form = commerce_psi_eft_submit_form($method_instance);
  // Remove the required flag for the fields
  foreach (element_children($form['bank_account']) as $field_name) {
    $form['bank_account'][$field_name]['#required'] = FALSE;
  }
  return $form['bank_account'];
}

/**
 * Callback function, scrub the data before saving.
 */
function commerce_psi_eft_fundraiser_commerce_scrub($fields) {
  // Scrub sensitive donation fields if they exists.
  if (isset($fields['bank account']['routing_number'])) {
    $fields['bank account']['routing_number'] = substr($fields['bank account']['routing_number'], -3);
  }
  if (isset($fields['bank account']['account_number'])) {
    $fields['bank account']['account_number'] = substr($fields['bank account']['account_number'], -3);
  }
  // Value added by commerce
  unset($fields['bank account']['confirm_account_number']);
  return $fields;
}

/**
 * Validate the submitted values with the psi_commerce validate function.
 */
function commerce_psi_eft_fundraiser_commerce_validate($submission_fields, $payment_fields) {
  $form_parents = array_merge($payment_fields['#parents'], array('bank account'));
  $values = array('bank_account' => $submission_fields['payment_fields']['bank account']);
  commerce_psi_eft_submit_form_validate(NULL, $payment_fields, $values, NULL, $form_parents);
  return $submission_fields;
}

/**
 * Submit the donation values to the PSI EFT charge handler.
 *
 * @param array $method_instance
 *   Commerce loaded method instance.
 * @param object $donation
 *   The donation to charge.
 *
 * @return bool
 *   Whether the charge was successful.
 */
function commerce_psi_eft_fundraiser_commerce_charge($method_instance, $donation) {
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

  $pane_values = array(
    'bank_account' => $donation->donation['payment_fields']['bank account'],
    'frequency' => $donation->donation['recurs_monthly'] == TRUE ? 'Monthly' : NULL,
  );

  // Execute call to PSI, only returns FALSE if the payment failed,
  // returns nothing if successful.
  $result = commerce_psi_eft_submit_form_submit($method_instance, $pane_form, $pane_values, $order, $charge);
  $success = FALSE;
  if ($result !== FALSE) {
    $success = TRUE;
  }
  return $success;
}
