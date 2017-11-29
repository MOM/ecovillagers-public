<?php

/**
 * @file
 * Queue functions for Springboard data warehouse exports.
 */

/**
 * Queue processing hook.
 */
function springboard_dw_process_csv_export_queue() {
  $callback = 'springboard_dw_file_export';

  // Get an instance of the Drupal data warehouse queue.
  $queue = DrupalQueue::get('springboard_dw_file_export');

  // Create an array for placeholder to track any failed queue items.
  $failed_queue_items = array();

  $item_count = 0;

  // Lock and claim an item for queue processing.
  while ($item_count == 0 && $item = $queue->claimItem()) {
    // If the job responds back correctly, remove the queue item.
    if (call_user_func($callback, $item->data)) {
      try {
        $queue->deleteItem($item);
      } catch (Exception $e) {
        // In case of exception log it and leave the item in the queue
        // to be processed again later.
        watchdog_exception('cron', $e);

        // Add this failed item to the failed queue items array.
        $failed_queue_items[] = $item;
      }
    }
    else {
      // Add this failed item to the failed queue items array.
      $failed_queue_items[] = $item;
    }

    // Simple incr here to make sure we only grab one at a time since
    // processing these may be pretty heavy.
    $item_count++;
  }

  if (count($failed_queue_items)) {
    echo "\n" . count($failed_queue_items) . ' ' .
      format_plural(count($failed_queue_items), 'queue item', 'queue items') . ' ' . 'failed to process.' . "\n";
  }

  /*
   * Loop through any failed queue items and release them back onto the queue
   * This has to be done because releasing directly within the processing
   * loop causes an infinite loop as the failed
   * item is added back immediately to the top of the queue instead of being
   * postponed till the next queue batch
   * (Documented https://www.drupal.org/node/1524550
   * and https://www.drupal.org/node/1832818)
   */
  foreach ($failed_queue_items as $queue_item) :
    $queue->releaseItem($queue_item);
  endforeach;

  drush_print("Attempted to process $item_count item/s in the export queue.");
}

/**
 * Run a file export job.
 * @param $item
 * @return bool
 *
 * TODO - Might be good to define a hook here so, in the future, new types of
 * exports can be defined without modifying this code directly. -jestep
 */
function springboard_dw_file_export($item) {
  require_once "sites/all/libraries/springboard_composer/vendor/autoload.php";

  // If the queue type is Drupal then our dump will come from the Drupal DB
  // instead of the data warehouse.
  if ($item['queue_type'] == 'springboard_export') {
    if (is_array($item) && isset($item['export_data']) && isset($item['recipient'])) {
      $export_summary = springboard_export_drush_export_views_data_export($item['export_data']);

      // Only supporting a single file:
      if (isset($export_summary['external_export_file_urls']) && isset($export_summary['external_export_file_urls'][0])) {
        $download_url = $export_summary['external_export_file_urls'][0];
      }
      $success_email_response = springboard_dw_file_export_completed_notification(
        $download_url,
        $item['recipient']
      );

      // Since the export was a success, mark this as such to remove the queue item.
      return TRUE;
    }
  }
  elseif ($item['queue_type'] == 'Warehouse') {
    // Define the API endpoint
    $download_api_endpoint = '/donation/report/download';

    // Re-map the transaction start range to what is expected in the warehouse
    // API if it is passed.
    if (isset($item['export_filters']['transaction']['min'])) {
      // transactionDateRangeStart
      $item['export_filters']['transactionDateRangeStart'] =
        $item['export_filters']['transaction']['min'];
      unset($item['export_filters']['transaction']['min']);
    }

    // Re-map the transaction end range to what is expected in the warehouse
    // API if it is passed.
    if (isset($item['export_filters']['transaction']['max'])) {
      // transactionDateRangeStart
      $item['export_filters']['transactionDateRangeEnd'] =
        $item['export_filters']['transaction']['max'];
      unset($item['export_filters']['transaction']['max']);
    }

    // Submit the request to the Data Warehouse and get the response:
    $export_api_call = springboard_dw_api_call($download_api_endpoint,
      $item['export_filters'],
      'GET');

    // Get the response data from the export.
    $export_api_call_body = json_decode((string) $export_api_call->getBody());

    if (isset($export_api_call_body->status) && $export_api_call_body->status
      == 'success'
    ) {
      $email = springboard_dw_file_export_completed_notification
      ($export_api_call_body->s3Url,
        $item['recipient']);

      // Since the export was a success, mark this as such to remove the
      // queue item.
      return TRUE;
    }
    else {
      // Redact the authentication token from the URL params.
      $item['export_filters']['authenticationToken'] = 'redacted********';

      // Setup an array of the API call details prepped for logging.
      $api_call = array();
      $api_call['endpoint'] = $download_api_endpoint;
      $api_call['method'] = 'POST';
      $api_call['params'] = $item['export_filters'];
      $api_call['response'] = $export_api_call_body->getBody()->getContents();
      $api_call['responseCode'] = $export_api_call_body->getStatusCode();
      $api_call['fullUrl'] = $download_api_endpoint . '?' . http_build_query(springboard_dw_api_prep_call
        ($item['export_filters']));
      $watchdog_string = "<pre>Warehouse CSV export API call: \n" . print_r($api_call, TRUE) . "</pre>";

      springboard_dw_watchdog_log($watchdog_string);

      return FALSE;
    }
  }

  // Default return should consider the export a failure unless otherwise
  // indicated.
  return FALSE;
}

