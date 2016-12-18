<?php

/**
 * @file
 * Hooks that are invoked by Salesforce Sync.
 */

/**
 * @defgroup salesforce_sync_hooks Salesforce Sync Hooks
 * @{
 */

/**
 * Fire off behavior when an item succeeds processing.
 *
 * @param object $item
 *   Queue item
 * @param object $result
 *   The Salesforce response after the call was made
 */
function hook_salesforce_sync_pass_item($item, $result) {

}

/**
 * Fire off behavior when an item fails processing.
 *
 * @param object $item
 *   Queue item
 * @param string $message
 *   Message explaining why the item failed.
 * @param mixed $result
 *   Information about the failure, likely a Salesforce result object
 */
function hook_salesforce_sync_fail_item($item, $message, $result) {

}

/**
 * Fire off behavior when an item fails processing.
 *
 * @param object $batch
 *   Batch sent for processing.
 * @param string $message
 *   Message explaining why the batch failed.
 * @param mixed $result
 *   Information about the failure, likely a Salesforce result object.
 */
function hook_salesforce_sync_fail_batch($batch, $message, $result) {

}

/**
 * @}
 */
