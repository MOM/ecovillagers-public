<?php

/**
 * @file
 * Contains SalesforceQueue
 */

/**
 * Salesforce specific implementation of DrupalQueue
 */
class SalesforceQueue implements DrupalReliableQueueInterface {

  /**
   * The name of the queue this instance is working with.
   *
   * The 'all' queue is the multi-queue manager
   *
   * @var string
   */
  public $queueName;

  /**
   * The queues that the 'all' queue manages.
   *
   * @var array
   */
  protected $trackedQueues;

  /**
   * Expire times for the leases on the various sub queues.
   *
   * @var array
   */
  protected $leases = array();

  /**
   * A queue object for the given queue.
   *
   * @param string $queue_name
   *   Arbitrary string to name a subset of a queue.  Standard queues are 'new',
   *   'retry', and 'fail'.  The default name 'all' is a working name
   *   allowing you to have access to all queue items regardless of which queue
   *   subset they are in.
   */
  public static function get($queue_name = 'all') {
    $queue_name = empty($queue_name) ? 'all' : $queue_name;

    // Use the advanced drupal_static() pattern, since this can end up being
    // called repeatedly during queue batch processing.
    static $drupal_static_fast;
    if (!isset($drupal_static_fast)) {
      $drupal_static_fast['queues'] = &drupal_static(__FUNCTION__);
    }
    $queues = &$drupal_static_fast['queues'];
    if (!isset($queues[$queue_name])) {
      $queues[$queue_name] = new SalesforceQueue($queue_name);
    }
    return $queues[$queue_name];
  }

  /**
   * @name DrupalQueueInterface  The required interface methods
   * @{
   */

  /**
   * Construct object.
   *
   * @param string $queue_name
   *   Declare which queue subset you are working with.  Use 'all' to work with
   *   all items in the entire queue.
   */
  public function __construct($queue_name) {
    $this->queueName = $queue_name;

    // Tracked queues are those the 'all' queue manages.
    $this->trackedQueues = variable_get('salesforce_queue_tracked_queues', array('new', 'retry'));
  }

  /**
   * Add an item to the queue.
   *
   * If an item with identical values for drupal_id, module, delta and
   * object_type is already in the queue, the item in the queue will be
   * updated with the data provided rather than another queue item created.
   *
   * @param array $data
   *   A key array with the following:
   *     - drupal_id: Unique identifier of the Drupal object, such as the
   *         entity ID
   *     - module: Module implementing the data type
   *     - delta: Name or id of the subtype
   *     - object_type: Salesforce object type
   *     - operation: Action to take on Salesforce, CREATE, UPDATE, UPSERT, or
   *         DELETE
   *     - dedupe_field: Salesforce field to dedupe on during UPSERT operations
   *     - sobject: Salesforce sObject
   *
   * @return bool|int
   *   If the item insert or update failed, returns FALSE. If it succeeded,
   *   returns SAVED_NEW or SAVED_UPDATED, depending on the operation performed.
   */
  public function createItem($data) {
    // Abort if we did not receive a valid item that can be queued.
    if (!$this->isValidItem($data)) {
      // Send an error to admin that we couldn't save to the queue.
      watchdog('salesforce', '[@id] Submitted item could not be queued.',
        array('@id' => 'queue-01'), WATCHDOG_CRITICAL);
      return FALSE;
    }

    $keys = array();
    if ($this->itemInQueue($data)) {
      // If this item is in the queue, replace the original.
      // With drupal_write_record, replacement is just a matter of filling in
      // the $keys array.
      $keys = array('drupal_id', 'module', 'delta', 'object_type');
    }
    else {
      // As a new record, fill in all the new fields.
      $data['queue'] = $this->queueName == 'all' ? 'new' : $this->queueName;

      // We cannot rely on REQUEST_TIME because many items might be created
      // by a single request which takes longer than 1 second.
      $data['created'] = time();
    }

    // If sync_rules hasn't been set, add an empty array to make the database
    // happy and make it slightly easier on the developer to not be required.
    if (!isset($data['sync_rules'])) {
      $data['sync_rules'] = array();
    }

    // Invoke hook_salesforce_queue_create_item_alter().
    drupal_alter('salesforce_queue_create_item', $data);

    // Insert this baby.
    $data['sobject'] = json_encode($data['sobject']);
    $result = drupal_write_record('salesforce_queue', $data, $keys);

    // Invoke hook_salesforce_queue_create_item().
    module_invoke_all('salesforce_queue_create_item', $data, $result);

    return $result;
  }

