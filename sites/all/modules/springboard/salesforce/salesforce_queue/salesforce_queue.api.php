<?php

/**
 * @file
 * These are the hooks that are invoked by the Salesforce queue.
 */

/**
 * @defgroup salesforce_queue_hooks Salesforce Queue Hooks
 * @{
 * Salesforce Queue's hooks enable other modules to intercept events within
 * Salesforce Queue, such as the adding an item to the queue.
 */

/**
 * Alter an item before it is added to the queue.
 *
 * @param array $item
 *   Array of values to be added to the queue
 */
function hook_salesforce_queue_create_item_alter(&$item) {

}

/**
 * Fire off behavior after an item has been added to the queue.
 *
 * @param array $item
 *   Array of values that was added to the queue
 * @param bool $result
 *   If the item insert or update failed, returns FALSE. If it succeeded,
 *   returns SAVED_NEW or SAVED_UPDATED, depending on the operation performed.
 */
function hook_salesforce_queue_create_item($item, $result) {

}

/**
 * Fire off behavior before an item is deleted from the queue.
 *
 * @param object $item
 *   The object to be deleted from the queue
 */
function hook_salesforce_queue_delete_item($item) {

}

/**
 * Fire off behavior before the queue processing begins.
 *
 * This is triggered before any verification that the process is even capable of
 * being run
 *
 * @param SalesforceQueue $queue
 *   SalesforceQueue object
 */
function hook_salesforce_queue_preprocess_queue(SalesforceQueue $queue) {

}

/**
 * Allows you to alter items retreived from the queue before they are processed.
 *
 * @param array $items
 *   Array of queue objects
 * @param SalesforceQueue $queue
 *   SalesforceQueue object
 */
function hook_salesforce_queue_process_items_alter(&$items, $queue) {

}

/**
 * Fire off behavior after the queue processing completes.
 *
 * @param SalesforceQueue $queue
 *   SalesforceQueue object
 * @param int $end_response
 *   The status of the process when it ended.  Possible values are:
 *     - SALESFORCE_QUEUE_PROCESS_NOT_STARTED: No processing has been initiated
 *     - SALESFORCE_QUEUE_PROCESS_FAIL_CONNECT: Cannot connect to Salesforce
 *     - SALESFORCE_QUEUE_PROCESS_NO_ITEMS: There were no items found in the
 *         queue to process
 *     - SALESFORCE_QUEUE_PROCESS_FAIL_QUEUE_LEASED: Items cannot be claimed
 *         because the queue is already leased to another process
 *     - SALESFORCE_QUEUE_PROCESS_FAIL_CLAIM_ITEMS: Items cannot be claimed
 *         for an unknown reason
 *     - SALESFORCE_QUEUE_PROCESS_FAIL_NO_VALID_ITEMS: Although items were
 *         claimed from the queue, none of them passed validation
 *     - SALESFORCE_QUEUE_PROCESS_FAIL_LEASE_EXPIRED: The lease expired before
 *         all batches could be processed
 *     - SALESFORCE_QUEUE_PROCESS_COMPLETE: Items were found and processed all
 *         as expected
 */
function hook_salesforce_queue_postprocess_queue(SalesforceQueue $queue, $end_response) {

}

/**
 * Fire off behavior before a batch is processed.
 *
 * @param array $batch
 *   A batch array containing the salesforce object type, operation and items
 * @param SalesforceQueue $queue
 *   SalesforceQueue object
 */
function hook_salesforce_queue_preprocess_batch($batch, SalesforceQueue $queue) {

}

/**
 * Allows you to alter a batch before it is sent to Salesforce.
 *
 * @param array $batch
 *   Array of instructions that are used to formulate the API call to Salesforce
 * @param SalesforceQueue $queue
 *   SalesforceQueue object
 * @param SalesforceQueueProcessor $processor
 *   SalesforceQueueProcessor object
 */
function hook_salesforce_queue_batch_alter(&$batch, SalesforceQueue $queue, SalesforceQueueProcessor $processor) {

}

/**
 * Allows one final chance to alter the batch before it is sent to Salesforce.
 *
 * @param array $batch
 *   Array of instructions that are used to formulate the API call to Salesforce
 * @param SalesforceQueue $queue
 *   SalesforceQueue object
 * @param SalesforceQueueProcessor $processor
 *   SalesforceQueueProcessor object
 */
function hook_salesforce_queue_finalize_batch_alter(&$batch, SalesforceQueue $queue, SalesforceQueueProcessor $processor) {

}

/**
 * Fire off behavior after a batch is processed.
 *
 * @param array $batch
 *   A batch array containing the salesforce object type, operation and items
 * @param array $results
 *   The results of the process of sending the batch to Salesforce
 * @param SalesforceQueue $queue
 *   SalesforceQueue object
 */
function hook_salesforce_queue_postprocess_batch($batch, $results, SalesforceQueue $queue) {

}

/**
 * @}
 */
