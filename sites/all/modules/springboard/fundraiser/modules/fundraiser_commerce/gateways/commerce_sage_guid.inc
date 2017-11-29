<?php

/**
 * @file
 * Fundraiser based hook for commerce_sage_guid.
 */

/**
 * Implements hook_fundraiser_commerce_fundraiser_gateway_info().
 */
function commerce_sage_guid_fundraiser_commerce_fundraiser_gateway_info() {
  return array(
    'payment_method' => array('commerce_sage_guid' => 'guid'),
    'allow_recurring' => array('guid'),
    'form callback' => 'commerce_sage_guid_fundraiser_commerce_submit_form',
    'charge callback' => 'commerce_sage_guid_fundraiser_commerce_charge',
  );
}

/**
 * Returns the form fields for this method.
 */
function commerce_sage_guid_fundraiser_commerce_submit_form($payment_method, $config = NULL) {
  $method_instance = commerce_payment_method_instance_load($config['id']);
  $form = commerce_sage_guid_submit_form($method_instance);

  return $form;
}

/**
 * Charge callback for the commerce_sage_guid method.
 *
 * This function differs from many other gateway charge functions. It validates
 * the passed in GUID and creates a cardonfile record. It then switches the
 * donation over to another gateway for final processing.
 */
function commerce_sage_guid_fundraiser_commerce_charge($method_instance, $donation) {
  $order = commerce_order_load($donation->did);
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);

  $guid = $donation->donation['payment_fields']['guid']['guid'];
  // Query the Sage Vault for this guid.
  $request_parameters = [
    'GUID' => $guid,
  ];

  // Load the payment gateway that will be used to process these charges.
  if (!empty($method_instance['settings']['sage_payment_cc_gateway'])) {
    $instance_id = $method_instance['settings']['sage_payment_cc_gateway'];
    $processing_method = commerce_payment_method_instance_load($instance_id);
    $request_parameters += _commerce_sage_payments_get_sage_payments_config($processing_method);
  }

  // If there isn't a selected cc config we can't proccess.
  if (empty($processing_method)) {
    drupal_set_message(t('A valid Sage Payment configuration was not found.'));
    return FALSE;
  }

  // Check if there's a local card already existing.
  $card_data = _commerce_sage_guid_get_cardonfile($guid);

  // If no local card data for this guid make a cardonfile entry now.
  if (empty($card_data)) {

    try {
      $vault_client = _commerce_sage_payments_get_sage_payments_vault_management_client();
      $response = $vault_client->SELECT_DATA($request_parameters);
    }
    catch (Exception $e) {
      drupal_set_message(t('There was an error connecting to the Sage Vault'));
      return FALSE;
    }

    // If we got a response validate it returned a result.
    if (
      !empty($response)
      && !empty($response->SELECT_DATAResult)
    ) {
      // Break the GUID apart and determine if this is a card or bank account.
      $guid_parts = explode('|', $response->SELECT_DATAResult);

      // Credit card is two parts.
      if (count($guid_parts) == 2) {
        $card_number = $guid_parts[0];
        list($card_exp_month, $card_exp_year) = str_split($guid_parts[1], 2);

        // Generate the values needed for the cardonfile record.
        $card_exp_year = '20' . $card_exp_year;
        // Get the card type.
        module_load_include('inc', 'commerce_payment', 'includes/commerce_payment.credit_card');
        $all_types = array_keys(commerce_payment_credit_card_types());
        $card_type = commerce_payment_validate_credit_card_type($card_number, $all_types);

        // Reduce the card number to the last four.
        $card_number = substr($card_number, -4);
      }
      // ETF is three parts and we don't support it.
      elseif (count($guid_parts) == 3) {
        drupal_set_message(t('This GUID is ETF and is not supported.'));
        return FALSE;
      }
      // A different format can't be processed for now.
      else {
        drupal_set_message(t('There was an error processing this GUID.'));
        return FALSE;
      }

      // Get the card name from the billing address.
      $card_name = '';
      if ($order_wrapper->commerce_customer_billing->value()) {
        $billing_address = $order_wrapper->commerce_customer_billing->commerce_customer_address->value();
        $card_name = $billing_address['name_line'];
      }

      // Save a new cardonfile entry.
      $card_data = commerce_cardonfile_new();
      $card_data->uid = $donation->uid;
      $card_data->payment_method = $processing_method['base'];
      $card_data->instance_id = $processing_method['instance_id'];
      $card_data->remote_id = $guid;
      $card_data->card_type = !empty($card_type) ? $card_type : 'card';
      $card_data->card_number = $card_number;
      $card_data->card_exp_month = $card_exp_month;
      $card_data->card_exp_year = $card_exp_year;
      $card_data->card_name = $card_name;
      $card_data->status = 1;
      commerce_cardonfile_save($card_data);
    }
    // If we didn't load a result send the user back to the form.
    else {
      drupal_set_message(t('The GUID was not found in the Sage Vault.'), 'error');
      return FALSE;
    }
  }

  // Add these values to the donation under the payment and data arrays.
  $donation->donation['payment_method'] = $donation->data['payment_method'] = 'credit';
  $donation->donation['payment_fields']['credit'] = array(
    'card_number' => $card_data->card_number,
    'card_expiration_month' => $card_data->card_exp_month,
    'card_expiration_year' => $card_data->card_exp_year,
    'code' => '',
  );
  $donation->data['payment_fields'] = $donation->donation['payment_fields'];

  // Add values to the pane values.
  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
  $pane_values = _fundraiser_commerce_credit_card_pane_values($donation);
  $pane_values['cardonfile'] = $card_data->card_id;

  // Translate from donation settings to the correct values for the plugin.
  $charge = $order_wrapper->commerce_order_total->value();
  if (!isset($charge['recurs_monthly']) && isset($donation->donation['recurs_monthly'])) {
    $charge['recurs_monthly'] = $donation->donation['recurs_monthly'];
  }

  // Execute call to Sage depending on what payment method we have.
  $result = commerce_sage_payments_cc_vault_submit_form_submit($processing_method, array(), $pane_values, $order, $charge);

  $success = FALSE;
  if ($result !== FALSE) {
    $success = TRUE;
  }

  if ($success) {
    // Reset the gateway on this donation.
    $donation->gateway = _fundraiser_gateway_info($processing_method['instance_id']);
    $donation->data['cardonfile'] = $card_data->card_id;
  }

  // Perform post processing functions.
  _fundraiser_commerce_charge_submit_form_process($success, $processing_method, $pane_values, $donation);

  return $success;
}
