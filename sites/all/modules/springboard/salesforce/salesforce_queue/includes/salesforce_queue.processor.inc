<?php

/**
 * @file
 * Contains SalesforceQueueProcessor
 */

/**
 * Processes items from SalesforceQueue.
 */
class SalesforceQueueProcessor {

  /**
   * SalesforceQueue object.
   *
   * @var object
   */
  protected $queue;

  /**
   * Name of the SalesforceQueue this processor is processing.
   *
   * @var string
   */
  public $queueName;

  /**
   * SalesforceSync object that controls synchronization tasks with Salesforce.
   *
   * @var SalesforceSync
   */
  public $salesforceSync;

  /**
   * Batch of items from the queue that need to be processed.
   *
   * @var array
   */
  protected $items = array();

  /**
   * Array of groups of items that can be sent to Salesforce simultaneously.
   *
   * @var array
   */
  protected $batches = array();

  /**
   * The configured maximum number of items that can be processed at once.
   *
   * This depends upon the system resources
   *
   * @var int
   */
  protected $maxItems = 1000;

  /**
   * The configured default time the queue will be leased to our process.
   *
   * @var int
   */
  protected $leaseTime = 3600;

  /**
   * The time at which the current claim on the queue will expire.
   *
   * @var int
   */
  protected $leaseExpire = 0;

  /**
   * Unique identifier that allows unlocking the lease on the queue.
   *
   * @var string
   */
  protected $leaseKey;

  /**
   * The maximum number of items that can be sent to Salesforce in one call.
   *
   * @var int
   */
  protected $maxBatchSize = 200;

  /**
   * Defines a default response to the end of the processing.
   *
   * @var int
   */
  protected $endStatus = SALESFORCE_QUEUE_PROCESS_NOT_STARTED;

  /**
   * A processor object for the given queue.
   *
   * @param SalesforceQueue $queue
   *   The desired queue to process against, or NULL to process against the
   *   multi-queue manager
   *
   * @return SalesforceQueueProcessor
   *   A processor for the given queue
   */
  public static function get(SalesforceQueue $queue = NULL) {
    $queue = is_null($queue) ? salesforce_queue_load() : $queue;
    $processor = new SalesforceQueueProcessor($queue);
    return $processor;
  }

  /**
   * Construct the object.
   *
   * @param SalesforceQueue $queue
   *   SalesforceQueue object
   */
  public function __construct(SalesforceQueue $queue) {
    $this->queue = $queue;
    $this->queueName = $queue->queueName;
    $this->salesforceSync = new SalesforceSync();
    $this->setSalesforceApi();
    $this->setSalesforceSoap();
    $this->maxItems = variable_get('salesforce_queue_max_items', SALESFORCE_QUEUE_MAX_ITEMS_DEFAULT);
    $this->leaseTime = variable_get('salesforce_queue_lease_time', SALESFORCE_QUEUE_LEASE_TIME_DEFAULT);
    $this->maxBatchSize = variable_get('salesforce_sync_max_batch_size', SALESFORCE_SYNC_MAX_BATCH_SIZE_DEFAULT);
  }

