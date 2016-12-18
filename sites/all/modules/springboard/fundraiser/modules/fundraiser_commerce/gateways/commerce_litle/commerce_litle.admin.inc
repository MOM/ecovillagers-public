<?php

/**
 * @file
 * Administrative forms for the Litle module.
 */


/**
 * Form callback: allows the user to capture a prior authorization.
 *
 * @todo Complete this function for Litle.
 */
function commerce_litle_cc_capture_form($form, &$form_state, $order, $transaction) {
  $form_state['order'] = $order;
  $form_state['transaction'] = $transaction;

  // Load and store the payment method instance for this transaction.
  $payment_method = commerce_payment_method_instance_load($transaction->instance_id);
  $form_state['payment_method'] = $payment_method;

  $balance = commerce_payment_order_balance($order);

  if ($balance['amount'] > 0 && $balance['amount'] < $transaction->amount) {
    $default_amount = $balance['amount'];
  }
  else {
    $default_amount = $transaction->amount;
  }

  // Convert the price amount to a user friendly decimal value.
  $default_amount = commerce_currency_amount_to_decimal($default_amount, $transaction->currency_code);

  $description = implode('<br />', array(
    t('Authorization: @amount', array('@amount' => commerce_currency_format($transaction->amount, $transaction->currency_code))),
    t('Order balance: @balance', array('@balance' => commerce_currency_format($balance['amount'], $balance['currency_code']))),
  ));

  $form['amount'] = array(
    '#type' => 'textfield',
    '#title' => t('Capture amount'),
    '#description' => $description,
    '#default_value' => $default_amount,
    '#field_suffix' => check_plain($transaction->currency_code),
    '#size' => 16,
  );

  $form = confirm_form($form,
    t('What amount do you want to capture?'),
    'admin/commerce/orders/' . $order->order_id . '/payment',
    '',
    t('Capture'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

/**
 * Validate handler: ensure a valid amount is given.
 *
 * @todo Complete this function.
 */
function commerce_litle_cc_capture_form_validate($form, &$form_state) {
  $transaction = $form_state['transaction'];
  $amount = $form_state['values']['amount'];

  // Ensure a positive numeric amount has been entered for capture.
  if (!is_numeric($amount) || $amount <= 0) {
    form_set_error('amount', t('You must specify a positive numeric amount to capture.'));
  }

  // Ensure the amount is less than or equal to the authorization amount.
  if ($amount > commerce_currency_amount_to_decimal($transaction->amount, $transaction->currency_code)) {
    form_set_error('amount', t('You cannot capture more than you authorized through Litle.'));
  }

  // If the authorization has expired, display an error message and redirect.
  if (time() - $transaction->created > 86400 * 30) {
    drupal_set_message(t('This authorization has passed its 30 day limit cannot be captured.'), 'error');
    drupal_goto('admin/commerce/orders/' . $form_state['order']->order_id . '/payment');
  }
}

/**
 * Submit handler: process a prior authorization capture via AIM.
 *
 * @todo Complete this function.
 */
function commerce_litle_cc_capture_form_submit($form, &$form_state) {
  $transaction = $form_state['transaction'];
  $amount = $form_state['values']['amount'];

  // Build a name-value pair array for this transaction.
  $nvp = array(
    'x_type' => 'PRIOR_AUTH_CAPTURE',
    'x_trans_id' => $transaction->remote_id,
    'x_amount' => $amount,
  );

  // Submit the request to Litle.
  $response = commerce_litle_cc_request($form_state['payment_method'], $nvp);

  // Update and save the transaction based on the response.
  $transaction->payload[REQUEST_TIME] = $response;

  // If we didn't get an approval response code...
  if ($response[0] != '1') {
    // Display an error message but leave the transaction pending.
    drupal_set_message(t('Prior authorization capture failed, so the transaction will remain in a pending status.'), 'error');
    drupal_set_message(check_plain($response[3]), 'error');
  }
  else {
    drupal_set_message(t('Prior authorization captured successfully.'));

    // Update the transaction amount to the actual capture amount.
    $transaction->amount = commerce_currency_decimal_to_amount($amount, $transaction->currency_code);

    // Set the remote and local status accordingly.
    $transaction->status = COMMERCE_PAYMENT_STATUS_SUCCESS;
    $transaction->remote_status = $response[11];

    // Append a capture indication to the result message.
    $transaction->message .= '<br />' . t('Captured: @date', array('@date' => format_date(REQUEST_TIME, 'short')));
  }

  commerce_payment_transaction_save($transaction);

  $form_state['redirect'] = 'admin/commerce/orders/' . $form_state['order']->order_id . '/payment';
}

/**
 * Form callback: allows the user to void a transaction.
 */
function commerce_litle_cc_void_form($form, &$form_state, $order, $transaction) {
  $form_state['order'] = $order;
  $form_state['transaction'] = $transaction;

  // Load and store the payment method instance for this transaction.
  $payment_method = commerce_payment_method_instance_load($transaction->instance_id);
  $form_state['payment_method'] = $payment_method;

  $form['markup'] = array(
    '#markup' => t('Are you sure that you want to void this transaction?'),
  );

  $form = confirm_form(
    $form,
    t('Are you sure that you want to void this transaction?'),
    'admin/commerce/orders/' . $order->order_id . '/payment',
    '',
    t('Void'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

/**
 * Submit handler: process the void request.
 *
 * @todo Complete this function
 */
function commerce_litle_cc_void_form_submit($form, &$form_state) {
  $transaction = $form_state['transaction'];

  // Build a name-value pair array for this transaction.
  $nvp = array(
    'x_type' => 'VOID',
    'x_trans_id' => $transaction->remote_id,
  );

  // Submit the request to Litle.
  $response = commerce_litle_cc_request($form_state['payment_method'], $nvp);

  // Update and save the transaction based on the response.
  $transaction->payload[REQUEST_TIME] = $response;

  // If we got an approval response code...
  if ($response[0] == 1) {
    drupal_set_message(t('Transaction successfully voided.'));

    // Set the remote and local status accordingly.
    $transaction->status = COMMERCE_PAYMENT_STATUS_FAILURE;
    $transaction->remote_status = $response[11];
    $transaction->payload[REQUEST_TIME] = $response;

    // Update the transaction message to show that it has been voided.
    $transaction->message .= '<br />' . t('Voided: @date', array('@date' => format_date(REQUEST_TIME, 'short')));
  }
  else {
    drupal_set_message(t('Void failed: @reason', array('@reason' => check_plain($response[3]))), 'error');
  }

  commerce_payment_transaction_save($transaction);

  $form_state['redirect'] = 'admin/commerce/orders/' . $form_state['order']->order_id . '/payment';
}

/**
 * Form callback: allows the user to issue a credit on a prior transaction.
 */
function commerce_litle_credit_form($form, &$form_state, $order, $transaction) {
  $form_state['order'] = $order;
  $form_state['transaction'] = $transaction;

  // Load and store the payment method instance for this transaction.
  $payment_method = commerce_payment_method_instance_load($transaction->instance_id);
  $form_state['payment_method'] = $payment_method;

  if ($payment_method['method_id'] == 'commerce_litle_cc') {
    $payment_display_name = 'credit card';
  }
  else {
    $payment_display_name = 'bank account';
  }

  $default_amount = commerce_currency_amount_to_decimal($transaction->amount, $transaction->currency_code);

  $form['amount'] = array(
    '#type' => 'textfield',
    '#title' => t('Credit amount'),
    '#description' => t('Enter the amount to be credited back to the original %payment.', array('%payment' => $payment_display_name)),
    '#default_value' => $default_amount,
    '#field_suffix' => check_plain($transaction->currency_code),
    '#size' => 16,
  );

  $form = confirm_form($form,
    t('What amount do you want to credit?'),
    'admin/commerce/orders/' . $order->order_id . '/payment',
    '',
    t('Credit'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

/**
 * Validate handler: check the credit amount before attempting credit request.
 */
function commerce_litle_credit_form_validate($form, &$form_state) {
  $transaction = $form_state['transaction'];
  $amount = $form_state['values']['amount'];

  // Ensure a positive numeric amount has been entered for credit.
  if (!is_numeric($amount) || $amount <= 0) {
    form_set_error('amount', t('You must specify a positive numeric amount to credit.'));
  }

  // Ensure the amount is less than or equal to the captured amount.
  if ($amount > commerce_currency_amount_to_decimal($transaction->amount, $transaction->currency_code)) {
    form_set_error('amount', t('You cannot credit more than you captured through Litle.'));
  }

  // Using 120 days here since that's what authnet module uses.
  // If the transaction is older than 120 days, display an error and redirect.
  if (time() - $transaction->created > 86400 * 120) {
    drupal_set_message(t('This capture has passed its 120 day limit for issuing credits.'), 'error');
    drupal_goto('admin/commerce/orders/' . $form_state['order']->order_id . '/payment');
  }
}

/**
 * Submit handler: process a credit.
 */
function commerce_litle_credit_form_submit($form, &$form_state) {
  $payment_method = $form_state['payment_method'];
  $transaction = $form_state['transaction'];
  $order = $form_state['order'];
  $amount = $form_state['values']['amount'];

  commerce_litle_credit_request($payment_method, $transaction, $order, $amount);

  $form_state['redirect'] = 'admin/commerce/orders/' . $order->order_id . '/payment';
}

/**
 * Makes the Credit/echeckCredit request and handles transactions and logging.
 *
 * Formats the request, makes it.
 * Logs response and request if needed.
 * On success creates a new transaction.
 * On failure updates the current transaction.
 *
 * @param array $payment_method
 *   Uses the payment method settings to determine what to log.
 *
 * @param object $transaction
 *   The transaction object.
 *
 * @param object $order
 *   The order object.
 *
 * @param float $amount
 *   Decimal format amount.  Gets converted to and from amount in this function.
 *
 * @return bool
 *   Whether the refund was successful.
 */
function commerce_litle_credit_request($payment_method, $transaction, $order, $amount) {
  $credit_amount = commerce_currency_decimal_to_amount($amount, $transaction->currency_code);

  // Build a name-value pair array for this transaction.
  // Litle expects amounts in integer number of cents.
  $nvp = array(
    'litleTxnId' => $transaction->remote_id,
    'amount' => $credit_amount,
  );

  // Log the request if specified.
  if ($payment_method['settings']['log']['request'] === 'request') {
    watchdog('commerce_litle', 'Litle Credit request: !param', array('!param' => '<pre>' . check_plain(print_r($nvp, TRUE)) . '</pre>'), WATCHDOG_DEBUG);
  }

  $litle = _commerce_litle_get_litle();
  $nvp = array_merge($nvp, _commerce_litle_get_litle_config($payment_method));
  $nvp['id'] = $nvp['litleTxnId'];

  // Submit the request to Litle.
  if ($payment_method['method_id'] == 'commerce_litle_cc') {
    $response = $litle->creditRequest($nvp);
  }
  else {
    $response = $litle->echeckCreditRequest($nvp);
  }

  $response_string = $litle->getDomDocumentAsString($response);
  $response_code = $litle->getNode($response, 'response');

  // Log the response if specified.
  if ($payment_method['settings']['log']['response'] === 'response') {
    watchdog('commerce_litle', 'Litle Credit response: !param', array('!param' => '<pre>' . check_plain($response_string) . '</pre>', WATCHDOG_DEBUG));
  }

  if ($response_code == '000') {
    drupal_set_message(t('Credit for @amount issued successfully', array('@amount' => commerce_currency_format($credit_amount, $transaction->currency_code))));

    // Create a new transaction to record the credit.
    $credit_transaction = commerce_payment_transaction_new('commerce_litle_cc', $order->order_id);
    $credit_transaction->instance_id = $payment_method['instance_id'];
    $credit_transaction->remote_id = $litle->getNode($response, 'litleTxnId');
    $credit_transaction->amount = $credit_amount * -1;
    $credit_transaction->currency_code = $transaction->currency_code;
    $credit_transaction->payload[REQUEST_TIME] = $response_string;
    $credit_transaction->status = COMMERCE_PAYMENT_STATUS_SUCCESS;
    $credit_transaction->remote_status = COMMERCE_CREDIT_AUTH_CAPTURE;
    $credit_transaction->message = t('Credited to @remote_id.', array('@remote_id' => $transaction->remote_id));

    // Save the credit transaction.
    commerce_payment_transaction_save($credit_transaction);

    return TRUE;
  }
  else {
    // Save the failure response message to the original transaction.
    $transaction->payload[REQUEST_TIME] = $response_string;

    // Display a failure message and response reason from Litle .
    $message = $litle->getNode($response, 'message');
    drupal_set_message(t('Credit failed: @reason', array('@reason' => check_plain($message))), 'error');

    commerce_payment_transaction_save($transaction);
  }

  return FALSE;
}
