<?php

/**
 * @file
 * Functionality that is common to both credit and EFT glue code.
 */

/**
 * A charge function that calls the SendUpsell API method.
 *
 * @param array $payment_method
 *   Payment method data.
 * @param object $donation
 *   The donation object for the donation that corresponds to the upsell
 *   recurring series.
 * @param object $order
 *   The order object that goes along with the donation.
 * @param array $charge
 *   Information about the charge amount and currency.
 *
 * @return bool
 *   Whether the upsell API call was successful.  Determines donation success
 *   or failure.
 */
function commerce_psi_common_master_donation_upsell_charge($payment_method, $donation, $order, $charge) {

  // This will be the transaction ID from the upsdol donation.
  $upsold_remote_id = commerce_psi_common_get_transaction_remote_id_from_order($donation->fundraiser_upsell->related_did);

  if ($upsold_remote_id === FALSE) {
    // @todo What else should we do here?
    return FALSE;
  }

  $upsell_data = commerce_psi_common_format_upsell_data($payment_method, $order, $charge, $upsold_remote_id);
  $response = commerce_psi_send_upsell($payment_method, $upsell_data);

  return commerce_psi_common_save_upsell_response($payment_method, $donation, $charge, $response);
}

/**
 * Gets the remote ID for the most recently created successful transaction.
 *
 * This is used to populate the PriorOneTimeTransactionId value for the upsell
 * request.
 *
 * @param int $order_id
 *   The ID of the order for which we want the transaction.
 *
 * @return string|NULL
 *   The remote ID or FALSE if there are no results.
 */
function commerce_psi_common_get_transaction_remote_id_from_order($order_id) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'commerce_payment_transaction')
    ->propertyCondition('order_id', $order_id)
    ->propertyCondition('status', 'success')
    ->propertyOrderBy('created', 'DESC')
    ->range(0, 1);
  $result = $query->execute();
  if (isset($result['commerce_payment_transaction'])) {
    $transaction_ids = array_keys($result['commerce_payment_transaction']);
    $transactions = entity_load('commerce_payment_transaction', $transaction_ids);
    $transaction = array_shift($transactions);

    return $transaction->remote_id;
  }

  return FALSE;
}

/**
 * Creates the upsell data array for passing to PSI's API.
 *
 * @param array $payment_method
 *   The payment method data needed to get some of the values.
 * @param object $order
 *   The order object to populate values.
 * @param array $charge
 *   Charge amount and currency_code.
 * @param string $upsold_order_remote_id
 *   The transaction ID for the upsold transaction.
 *
 * @return array
 *   The formatted upsell data for the API call.
 */
function commerce_psi_common_format_upsell_data($payment_method, $order, $charge, $upsold_order_remote_id) {
  $values = array();
  $values['Amount'] = commerce_currency_amount_to_decimal($charge['amount'], $charge['currency_code']);

  $values['ClientTransactionId'] = $order->order_id;

  $values['frequency'] = 'Monthly';

  $values['PriorOneTimeTransactionId'] = $upsold_order_remote_id;

  $values['MarketSource'] = commerce_psi_get_market_source($payment_method, $order);

  $values['PayCode'] = commerce_psi_get_pay_code($payment_method, $order);

  $values['ProcessDateTime'] = date('c');

  // This is optional for the upsell request.
  $values['ProgramCode'] = commerce_psi_get_program_code($payment_method, $order);

  // This is optional for the upsell request.
  $values['SourceCode'] = commerce_psi_get_source_code($payment_method, $order);

  return $values;
}

/**
 * Creates a new transaction and saves the response from the upsell request.
 *
 * @param array $payment_method
 *   Used to save extra data to the transaction.
 * @param object $donation
 *   The related donation.
 * @param array $charge
 *   The charge data.
 * @param object $response
 *   The response returned from PSI.
 *
 * @return bool
 *   Whether the response was successful.
 */
function commerce_psi_common_save_upsell_response($payment_method, $donation, $charge, $response) {
  // Prepare a transaction object.
  $transaction = commerce_payment_transaction_new($donation->gateway['id'], $donation->did);
  $transaction->instance_id = $payment_method['instance_id'];
  $transaction->amount = $charge['amount'];
  $transaction->currency_code = $charge['currency_code'];
  $transaction->status = COMMERCE_PAYMENT_STATUS_PENDING;

  // If no response bail out and ask them to try again.
  if (empty($response)) {
    $transaction->status = COMMERCE_PAYMENT_STATUS_FAILURE;
    $transaction->message = 'The PSI API did not respond.';
    commerce_payment_transaction_save($transaction);
    fundraiser_donation_decline($donation);
    return FALSE;
  }

  $transaction->payload[REQUEST_TIME] = $response;
  $transaction->remote_id = $response->ClientTransactionId;

  // Mark as success if we get back a 1 or 4.
  if (in_array((int) $response->ResponseCode, array(1, 4))) {
    $success = TRUE;
  }
  else {
    $success = FALSE;
  }

  $transaction->status  = $success ? COMMERCE_PAYMENT_STATUS_SUCCESS : COMMERCE_PAYMENT_STATUS_FAILURE;
  $transaction->remote_status = $response->Approved;

  // Build the response message.
  $transaction->message = '<b>!status:</b> !response_message Response code: !response_code; Reason code: !reason_code';
  $transaction->message_variables = array(
    '!status' => $success ? t('APPROVED') : t('FAILED'),
    '!response_message' => check_plain($response->ResponseMessage),
    '!response_code' => $response->ResponseCode,
    '!reason_code' => $response->ReasonCode,
  );

  if ($success) {
    $transaction->message .= '; Authorization code: !auth_code';
    $transaction->message_variables['!auth_code'] = $response->AuthorizationCode;
  }

  // Save the transaction information.
  commerce_payment_transaction_save($transaction);

  if ($success) {

    return TRUE;
  }

  return FALSE;
}