  /**
   * Kicks off processing up-to the maximum allowed items from the given queue.
   */
  public function process() {
    // Invokes hook_salesforce_queue_preprocess_queue().
    module_invoke_all('salesforce_queue_preprocess_queue', $this->queue);

    // Gather items to process.
    // Because processor is run on cron, and an error is issued if Salesforce
    // cannot connect, first check to see if there are any items in the queue.
    // Cron may be run on numerous occasions before the site administrator
    // starts actually using the Salesforce Queue, so lets send them more severe
    // errors only if there are actually any queue items to process.
    $this->claimItems();
    if (!empty($this->items)) {
      // Check Salesforce connection.
      // This extra check is for simpletests and drush which require a specific
      // $sfapi in certain instances.
      $this->setSalesforceApi();
      $sfapi_passed = TRUE;
      if (!is_object($this->salesforceSync->sfapi)) {
        $sfapi_passed = FALSE;
        watchdog('salesforce', '[@id] QueueProcessor failed: Cannot connect to Salesforce.',
          array('@id' => 'queue-03'), WATCHDOG_ALERT);
        $this->endStatus = SALESFORCE_QUEUE_PROCESS_FAIL_CONNECT;
      }

      // After Salesforce connection is successful, test the soap connection.
      $soap_passed = FALSE;
      if ($sfapi_passed) {
        $this->setSalesforceSoap();
        $soap_passed = TRUE;
        if (!is_object($this->salesforceSync->soap)) {
          $soap_passed = FALSE;
          watchdog('salesforce', '[@id] QueueProcessor failed: Cannot use SOAP connection.',
            array('@id' => 'queue-04'), WATCHDOG_ALERT);
          $this->endStatus = SALESFORCE_QUEUE_PROCESS_FAIL_SOAP;
        }
      }

      // Continue only if there is a verified connection to Salesforce.
      if ($soap_passed) {
        // Invokes hook_salesforce_queue_process_items_alter().
        drupal_alter('salesforce_queue_process_items', $this->items, $this->queue);

        // Sort the items into a set of logical batches that can be sent off to
        // Salesforce.
        $this->createBatches();
        if (empty($this->batches)) {
          // If there were items in the queue, but no batches, then that means
          // no claimed items were valid.
          $this->endStatus = SALESFORCE_QUEUE_PROCESS_FAIL_NO_VALID_ITEMS;

          // Send an error to admin that there were no valid items in the queue
          // to process.
          watchdog('salesforce', '[@id] QueueProcessor ran but only invalid items found.',
            array('@id' => 'queue-05'), WATCHDOG_NOTICE);
        }
        else {
          $this->processBatches();
        }
      }
    }

    if ($this->endStatus == SALESFORCE_QUEUE_PROCESS_NOT_STARTED) {
      // We got to the end without anyone else reporting anything!
      $end_status = SALESFORCE_QUEUE_PROCESS_COMPLETE;
    }
    else {
      $end_status = $this->endStatus;
    }

    $this->resetInternalState();

    // Invokes hook_salesforce_queue_postprocess_queue().
    module_invoke_all('salesforce_queue_postprocess_queue', $this->queue, $end_status);

    return $end_status;
  }

  /**
   * Claim a batch of items to process.
   */
  public function claimItems() {
    // If there are still unprocessed items, lets finish those first.
    if (empty($this->items)) {
      // Make sure we don't have a claim on the queue by releasing it.
      $this->releaseQueue();

      // Claim some items.
      $items = $this->queue->claimBatch($this->maxItems, $this->leaseTime);

      // SalesforceQueue::claimBatch() returns FALSE if there are no more items
      // or when the queue is currently leased.
      if (empty($items)) {
        // Is the queue leased?
        if ($this->queue->queueIsLeased()) {
          // The process was run while the queue is already leased.  This could
          // be user error, or could be a sign that processes are piling up due
          // to some sort of conflict with server resources or connections with
          // Salesforce, or the configuration settings about how much to process
          // or even how often we're trying to run this process.
          $message = '[@id] QueueProcessor claimed no items: Queue leased';
          $severity = WATCHDOG_NOTICE;
          $log_id = 'queue-06';
          $this->endStatus = SALESFORCE_QUEUE_PROCESS_FAIL_QUEUE_LEASED;
        }
        elseif ($this->queue->numberOfItems(TRUE) < 1) {
          // No items are in the queue.  Pretty minor issue.
          $message = '[@id] QueueProcessor found no items in queue';
          $severity = WATCHDOG_DEBUG;
          $log_id = 'queue-07';
          $this->endStatus = SALESFORCE_QUEUE_PROCESS_NO_ITEMS;
        }
        else {
          // If we get here, then we're really clueless as to what is going on.
          $message = '[@id] QueueProcessor claimed no items: Reason unknown.  Eeps.';
          $severity = WATCHDOG_ALERT;
          $log_id = 'queue-08';
          $this->endStatus = SALESFORCE_QUEUE_PROCESS_FAIL_CLAIM_ITEMS;
        }
        watchdog('salesforce', $message, array('@id' => $log_id), $severity);
      }
      else {
        $this->leaseKey = $items[0]->leaseKey;
        $this->items = $items;
      }
    }
    return $this->items;
  }

