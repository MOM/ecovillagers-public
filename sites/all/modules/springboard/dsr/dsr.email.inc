<?php
/**
 * @file
 * Email related functions for dsr.
 */

/**
 * Creates a multipart email for dsr_mail().
 *
 * @param array $params
 *   The parameters provided by hook_mail().
 *
 * @return array
 *   An array for merging into the mail in dsr_mail().
 */
function dsr_create_multipart_email($params) {
  $stats = $params['stats'];
  $start_date = $params['start_date'];
  $end_date = $params['end_date'];

  // To make the HTML email work, implement all our own headers.
  $boundary = '----=_NextPart_' . md5(uniqid());

  $headers = array(
    'MIME-Version' => '1.0',
    'Content-Type' => 'multipart/alternative; boundary="' . $boundary . '"',
    'Content-Transfer-Encoding' => '8Bit',
    'X-Mailer' => 'Drupal',
  );

  if (!empty($params['bcc_address'])) {
    $headers['Bcc'] = $params['bcc_address'];
  }
  //
  // Now create the message, with an HTML component and a plaintext component.
  //

  $body_html = '<html><head></head><body>';
  $body_html .= dsr_collect_stats($start_date, $end_date, FALSE);
  $body_html .= '<p><em>Summary processed on server ' . $_SERVER['SERVER_ADDR'] . '</em></p>';
  $body_html .= '</body></html>';
  $body_text = dsr_create_text_email($start_date, $end_date, $stats);
  $multi_body  = "

This is a multi-part message in MIME format.

--$boundary
Content-Type: text/plain; charset=UTF-8; format=flowed;
Content-Transfer-Encoding: 8bit

$body_text

--$boundary
Content-Type: text/html; charset=UTF-8; format=flowed;
Content-Transfer-Encoding: 8bit

$body_html

";

  $email['body'] = $multi_body;
  $email['headers'] = $headers;

  return $email;
}

/**
 * @param string $start_date
 * @param string $end_date
 * @param array $stats
 *
 * @return string
 */
function dsr_create_text_email($start_date, $end_date, $stats) {
  $sf_posted_amount = number_format($stats['salesforce_posted']['total_amount'], 2, '.', ',');
  $drupal_posted_amount = number_format($stats['drupal_posted']['total_amount'], 2, '.', ',');
  $sf_refunded_amount = number_format($stats['salesforce_refunded']['total_amount'], 2, '.', ',');
  $drupal_refunded_amount = number_format($stats['drupal_refunded']['total_amount'], 2, '.', ',');
  $sf_partially_refunded_amount = number_format($stats['salesforce_partially_refunded']['total_amount'], 2, '.', ',');
  $drupal_partially_refunded_amount = number_format($stats['drupal_partially_refunded']['total_amount'], 2, '.', ',');

  $posted_types = _dsr_text_results('posted', $stats);
  $refunded_types = _dsr_text_results('refunded', $stats);
  $partially_refunded_types = _dsr_text_results('partially_refunded', $stats);

  $links = '';
  $notification = t('No discrepancies detected');

  if ($stats['posted_discrepancy']) {
    $links .= dsr_email_report_link('posted', $start_date, $end_date);
    $notification = t('Discrepancies detected');
  }

  if ($$stats['refunded_discrepancy']) {
    $links .= dsr_email_report_link('refunded', $start_date, $end_date);
    $notification = t('Discrepancies detected');
  }

  if ($stats['partially_refunded_discrepancy']) {
    $links .= dsr_email_report_link('partially_refunded', $start_date, $end_date);
    $notification = t('Discrepancies detected');
  }

  $email = <<<EOT

$notification

***** Posted Transactions *****
Drupal ||  count: {$stats['drupal_posted']['total_count']}  total amount: {$stats['drupal_posted']['total_amount']}
Salesforce ||  count: {$stats['salesforce_posted']['total_count']}  total amount: {$stats['salesforce_posted']['total_amount']}
{$posted_types}


***** Refunded Transactions *****
Drupal ||  count: {$stats['drupal_refunded']['total_count']}  total amount: {$stats['drupal_refunded']['total_amount']}
Salesforce ||  count: {$stats['salesforce_refunded']['total_count']}  total amount: {$stats['salesforce_refunded']['total_amount']}
{$refunded_types}


***** Partially Refunded Transactions *****
Drupal ||  count: {$stats['drupal_partially_refunded']['total_count']}  total amount: {$stats['drupal_partially_refunded']['total_amount']}
Salesforce ||  count: {$stats['salesforce_partially_refunded']['total_count']}  total amount: {$stats['salesforce_partially_refunded']['total_amount']}
{$partially_refunded_types}

$links

Summary processed on server {$_SERVER['SERVER_ADDR']}

EOT;

  return $email;

}

/**
 * @param string $type
 * @param string $start_date
 * @param string $end_date
 *
 * @return string
 */
function dsr_email_report_link($type, $start_date, $end_date) {
  global $base_url;
  return $base_url . '/' . DSR_RECONCILIATION_PATH . '/report/' . $type . '/' . date('Y-m-d', strtotime($start_date)) . '/' . date('Y-m-d', strtotime($end_date)) . "\n";
}

/**
 * @param string $suffix
 * @param array $stats
 *
 * @return null|string
 */
function _dsr_text_results($suffix, $stats) {
  if (isset($stats["salesforce_$suffix"]['types'])) {
    foreach ($stats["salesforce_$suffix"]['types'] as $label => $data) {
      $total_count = $stats["salesforce_$suffix"]['types'][$label]['total_count'];
      $total_amount = $stats["salesforce_$suffix"]['tyoes'][$label]['total_amount'];
      $results .= "  --  $label ||  count: $total_count  total amount: $total_amount\n";
    }
    return $results;
  }
  return NULL;
}
