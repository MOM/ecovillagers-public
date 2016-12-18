<?php
/**
 * @file
 * Report queries.
 */

/**
 * Ecommerce agnostic report select query.
 *
 * @param string $status
 *   Accepted values: 'payment_received', 'refunded', or 'partially_refunded'.
 *
 * @param string $start
 *   The report start date formatted for MySQL.
 *
 * @param string $end
 *   The report end date formatted for MySQL.
 *
 * @return array
 *   An array with 'total_count' and 'total_amount' keys.
 */
function dsr_select($status, $start, $end) {
  $results = array(
    'total_count' => 0,
    'total_amount' => 0,
  );

  // We are using the transaction table as the base here to ensure we capture all orders that have transacted.
  $query = "SELECT MAX(t.transaction_id), t.order_id, a.commerce_order_total_amount FROM {commerce_payment_transaction} t
  LEFT JOIN {commerce_order} o ON o.order_id = t.order_id
  LEFT JOIN {field_data_commerce_order_total} a ON o.order_id = a.entity_id AND o.revision_id = a.revision_id
  WHERE t.status = 'success'
  AND o.status = :status
  AND from_unixtime(t.changed) BETWEEN :start AND :end
  GROUP BY t.order_id";

  $replacements = array(
    ':status' => $status,
    ':start' => $start,
    ':end' => $end,
  );

  $transactions = db_query($query, $replacements);

  // Some statuses need the order total, others will need the balance taken into account.
  $amount_stat = in_array($status, array('payment_received', 'refunded')) ? 'total' : 'balance';

  foreach ($transactions as $transaction) {
    $results['total_count']++;

    // Compute the amount.
    if ($amount_stat == 'total') {
      $results['total_amount'] += $transaction->commerce_order_total_amount;
    }
    else {
      $order = commerce_order_load($transaction->order_id);
      $balance = commerce_payment_order_balance($order);
      $results['total_amount'] += $transaction->commerce_order_total_amount - $balance['amount'];
    }
  }

  $results['total_amount'] = $results['total_amount'] / 100;

  return $results;
}

/**
 * Get a list of order data by status and date range.
 *
 * @param string $status
 *   Order status (payment_received, refunded, partially_refunded).
 *
 * @param string $start
 *   The start date formatted for MySQL.
 *
 * @param string $end
 *   The end date formatted for MySQL.
 *
 * @return array
 *   An array of orders matching the select criteria.
 */
function dsr_get_orders($status, $start, $end) {
  $orders = array();

  // We are using the transaction table as the base here to ensure we capture all orders that have transacted.
  $query = "SELECT MAX(t.transaction_id), t.order_id, a.commerce_order_total_amount FROM {commerce_payment_transaction} t
  LEFT JOIN {commerce_order} o ON o.order_id = t.order_id
  LEFT JOIN {field_data_commerce_order_total} a ON o.order_id = a.entity_id AND o.revision_id = a.revision_id
  WHERE t.status = 'success'
  AND o.status = :status
  AND from_unixtime(t.changed) BETWEEN :start AND :end
  GROUP BY t.order_id";

  $replacements = array(
    ':status' => $status,
    ':start' => $start,
    ':end' => $end,
  );

  $transactions = db_query($query, $replacements);
  foreach ($transactions as $transaction) {
    // For payment recieved status we can use the total amount.
    if ($status == 'payment_received') {
      $orders[$transaction->order_id] = $transaction->commerce_order_total_amount / 100;
    }
    // Other status will need the balance taken into account.
    else {
      $order = commerce_order_load($transaction->order_id);
      $balance = commerce_payment_order_balance($order);
      $orders[$transaction->order_id] = ($transaction->commerce_order_total_amount - $balance['amount']) / 100;
    }
  }

  return $orders;
}

/**
 * Perform aggregate query on Salesforce data by donation status and date range.
 *
 * @param string $status
 * @param string $start_date
 * @param string $end_date
 *
 * @return array
 */
function dsr_salesforce_aggregate($status, $start_date, $end_date) {
  // Map from commerce status to SF stage.
  $sf_status = array(
    'payment_received' => 'Posted',
    'refunded' => 'Refunded',
    'partially_refunded' => 'Partially Refunded',
  );

  // Map from commerce status to SF SOQL query.
  $sf_soql = array(
    'payment_received' => variable_get('dsr_posted_aggregate_s', DSR_DEFAULT_AGGREGATE_SOQL),
    'refunded' => variable_get('dsr_refunded_aggregate_s', DSR_DEFAULT_AGGREGATE_SOQL),
    'partially_refunded' => variable_get('dsr_partially_refunded_aggregate_s', DSR_DEFAULT_AGGREGATE_SOQL),
  );

  // Replace the values in the SOQL query.
  $replace = array(
    ':stage' => $sf_status[$status],
    ':start' => $start_date,
    ':end' => $end_date,
  );
  $soql = strtr($sf_soql[$status], $replace);

  $salesforce = salesforce_get_api();

  if ($salesforce->isAuthorized()) {
    $soql = rawurlencode($soql);
    $response = $salesforce->apiCall('query?q=' . $soql);
    return _dsr_parse_aggregate_result($response);
  }
  else {
    drupal_set_message('Unable to connect to Salesforce at this time. Please double check your credentials and try again.');
    return array('total_count' => 0, 'total_amount' => 0);
  }

}

/**
 * Runs a predefined SOQL statement and returns all the results as an array.
 *
 * @param $soql
 *   The SOQL statement to run.
 * @param $key_field
 *   The field to use as the key if you want an associative array returned.
 *
 * @deprecated $salesforce->client is not an object. Also this doesn't appear
 *             to be called anywhere.
 */
function dsr_soql_select($soql, $key_field = NULL) {
  $records = array();
  $continue = TRUE;

  $salesforce = salesforce_get_api();
  // Make sure we've got a good connection.
  if ($salesforce->isAuthorized()) {
    $results = $salesforce->client->query(rawurlencode($soql));
    return $results->records;
  }

  // Return false if we couldn't connect.
  return FALSE;
}
