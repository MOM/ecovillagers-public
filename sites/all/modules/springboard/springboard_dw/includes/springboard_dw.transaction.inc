<?php

/**
 * @file
 * Transaction related functions for Springboard data warehouse.
 */

function springboard_dw_transaction_get_by_id($transaction_id) {
  if (empty($transaction_id)) {
    return FALSE;
  }
  $query = db_query('select transaction_id, revision_id, uid, order_id, payment_method, instance_id, remote_id, message, message_variables, amount, currency_code, status, remote_status, created, changed from {commerce_payment_transaction} where remote_id = CAST(:transaction_id AS CHAR)',
    array(':transaction_id' => $transaction_id))->fetchAssoc();

  return $query;
}

/**
 * Returns the latest transaction date for an order.
 *
 * @param $order_id
 *   The id of the order.
 * 
 * @return an integer timestamp or NULL.
 */
function springboard_dw_transaction_date_get_by_order_id($order_id) {
  $transaction_date = db_query('select max(created) from {commerce_payment_transaction} where order_id = :order_id',
    array(':order_id' => $order_id))->fetchField();

  return $transaction_date;
}