/** Insert a new item into the Springboard data warehouse CSV export queue.
 * @param $type
 * @param $export_data
 * @param $recipient
 */
function springboard_dw_export_insert($type, $export_data, $recipient) {

  // Get the Drupal data warehouse queue.
  $queue = DrupalQueue::get("springboard_dw_file_export");

  // Get the export details and map them to the queue item array.
  $export_item = array();
  $export_item['queue_type'] = $type;
  $export_item['export_data'] = $export_data;
  $export_item['drush_command'] = $drush_command;
  $export_item['recipient'] = $recipient;

  // Create the queue item.
  $queue_item_created = $queue->createItem($export_item);

  // Log the queue item.
  springboard_dw_log_queue_item($export_item);

  // Return the result of the Drupal queue item creation.
  return $queue_item_created;
}

function springboard_dw_file_export_completed_notification($download_url,
                                                          $recipient) {
  // Use the user/1 email if a recipient is not provided or is invalid:
  if (!is_string($recipient) || strpos($recipient, '@') === FALSE) {
    $user = user_load(1);
    if (isset($user->mail)) {
      $recipient = $user->mail; 
    }
  }

  // Define the API endpoint for the notification.
  $api_endpoint = '/reports/email';
  $full_endpoint = springboard_dw_api_endpoint($api_endpoint);

  $authentication_token = variable_get
  ('springboard_dw_api_email_authentication_token', FALSE);

  // Construct the payload for the API call.
  $api_payload = [
    'emailAuthenticationToken' => $authentication_token,
    'recipient_address'        => $recipient,
    'download_url'             => $download_url,
  ];

  // Instantiate an API client instance.
  $api_client = springboard_dw_api_client();

  // Generate a API client request using email authentication payload.
  $api_response = $api_client->request(
    'POST',
    $full_endpoint,
    array(
      'form_params' => $api_payload,
    )
  );

  $response_data = json_decode((string) $api_response->getBody());

//  $api_payload['emailAuthenticationToken'] = 'redacted********';

  // Setup an array of the API call details prepped for logging.
  $api_call = array();
  $api_call['endpoint'] = $api_endpoint;
  $api_call['method'] = 'POST';
  $api_call['params'] = $api_payload;
  $api_call['response'] = $api_response->getBody()->getContents();
  $api_call['responseCode'] = $api_response->getStatusCode();
  $api_call['fullUrl'] = $full_endpoint . '?' . http_build_query(springboard_dw_api_prep_call
    ($api_payload));
  $watchdog_string = "<pre>Warehouse CSV export notification email API call: \n" . print_r($api_call, TRUE) . "</pre>";

  springboard_dw_watchdog_log($watchdog_string);

  return $response_data;
}