  /**
   * Releases this processor's claim on the queue.
   */
  public function releaseQueue() {
    $current_lease_key = variable_get('salesforce_queue_' . $this->queueName . '_lease_key', NULL);
    if (!empty($this->leaseKey) && $this->leaseKey == $current_lease_key) {
      $this->queue->releaseBatch($this->leaseKey);
      $this->leaseKey = NULL;
    }
  }

  /**
   * Group the items into batches that can be sent to Salesforce in one call.
   *
   * A batch of items are defined as items that can be sent to Salesforce in
   * one call. They can if they match the following requirements:
   *   - Same Salesforce object type
   *     - If operation is DELETE, object type doesn't matter
   *   - Same operation
   *     - If operation is UPSERT, they have the same dedupe field
   *   - No more than 200 items ($maxBatchSize)
   *
   * @NOTE There may be an additional complication when considering row-by-row
   *       comparision.  A field map may have individual fields check against
   *       Salesforce to see if it should write/overwrite/ignore the submitted
   *       value when sending to Salesforce
   */
  public function createBatches() {
    // The goal is to have one loop through the items.
    $batch_groups = array();
    $count = count($this->items);
    while ($count > 0) {
      $item = array_shift($this->items);
      $count--;

      // Adjust just in case an UPSERT command falls through without a dedupe.
      if ($item->operation == 'UPSERT' && empty($item->dedupe_field)) {
        $item->operation = 'CREATE';
      }

      // Test the item for validity and fail it if it does not pass.
      if ($this->isValidItem($item)) {
        // Slot the item into a Object->Operation->Dedupe batch group.
        $this->addItemToBatchGroups($item, $batch_groups);
      }
      else {
        $this->salesforceSync->failItem($item, SALESFORCE_QUEUE_PROCESS_ITEM_FAIL_NOT_VALID);
      }
    }

    // Grab all the batches from the groups and put them in a linear order by
    // how it has been configured.
    $batches = $this->sortBatches($batch_groups);

    // All done! Add the new set of batches to the end of the current set.
    $this->batches = array_merge($this->batches, $batches);
    return $this->batches;
  }