  /**
   * Quantity of items in the queue you have initialized.
   *
   * @param bool $only_tracked_queues
   *   Whether or not the 'all' queue should count all items in the queue or
   *   only items that are within the queues it tracks.  Defaults to FALSE so
   *   it will count all items in the queue by default.
   *
   * @return int
   *   Quanity of items found
   */
  public function numberOfItems($only_tracked_queues = FALSE) {
    $query = db_select('salesforce_queue', 'q')
      ->fields('q', array('item_id'));
    if ($this->queueName != 'all') {
      $query->condition('queue', $this->queueName);
    }
    elseif ($only_tracked_queues) {
      $query->condition('queue', $this->trackedQueues, 'IN');
    }
    return $query
      ->countQuery()
      ->execute()
      ->fetchField();
  }

  /**
   * Wrapper for claimBatch() to claim just a single item from the queue.
   *
   * @param int $lease_time
   *   The amount of time you believe it will take to process the item.  If your
   *   process takes longer, another process could take the item.
   *
   * @return object
   *   Returns all the information about the item from the queue.
   */
  public function claimItem($lease_time = 3600) {
    $items = $this->claimBatch(1, $lease_time);
    if (empty($items)) {
      return FALSE;
    }
    return $items[0];
  }

  /**
   * Wrapper for releaseBatch() which will release the queue.
   *
   * @param object $item
   *   The original queue item as given to you in claimItem()
   *
   * @return bool
   *   TRUE if the release could be granted.  FALSE if the release could not be
   *   granted because the wrong key was granted.
   */
  public function releaseItem($item) {
    if (is_object($item)) {
      return $this->releaseBatch($item->leaseKey);
    }
    return FALSE;
  }

  /**
   * Remove an item from the queue.
   *
   * @param object $item
   *   The original queue item as given to you in claimItem()
   *
   * @return bool
   *   TRUE on successful delete, FALSE if the delete could not be performed
   */
  public function deleteItem($item) {
    if (!is_object($item)) {
      // Cannot delete from this kind of item.
      return FALSE;
    }

    // Invoke hook_salesforce_queue_delete_item().
    module_invoke_all('salesforce_queue_delete_item', $item);

    $result = db_delete('salesforce_queue')
      ->condition('drupal_id', $item->drupal_id)
      ->condition('module', $item->module)
      ->condition('delta', $item->delta)
      ->condition('object_type', $item->object_type)
      ->execute();

    return $result;
  }

  /**
   * Create a new queue.
   */
  public function createQueue() {
    // All tasks are stored in a single database table (which is created when
    // salesforce_queue is first installed) so there is nothing we need to do to
    // create a new queue.
  }

  /**
   * Delete all queued items in the initiated queue.
   *
   * @return bool
   *   TRUE on successful delete, FALSE if the delete could not be performed
   */
  public function deleteQueue() {
    // Can't hold a lease on nothing, so force the release of the queue.
    $this->releaseBatch(NULL, TRUE);
    $query = db_delete('salesforce_queue');
    if ($this->queueName != 'all') {
      $query->condition('queue', $this->queueName);
    }
    return $query->execute();
  }

  /**
   * @} DrupalQueueInterface
   */

  /**
   * Helper to open an item after it has been retreived from the database.
   *
   * @param object $item
   *   A record as retreived from the database
   *
   * @return object
   *   The record formatted for general use
   */
  protected function unfoldItem($item) {
    if (is_object($item)) {
      $item->sobject = json_decode($item->sobject);
      if (isset($item->sobject->fields)) {
        $item->sobject->fields = (array) $item->sobject->fields;
      }
      $item->sync_rules = unserialize($item->sync_rules);
    }
    return $item;
  }

