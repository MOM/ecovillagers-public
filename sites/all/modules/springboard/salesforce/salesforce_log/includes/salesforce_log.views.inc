<?php

/**
 * @file
 * Views definition.
 */

/**
 * Implements hook_views_data().
 */
function salesforce_log_views_data() {
  // Main Salesforce log batch base table.
  // ----------------------------------------------------------------------
  // Define the base group of this table. Fields that don't have a group defined
  // will go into this field by default.
  $data['salesforce_log_batch']['table']['group']  = t('Salesforce batch log');

  // Advertise this table as a possible base table.
  $data['salesforce_log_batch']['table']['base'] = array(
    'field' => 'bid',
    'title' => t('Salesforce batch'),
    'help' => t("Salesforce batches contain logs of data synced to Salesforce."),
  );

  // Fields.
  // ----------------------------------------------------------------
  // Field batch id.
  $data['salesforce_log_batch']['bid'] = array(
    'title' => t('Batch Item ID'),
    'help' => t('The unique ID of the batch.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Field start timestamp.
  $data['salesforce_log_batch']['start'] = array(
    'title' => t('Start Timestamp'),
    'help' => t('The date the batch started.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );

  // Field end timestamp.
  $data['salesforce_log_batch']['end'] = array(
    'title' => t('End Timestamp'),
    'help' => t('The date the batch finished.)'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );

  // Field count.
  $data['salesforce_log_batch']['count'] = array(
    'title' => t('Count'),
    'help' => t('Total count of items in the batch.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Field successes.
  $data['salesforce_log_batch']['successes'] = array(
    'title' => t('Successes'),
    'help' => t('Amount of successesfully synced items in the batch.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Field failures.
  $data['salesforce_log_batch']['failures'] = array(
    'title' => t('Failures'),
    'help' => t('Amount of failed items in the batch.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Field module.
  $data['salesforce_log_batch']['module'] = array(
    'title' => t('Module'),
    'help' => t('The module linked to the items in this batch.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'SalesforceLogHandlerFilterModule',
    ),
  );

  // Field delta.
  $data['salesforce_log_batch']['delta'] = array(
    'title' => t('Delta'),
    'help' => t('The delta of the items in this batch.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  // Field object_type.
  $data['salesforce_log_batch']['object_type'] = array(
    'title' => t('Object type'),
    'help' => t('The Salesforce object of the items in this batch.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'SalesforceLogHandlerFilterObjectType',
    ),
  );

  // Field operation.
  $data['salesforce_log_batch']['operation'] = array(
    'title' => t('Operation'),
    'help' => t('The sync operation of this batch.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'SalesforceLogHandlerFilterOperation',
    ),
  );

  // Main Salesforce log item base table.
  // ----------------------------------------------------------------------
  // Define the base group of this table. Fields that don't have a group defined
  // will go into this field by default.
  $data['salesforce_log_item']['table']['group']  = t('Salesforce item log');

  // Advertise this table as a possible base table.
  $data['salesforce_log_item']['table']['base'] = array(
    'field' => 'lid',
    'title' => t('Salesforce batch items'),
    'help' => t("Salesforce items synced through the batch process."),
  );

  // Explain how this table joins to others.
  $data['salesforce_log_item']['table']['join'] = array(
    'salesforce_log_batch' => array(
      'left_field' => 'bid',
      'field' => 'bid',
    ),
  );

  // Fields.
  // ----------------------------------------------------------------
  // Field log item id.
  $data['salesforce_log_item']['lid'] = array(
    'title' => t('Log Item ID'),
    'help' => t('The unique ID of this item.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Field queue item id.
  $data['salesforce_log_item']['item_id'] = array(
    'title' => t('Item Queue ID'),
    'help' => t('The queue ID of this item.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'base' => 'salesforce_queue',
      'base field' => 'item_id',
      'handler' => 'views_handler_relationship',
      'label' => t('Queue item'),
      'title' => t('Queue item'),
      'help' => t('The item that is in the queue. This may not exist.'),
      'required' => FALSE,
    ),
  );

  // Field batch item id.
  $data['salesforce_log_item']['bid'] = array(
    'title' => t('Item Batch ID'),
    'help' => t('The batch ID this item was synced in.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'base' => 'salesforce_log_batch',
      'base field' => 'bid',
      'handler' => 'views_handler_relationship',
      'label' => t('Batch'),
      'title' => t('Batch'),
      'help' => t('The batch containing this item.'),
    ),
  );

  // Field Drupal id.
  $data['salesforce_log_item']['drupal_id'] = array(
    'title' => t('Drupal ID'),
    'help' => t('The Drupal ID of this item.'),
    'field' => array(
      'handler' => 'SalesforceLogHandlerFieldDrupalId',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Field module.
  $data['salesforce_log_item']['module'] = array(
    'title' => t('Module'),
    'help' => t('The module linked to the item.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'SalesforceLogHandlerFilterModule',
    ),
  );

  // Field delta.
  $data['salesforce_log_item']['delta'] = array(
    'title' => t('Delta'),
    'help' => t('The delta of the item.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  // Field queue.
  $data['salesforce_log_item']['queue'] = array(
    'title' => t('Queue'),
    'help' => t('The name of the processing queue this item was within.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'SalesforceLogHandlerFilterQueue',
    ),
  );

  // Field retries.
  $data['salesforce_log_item']['retries'] = array(
    'title' => t('Retries'),
    'help' => t('Number of times this item has failed attempts to be processed.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Field object_type.
  $data['salesforce_log_item']['object_type'] = array(
    'title' => t('Object type'),
    'help' => t('The Salesforce object of the items in this batch.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'SalesforceLogHandlerFilterObjectType',
    ),
  );

  // Field operation.
  $data['salesforce_log_item']['operation'] = array(
    'title' => t('Operation'),
    'help' => t('The sync operation of this batch.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'SalesforceLogHandlerFilterOperation',
    ),
  );

  // Field sobject.
  $data['salesforce_log_item']['sobject'] = array(
    'title' => t('Salesforce sObject'),
    'help' => t('The Salesforce sObject in json format.'),
    'field' => array(
      'handler' => 'SalesforceLogHandlerFieldSobject',
      'click sortable' => FALSE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  // Field dedupe field.
  $data['salesforce_log_item']['dedupe_field'] = array(
    'title' => t('Dedupe field'),
    'help' => t('The Salesforce field to dedupe on during UPSERT operations.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  // Field status.
  $data['salesforce_log_item']['status'] = array(
    'title' => t('Status'),
    'help' => t('The status of this item after it was synced.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  // Field error code.
  $data['salesforce_log_item']['error_code'] = array(
    'title' => t('Error code'),
    'help' => t('The error code returned from salesforce if this item failed to sync.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  // Field message.
  $data['salesforce_log_item']['message'] = array(
    'title' => t('Message'),
    'help' => t('The message returned from salesforce if this item failed to sync.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  // Field sfid.
  $data['salesforce_log_item']['sfid'] = array(
    'title' => t('Salesforce id'),
    'help' => t('The status of this item after it was synced.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  // Salesforce queue table.
  // ----------------------------------------------------------------------
  // Define the base group of this table. Fields that don't have a group defined
  // will go into this field by default.
  $data['salesforce_queue']['table']['group']  = t('Salesforce queue');

  // Advertise this table as a possible base table.
  $data['salesforce_queue']['table']['base'] = array(
    'field' => 'item_id',
    'title' => t('Salesforce queue'),
    'help' => t("Drupal objects queued to sync to Salesforce."),
  );

  // Fields.
  // ----------------------------------------------------------------
  // Field item id.
  $data['salesforce_queue']['item_id'] = array(
    'title' => t('Queue ID'),
    'help' => t('The queue ID of this item.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Field Drupal id.
  $data['salesforce_queue']['drupal_id'] = array(
    'title' => t('Drupal ID'),
    'help' => t('The Drupal ID of this item.'),
    'field' => array(
      'handler' => 'SalesforceLogHandlerFieldDrupalId',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Field module.
  $data['salesforce_queue']['module'] = array(
    'title' => t('Module'),
    'help' => t('The module linked to the items in this batch.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'SalesforceLogHandlerFilterModule',
    ),
  );

  // Field delta.
  $data['salesforce_queue']['delta'] = array(
    'title' => t('Delta'),
    'help' => t('The delta of the items in this batch.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  // Field object_type.
  $data['salesforce_queue']['object_type'] = array(
    'title' => t('Object type'),
    'help' => t('The Salesforce object of the items in this batch.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'SalesforceLogHandlerFilterObjectType',
    ),
  );

  // Field operation.
  $data['salesforce_queue']['operation'] = array(
    'title' => t('Operation'),
    'help' => t('The sync operation of this batch.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'SalesforceLogHandlerFilterOperation',
    ),
  );

  // Field dedupe field.
  $data['salesforce_queue']['dedupe_field'] = array(
    'title' => t('Dedupe field'),
    'help' => t('The Salesforce field to dedupe on during UPSERT operations.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  // Field sobject.
  $data['salesforce_queue']['sobject'] = array(
    'title' => t('Salesforce sObject'),
    'help' => t('The Salesforce sObject in json format.'),
    'field' => array(
      'handler' => 'SalesforceLogHandlerFieldSobject',
      'click sortable' => FALSE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  // Field sobject.
  $data['salesforce_queue']['sync_rules'] = array(
    'title' => t('Sync rules'),
    'help' => t('A serialized array that stores the sync rules for each field in the sObject.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  // Field queue.
  $data['salesforce_queue']['queue'] = array(
    'title' => t('Queue'),
    'help' => t('The name of the processing queue this item is within.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'SalesforceLogHandlerFilterQueue',
    ),
  );

  // Field retries.
  $data['salesforce_queue']['retries'] = array(
    'title' => t('Retries'),
    'help' => t('Number of times this item as failed attempts to be processed.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Field created.
  $data['salesforce_queue']['created'] = array(
    'title' => t('Created Timestamp'),
    'help' => t('Timestamp of when the item was created.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );

  return $data;
}