  /**
   * Slot the given item into a Object->Operation->Dedupe batch group.
   *
   * @param object $item
   *   A queue item
   * @param array $batch_groups
   *   Temporary holder that categorizes all of the items and places them in
   *   group no larger than $maxBatchSize
   */
  protected function addItemToBatchGroups($item, &$batch_groups) {
    // Set up our brevity vars.
    $op = $item->operation;
    $object_type = $item->object_type;
    $dedupe_field = $item->dedupe_field;
    $batch_template = array(
      'operation' => $op,
      'count' => 0,
      'items' => array(),
    );

    // Declare batch_group levels this item will be sorted under.
    $lvl1 = ($op == 'DELETE') ? 'DELETE' : $object_type;
    $lvl2 = ($op == 'DELETE') ? NULL : $op;
    $lvl3 = ($op == 'UPSERT') ? $dedupe_field : NULL;

    // Find the batch_group for this item, while creating missing batch_groups
    // along the way.
    if (!isset($batch_groups[$lvl1])) {
      $batch_groups[$lvl1] = array();
    }
    // DELETE.
    if (is_null($lvl2)) {
      $batch_group = &$batch_groups[$lvl1];
    }
    else {
      if (!isset($batch_groups[$lvl1][$lvl2])) {
        $batch_groups[$lvl1][$lvl2] = array();
      }
      // CREATE and UPDATE.
      if (is_null($lvl3)) {
        $batch_group = &$batch_groups[$lvl1][$lvl2];
      }
      else {
        // UPSERT.
        if (!isset($batch_groups[$lvl1][$lvl2][$lvl3])) {
          $batch_groups[$lvl1][$lvl2][$lvl3] = array();
        }
        $batch_group = &$batch_groups[$lvl1][$lvl2][$lvl3];
      }
    }

    // Check to see if the current batch is filled up or not.  If it is full,
    // start a new batch.
    end($batch_group);
    $last_key = key($batch_group);
    reset($batch_group);
    if (empty($batch_group) || $batch_group[$last_key]['count'] >= $this->maxBatchSize) {
      // Create a new batch.
      $batch_key = is_numeric($last_key) ? $last_key + 1 : 0;
      $batch = $batch_template;
      if ($op == 'DELETE') {
        $batch['ids'] = array();
      }
      else {
        $batch['object_type'] = $object_type;
        $batch['sobjects'] = array();
      }
      if ($op == 'UPSERT') {
        $batch['dedupe_field'] = $dedupe_field;
        $batch['sync_rules'] = array(
          'apply' => FALSE,
          'fields' => array(),
          'dedupe_values' => array(),
        );
      }
      elseif ($op == 'UPDATE') {
        $batch['sync_rules'] = array(
          'apply' => FALSE,
          'fields' => array(),
          'ids' => array(),
        );
      }
    }
    else {
      // Use current batch.
      $batch_key = $last_key;
      $batch = $batch_group[$batch_key];
    }

    // When sending to Salesforce we just need the sobject, but in other
    // processes we need the items.  To prevent looping through the items
    // once again, we'll store a link to the sobject.
    $count = $batch['count'];
    $batch['items'][$count] = $item;
    if ($op == 'DELETE') {
      // Because DELETE has to be special like that.
      $batch['ids'][$count] = &$item->sobject->Id;
    }
    else {
      // Link to the sobject in the item so editing one edits the other.
      $batch['sobjects'][$count] = &$batch['items'][$count]->sobject;
    }
    $batch['count']++;

    // UPSERT and UPDATE items need to have their sync_rules checked.  Add the
    // information needed to process their sync rules to the batch.
    if ($this->itemNeedsToCheckSalesforce($item)) {
      $batch['sync_rules']['apply'] = TRUE;

      // UPDATE items need to store all the fields and object Ids.
      if ($op == 'UPDATE') {
        $batch['sync_rules']['ids'][$item->sobject->Id] = $item->sobject->Id;
        foreach ($item->sobject->fields as $field => $value) {
          $batch['sync_rules']['fields'][$field] = $field;
        }
      }

      // UPSERT items need to store all their fields and the values they have
      // set for the given dedupe field.
      elseif ($op == 'UPSERT') {
        $batch['sync_rules']['dedupe_values'][$item->sobject->fields[$item->dedupe_field]] = $item->sobject->fields[$item->dedupe_field];
        foreach ($item->sobject->fields as $field => $value) {
          $batch['sync_rules']['fields'][$field] = $field;
        }
      }
    }

    // $batch_groups referred by reference.
    $batch_group[$batch_key] = $batch;
  }

  /**
   * Check if the item needs to check Salesforce records before sending data.
   *
   * @param object $item
   *   Queue item
   *
   * @return boolean
   *   TRUE if the item needs to check the record on Salesforce before sending
   *   its data to Salesforce, and FALSE if it can just go ahead and send its
   *   data to Salesforce as-is.
   */
  protected function itemNeedsToCheckSalesforce($item) {
    if (($item->operation == 'UPSERT' || $item->operation == 'UPDATE') && isset($item->sync_rules) && !empty($item->sync_rules)) {
      foreach ($item->sync_rules as $rule) {
        // There is no need to pull down the Salesforce record if all the rules
        // are to always replace the Salesforce value.
        if ($rule != SALESFORCE_SYNC_RULE_ALWAYS) {
          return TRUE;
        }
      }
    }
    return FALSE;
  }