  /**
   * Grab a batch of items from the queue and inform the queue is leased.
   *
   * DrupalQueue first selects a row and then tries to update the row, and
   * will try again if the update fails because another worker took it in the
   * mean time.  For our situation with Salesforce, we do not need to worry
   * about the concurrency issue because the queue *must* be processed
   * linearly due to the dependencies of queue items (e.g.: Accounts must be
   * sent before any Opportunities queued after them).  In an asyncronous
   * worker, these dependencies could break (e.g.: an Opportunity queued after
   * a dependant Account could be processed earlier).  We do not nead to lock
   * any items in the queue but merely state that we've got a lease on the
   * entire table.
   *
   * @param int $quantity
   *   The maximum number of items to retreive from the queue.  If the queue
   *   does not have that many items, all remaining items will be retreived.
   * @param int $lease_time
   *   The amount of time you believe it will take to process the items.  If
   *   your process takes longer, another process could take the items.
   *
   * @return array
   *   Returns an array of objects retreived from the queue up to the number of
   *   items requested for $quantity. FALSE if no items were retreived from the
   *   queue.
   */
  public function claimBatch($quantity = 1000, $lease_time = 3600) {
    // Don't claim any items if a current process has claimed a lease on the
    // rights to process this queue.
    $items = array();
    $key = $this->leaseQueue($lease_time);
    if ($key) {
      $query = db_select('salesforce_queue', 'q')
        ->fields('q')
        ->range(0, $quantity)
        // Always oldest first regardless of status.
        ->orderBy('created', 'ASC');
      if ($this->queueName == 'all') {
        // The 'all' queue manages across multiple queues.
        // NOTE: Prior version added items from the 'retry' queue only after all
        // items from the 'new' queue have been processed. But, due to
        // dependency issues when creating Salesforce objects, I am going to
        // always process older items first regardless of status.  The 'failed'
        // queue, though, is not a tracked queue so they would  not be included.
        $query->condition('queue', $this->trackedQueues, 'IN');
      }
      else {
        $query->condition('queue', $this->queueName);
      }
      $result = $query->execute();
      foreach ($result as $record) {
        $item = $this->unfoldItem($record);
        $item->leaseKey = $key;
        $items[] = $item;
      }
      if (empty($items)) {
        // Nothing there. Release the lease.
        $this->releaseBatch($key);
      }
    }
    else {
      // Send a warning that there was an attempt to claim items when the queue
      // was leased.
      watchdog('salesforce', '[@id] A claim was attempted on a leased queue.',
        array('@id' => 'queue-02'), WATCHDOG_DEBUG);
    }
    return empty($items) ? FALSE : $items;
  }

  /**
   * Release the queue so another batch can be started.
   *
   * @param string $key
   *   Unique identifier of the process that leased the queue
   * @param bool $force
   *   TRUE to force the lease to be released, FALSE to follow proper checks.
   *   Use this parameter only if you know exactly what you are doing.  For
   *   example, this is used to force the release of the lease when a queue is
   *   deleted.
   *
   * @return bool
   *   TRUE if the release could be granted.  FALSE if the release could not be
   *   granted because the wrong key was granted.
   */
  public function releaseBatch($key, $force = FALSE) {
    $lease_var = 'salesforce_queue_' . $this->queueName . '_lease';
    $key_var = $lease_var . '_key';
    $current_key = variable_get($key_var, NULL);
    if ($key == $current_key || $force) {
      lock_release($lease_var);
      return TRUE;
    }
    return FALSE;
  }

  /**
   * Claim a lease on the queue.
   *
   * @param int $lease_time
   *   The amount of time the queue will be leased to you before it will be
   *   opened to be leased to other processes.
   *
   * @return string
   *   A unique key that allows you to then release the lease prior to the lease
   *   time expiring.  FALSE if the queue is already leased.
   */
  public function leaseQueue($lease_time) {
    if ($this->queueIsLeased()) {
      // Queue is leased, I cannot lease it.
      return FALSE;
    }
    $lease_var = 'salesforce_queue_' . $this->queueName . '_lease';
    if (lock_acquire($lease_var, $lease_time)) {
      // The process that requests the lease gets a unique identifier as a key
      // that allows them to be the only process to lock and unlock the queue.
      // Otherwise, if multiple processes get kicked off simultaneously, they
      // can mistakenly unlock the original process' lease and cause overlapping
      // processing of the queue.
      $key = hash('md5', serialize($_SERVER) . uniqid());
      variable_set($lease_var . '_key', $key);
      return $key;
    }
    return FALSE;
  }