  /**
   * Sort batch groups into a linear order.
   *
   * Grab all the batches from the groups and sort them in a linear order by how
   * it has been configured for this site.
   *
   * @param array $batch_groups
   *   The temporary holder of queue items as created from addItemToBatchGroups
   *
   * @return array
   *   Array of batches that can be processed by processBatches and processBatch
   */
  protected function sortBatches($batch_groups) {
    $batches = array();

    // Remove the DELETE operation so we can place it at the end later.
    if (isset($batch_groups['DELETE'])) {
      $delete_batches = $batch_groups['DELETE'];
      unset($batch_groups['DELETE']);
    }

    // Move all of the batch items into the batches list in the configured order
    // @TODO set default object order.
    $default_object_order = array('Account', 'Contact', 'Opportunity');
    $object_order = variable_get('salesforce_queue_object_order', $default_object_order);
    $op_order = array('CREATE', 'UPSERT', 'UPDATE');
    foreach ($object_order as $object_type) {
      if (isset($batch_groups[$object_type])) {
        foreach ($op_order as $op) {
          if (isset($batch_groups[$object_type][$op])) {
            if ($op == 'UPSERT') {
              foreach ($batch_groups[$object_type][$op] as $field => $field_batches) {
                $batches = array_merge($batches, $batch_groups[$object_type][$op][$field]);
                unset($batch_groups[$object_type][$op][$field]);
              }
              unset($batch_groups[$object_type][$op]);
            }
            else {
              $batches = array_merge($batches, $batch_groups[$object_type][$op]);
              unset($batch_groups[$object_type][$op]);
            }
          }
        }
        if (empty($batch_groups[$object_type])) {
          unset($batch_groups[$object_type]);
        }
      }
    }

    // Lastly, If any Salesforce objects were not configured for a specific
    // order, append those to the end of the batch list.
    foreach ($batch_groups as $object_type => $operations) {
      foreach ($op_order as $op) {
        if (isset($batch_groups[$object_type][$op])) {
          if ($op == 'UPSERT') {
            foreach ($batch_groups[$object_type][$op] as $field => $batches) {
              $batches = array_merge($batches, $batch_groups[$object_type][$op][$field]);
            }
          }
          else {
            $batches = array_merge($batches, $batch_groups[$object_type][$op]);
          }
        }
      }
    }

    // Append the DELETE batches to the end.
    if (isset($delete_batches)) {
      $batches = array_merge($batches, $delete_batches);
    }

    return $batches;
  }

  /**
   * Check to see if the item can be sent to Salesforce as-is.
   *
   * @param object $item
   *   Queue item
   *
   * @return boolean
   *   TRUE if the item is valid and can be sent to Salesforce with the given
   *   operation.  FALSE if the item cannot be sent to Salesforce with the
   *   given operation and provided information.
   */
  protected function isValidItem($item) {
    $op = $item->operation;
    $sobject = $item->sobject;
    switch ($op) {
      case 'CREATE':
        // Cannot have an Id field, requires salesforce type and fields.
        if (!isset($sobject->Id) && isset($sobject->type) && isset($sobject->fields)) {
          return TRUE;
        }
        break;

      case 'UPSERT':
        // Cannot have an Id field, requires dedupe field, salesforce type and
        // fields.
        if (!isset($sobject->Id) && !empty($item->dedupe_field) && isset($sobject->type) && isset($sobject->fields)) {
          return TRUE;
        }
        break;

      case 'UPDATE':
        // Requires Id field, salesforce type and either fields or fields to
        // null.
        if (isset($sobject->Id) && isset($sobject->type) && (isset($sobject->fields) || isset($sobject->fieldsToNull))) {
          return TRUE;
        }
        break;

      case 'DELETE':
        // Only requires Id.
        if (isset($sobject->Id)) {
          return TRUE;
        }
    }
    return FALSE;
  }

  /**
   * Wrapper for processBatch() to process all batches ready for processing.
   *
   * @return array
   *   Array of result objects provided by Salesforce
   */
  public function processBatches() {
    $results = array();
    $count = count($this->batches);
    while ($count > 0) {
      $count--;
      $result = $this->processBatch();
      if (is_array($result)) {
        $results = array_merge($results, $result);
      }
    }
    return $results;
  }

  /**
   * Processes the next batch in line for processing.
   *
   * @return array
   *   Array of result objects provided by Salesforce
   */
  public function processBatch() {
    $batch = array_shift($this->batches);
    $results = array();

    // Invokes hook_salesforce_queue_preprocess_batch().
    module_invoke_all('salesforce_queue_preprocess_batch', $batch, $this->queue);

    // Invokes hook_salesforce_queue_batch_alter().
    drupal_alter('salesforce_queue_batch', $batch, $this->queue, $this);

    // Prepare the batch before checking the lease expiration to minimize time
    // delay between checking and sending.  This is to ensure the minimal risk
    // of two overlapping writes to Salesforce.
    $this->salesforceSync->sendBatchPrepare($batch);

    // Invokes hook_salesforce_queue_finalize_batch_alter(). Last chance.
    drupal_alter('salesforce_queue_finalize_batch', $batch, $this->queue, $this);

    // Make sure we have enough time to send these items to Salesforce before
    // our lease expires. We do not want to risk the chance of items getting
    // sent to Salesforce twice, so we will not send items outside our lease or
    // when it is leased to someone else.
    $current_lease_key = variable_get('salesforce_queue_' . $this->queueName . '_lease_key', NULL);
    if ($this->endStatus == SALESFORCE_QUEUE_PROCESS_FAIL_LEASE_EXPIRED || !$this->queue->queueIsLeased() || $current_lease_key != $this->leaseKey) {
      // Lease expired, fail.
      $this->endStatus = SALESFORCE_QUEUE_PROCESS_FAIL_LEASE_EXPIRED;
      watchdog('salesforce_queue', 'Processing batches incomplete due to expired lease.');
      $this->salesforceSync->failBatch($batch, SALESFORCE_QUEUE_PROCESS_ITEM_FAIL_LEASE_EXPIRED);
    }
    else {
      // Woot, lease active. Send this baby off to Salesforce.
      $results = $this->salesforceSync->sendBatch($batch);
    }

    // Invokes hook_salesforce_queue_postprocess_batch().
    module_invoke_all('salesforce_queue_postprocess_batch', $batch, $results, $this->queue);

    return $results;
  }

  /**
   * Eat yum yums.
   */
  protected function eatBatch() {
    // Nom nom nom.
  }

  /**
   * Release our claim on the queue and reset our internal state.
   */
  protected function resetInternalState() {
    $this->items = array();
    $this->batches = array();
    $this->endStatus = SALESFORCE_QUEUE_PROCESS_NOT_STARTED;
    return $this->releaseQueue();
  }

  /**
   * Helper to get all records created by this SalesforceProcessor.
   *
   * @return array
   *   Records that have been created.
   */
  public function getNewSfRecords() {
    return $this->salesforceSync->newSfRecords;
  }

  /**
   * Helper to get all item Ids processed by this SalesforceProcessor.
   *
   * @return array
   *   Ids of items that have been processed keyed by their unique identifier.
   */
  public function getProcessedItemIds() {
    return $this->salesforceSync->getProcessedItemIds();
  }

  /**
   * Helper to externally set the Salesforce API. Used for simpletests.
   */
  public function setSalesforceApi(Salesforce $sfapi = NULL) {
    $this->salesforceSync->setSalesforceApi($sfapi);
  }

  /**
   * Helper to externally set the Salesforce SOAP Partner. Used for simpletests.
   */
  public function setSalesforceSoap(SalesforceSoapPartner $soap = NULL) {
    $this->salesforceSync->setSalesforceSoap($soap);
  }

  /**
   * Helper to remove newly created items from Salesforce. Used for simpletests.
   */
  public function deleteNewSfRecords() {
    return $this->salesforceSync->deleteNewSfRecords();
  }
}