  /**
   * Discover if the queue can be leased to you or not.
   *
   * @return boolean
   *   TRUE if the queue is leased, FALSE if the queue is not leased
   */
  public function queueIsLeased() {
    // If the 'all' queue has a lease, the queues the 'all' queue manages cannot
    // get a lease.
    $queues_can_block_all = $this->trackedQueues;
    $queues_can_block_all[] = 'all';
    if (in_array($this->queueName, $queues_can_block_all) && !lock_may_be_available('salesforce_queue_all_lease')) {
      // The current queue is tracked by 'all' and 'all' is leased.
      return TRUE;
    }

    // If a queue is not a tracked queue, or 'all' is not leased, then all
    // we have to do is check that queue's lease time.
    if ($this->queueName != 'all') {
      if (lock_may_be_available('salesforce_queue_' . $this->queueName . '_lease')) {
        // Current queue is not leased.
        return FALSE;
      }
      // Current queue is leased.
      return TRUE;
    }

    // The 'all' queue cannot be leased when any of its tracked queues are
    // leased.
    foreach ($this->trackedQueues as $queue_name) {
      if (!lock_may_be_available('salesforce_queue_' . $queue_name . '_lease')) {
        // This queue is leased.
        return TRUE;
      }
    }
    // None of the tracked queues is leased, there's no lease to worry about.
    return FALSE;
  }

  /**
   * Check to see if a given item is already in the queue.
   *
   * @param array $data
   *   An array of data that is typically used in createItem() to send to queue.
   *   The nessisary keys for this method are:
   *     - drupal_id: Unique identifier of the Drupal object, such as the
   *         entity ID
   *     - module: Module implementing the data type
   *     - delta: Name or id of the subtype
   *     - object_type: Salesforce object type
   *
   * @return bool
   *   TRUE if the item is in the queue, FALSE if the item is not
   */
  public function itemInQueue($data) {
    if (!$this->isValidItem($data)) {
      return FALSE;
    }
    $count = db_select('salesforce_queue', 'q')
      ->fields('q', array('item_id'))
      ->condition('drupal_id', $data['drupal_id'])
      ->condition('module', $data['module'])
      ->condition('delta', $data['delta'])
      ->condition('object_type', $data['object_type'])
      ->countQuery()
      ->execute()
      ->fetchField();
    return $count > 0;
  }

  /**
   * Retreive an item from the queue.
   *
   * Do NOT use this to process an item. 'Get' does not lease the queue and
   * merely provides you the information about the queue item.  In order to
   * retreive an item for processing, you must 'claim' it.
   *
   * @param int $drupal_id
   *   Unique identifier of the Drupal object, such as the entity ID
   * @param string $module
   *   Module implementing the data type
   * @param varchar $delta
   *   Name or id of the subtype
   * @param string $object_type
   *   Salesforce object type
   *
   * @return object
   *   The queue item you requested, or FALSE if the item is not there
   */
  public function getItem($drupal_id, $module, $delta, $object_type) {
    $item = db_select('salesforce_queue', 'q')
      ->fields('q')
      ->condition('drupal_id', $drupal_id)
      ->condition('module', $module)
      ->condition('delta', $delta)
      ->condition('object_type', $object_type)
      ->execute()
      ->fetchObject();
    $item = $this->unfoldItem($item);
    return $item;
  }

  /**
   * Helper to check if a given array or object is valid queue data.
   */
  protected function isValidItem($item) {
    $data = is_object($item) ? (array) $item : $item;
    $required = array(
      'drupal_id',
      'module',
      'delta',
      'object_type',
      'operation',
      'sobject',
    );
    $provided = array_keys($data);
    if (count(array_intersect($required, $provided)) < 6) {
      // When it doesn't have all of the required fields, it is not valid.
      return FALSE;
    }
    return TRUE;
  }
}
