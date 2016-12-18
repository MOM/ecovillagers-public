<?php
/**
 * @file
 * Provides views table data for queue_api related tables.
 */

/**
 * Implements hook_views_data().
 */
function springboard_views_queue_api_views_data() {
  $data = array();
  // SF queue table metadata
  $data['sf_queue']['table'] = array(
    'group' => t('Salesforce queue'),
    'base' => array(
      'field' => 'id',
      'title' => t('Salesforce queue'),
      'help' => t('Items in the active queue to be synced to Salesforce.'),
    ),
  );
  // SF queue fields
  $data['sf_queue']['id'] = array(
    'title' => t('Primary key: ID'),
    'help' => t('The primary key of the sf_queue table.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['sf_queue']['oid'] = array(
    'title' => t('Object ID'),
    'help' => t('The ID of the object.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'base' => 'salesforce_management_object_map',
      'base field' => 'oid',
      'extra' => array(
        array(
          'field' => 'type',
          'value type' => 'field',
          'value' => 'drupal_type',
        ),
      ),
      'handler' => 'views_handler_relationship',
      'join_handler' => 'springboard_views_join',
      'label' => t('Queued object'),
    ),
  );
  $data['sf_queue']['oid_user'] = array(
    'title' => t('User object'),
    'help' => t('Drupal user object.'),
    'relationship' => array(
      'relationship field' => 'oid',
      'base' => 'users',
      'base field' => 'uid',
      'extra' => array(
        array(
          'table type' => 'left',
          'table' => 'sf_queue',
          'field' => 'type',
          'value type' => 'value',
          'value' => 'user',
        ),
      ),
      'handler' => 'views_handler_relationship',
      'join_handler' => 'springboard_views_join',
      'label' => t('User object'),
    ),
  );
  $data['sf_queue']['oid_donation'] = array(
    'title' => t('Donation object'),
    'help' => t('Drupal donation (Ubercart order) object.'),
    'relationship' => array(
      'relationship field' => 'oid',
      'base' => 'uc_orders',
      'base field' => 'order_id',
      'extra' => array(
        array(
          'table type' => 'left',
          'table' => 'sf_queue',
          'field' => 'type',
          'value type' => 'value',
          'value' => 'donation',
        ),
      ),
      'handler' => 'views_handler_relationship',
      'join_handler' => 'springboard_views_join',
      'label' => t('Donation object'),
    ),
  );
  $data['sf_queue']['type'] = array(
    'title' => t('Object type'),
    'help' => t('The object type.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_in_operator',
      'options callback' => 'springboard_views_sf_drupal_types',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['sf_queue']['sfid'] = array(
    'title' => t('Salesforce ID'),
    'help' => t('The Salesforce ID associated with this queued object.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['sf_queue']['fieldmap'] = array(
    'title' => t('Fieldmap'),
    'help' => t('The ID of the fieldmap associated with this queued object.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['sf_queue']['action'] = array(
    'title' => t('Action'),
    'help' => t('The action to perform when syncing.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['sf_queue']['created'] = array(
    'title' => t('Created'),
    'help' => t('The date this item was added to the queue.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
  );

  // --------------------------------------------------------------------------
  // SF retry queue table metadata
  $data['sf_retry_queue']['table'] = array(
    'group' => t('Salesforce retry queue'),
    'base' => array(
      'field' => 'id',
      'title' => t('Salesforce retry queue'),
      'help' => t('Items in the retry queue to be synced to Salesforce.'),
    ),
  );

  // SF retry queue fields
  $data['sf_retry_queue']['id'] = array(
    'title' => t('Primary key: ID'),
    'help' => t('The primary key of the sf_retry_queue table.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['sf_retry_queue']['oid'] = array(
    'title' => t('Object ID'),
    'help' => t('The ID of the object.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'base' => 'salesforce_management_object_map',
      'base field' => 'oid',
      'extra' => array(
        array(
          'field' => 'type',
          'value type' => 'field',
          'value' => 'drupal_type',
        ),
      ),
      'handler' => 'views_handler_relationship',
      'join_handler' => 'springboard_views_join',
      'label' => t('Queued object'),
    ),
  );
  $data['sf_retry_queue']['oid_user'] = array(
    'title' => t('User object'),
    'help' => t('Drupal user object.'),
    'relationship' => array(
      'relationship field' => 'oid',
      'base' => 'users',
      'base field' => 'uid',
      'extra' => array(
        array(
          'table type' => 'left',
          'table' => 'sf_retry_queue',
          'field' => 'type',
          'value type' => 'value',
          'value' => 'user',
        ),
      ),
      'handler' => 'views_handler_relationship',
      'join_handler' => 'springboard_views_join',
      'label' => t('User object'),
    ),
  );
  $data['sf_retry_queue']['oid_donation'] = array(
    'title' => t('Donation object'),
    'help' => t('Drupal donation (Ubercart order) object.'),
    'relationship' => array(
      'relationship field' => 'oid',
      'base' => 'uc_orders',
      'base field' => 'order_id',
      'extra' => array(
        array(
          'table type' => 'left',
          'table' => 'sf_retry_queue',
          'field' => 'type',
          'value type' => 'value',
          'value' => 'donation',
        ),
      ),
      'handler' => 'views_handler_relationship',
      'join_handler' => 'springboard_views_join',
      'label' => t('Donation object'),
    ),
  );
  $data['sf_retry_queue']['type'] = array(
    'title' => t('Object type'),
    'help' => t('The object type.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_in_operator',
      'options callback' => 'springboard_views_sf_drupal_types',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['sf_retry_queue']['sfid'] = array(
    'title' => t('Salesforce ID'),
    'help' => t('The Salesforce ID associated with this queued object.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['sf_retry_queue']['fieldmap'] = array(
    'title' => t('Fieldmap'),
    'help' => t('The ID of the fieldmap associated with this queued object.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['sf_retry_queue']['action'] = array(
    'title' => t('Action'),
    'help' => t('The action to perform when syncing.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['sf_retry_queue']['created'] = array(
    'title' => t('Created'),
    'help' => t('The date this item was added to the retry queue.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
  );
  $data['sf_retry_queue']['retry_date'] = array(
    'title' => t('Retry date'),
    'help' => t('The date this item will be re-queued.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
  );
  $data['sf_retry_queue']['attempts'] = array(
    'title' => t('Attempts'),
    'help' => t('Number of attempts on this item.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // --------------------------------------------------------------------------
  // SF permanent failures table metadata
  $data['sf_permanent_failure']['table'] = array(
    'group' => t('Salesforce permanent failures'),
    'base' => array(
      'field' => 'id',
      'title' => t('Salesforce permanent failures'),
      'help' => t('Items in the retry queue to be synced to Salesforce.'),
    ),
  );

  // SF permanent failures fields
  $data['sf_permanent_failure']['id'] = array(
    'title' => t('Primary key: ID'),
    'help' => t('The primary key of the sf_permanent_failure table.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );
  $data['sf_permanent_failure']['oid'] = array(
    'title' => t('Object ID'),
    'help' => t('The ID of the object.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'base' => 'salesforce_management_object_map',
      'base field' => 'oid',
      'extra' => array(
        array(
          'field' => 'type',
          'value type' => 'field',
          'value' => 'drupal_type',
        ),
      ),
      'handler' => 'views_handler_relationship',
      'join_handler' => 'springboard_views_join',
      'label' => t('Queued object'),
    ),
  );
  $data['sf_permanent_failure']['oid_user'] = array(
    'title' => t('User object'),
    'help' => t('Drupal user object.'),
    'relationship' => array(
      'relationship field' => 'oid',
      'base' => 'users',
      'base field' => 'uid',
      'extra' => array(
        array(
          'table type' => 'left',
          'table' => 'sf_permanent_failure',
          'field' => 'type',
          'value type' => 'value',
          'value' => 'user',
        ),
      ),
      'handler' => 'views_handler_relationship',
      'join_handler' => 'springboard_views_join',
      'label' => t('User object'),
    ),
  );
  $data['sf_permanent_failure']['oid_donation'] = array(
    'title' => t('Donation object'),
    'help' => t('Drupal donation (Ubercart order) object.'),
    'relationship' => array(
      'relationship field' => 'oid',
      'base' => 'uc_orders',
      'base field' => 'order_id',
      'extra' => array(
        array(
          'table type' => 'left',
          'table' => 'sf_permanent_failure',
          'field' => 'type',
          'value type' => 'value',
          'value' => 'donation',
        ),
      ),
      'handler' => 'views_handler_relationship',
      'join_handler' => 'springboard_views_join',
      'label' => t('Donation object'),
    ),
  );
  $data['sf_permanent_failure']['type'] = array(
    'title' => t('Object type'),
    'help' => t('The object type.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_in_operator',
      'options callback' => 'springboard_views_sf_drupal_types',
    ),
  );
  $data['sf_permanent_failure']['fieldmap'] = array(
    'title' => t('Fieldmap'),
    'help' => t('The ID of the fieldmap.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  $data['sf_permanent_failure']['action'] = array(
    'title' => t('Action'),
    'help' => t('The action that was attempted when syncing.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );
  $data['sf_permanent_failure']['date_added'] = array(
    'title' => t('Date added'),
    'help' => t('The date this item was added to the permanent failures.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
  );

  // SF queue table metadata
  $data['sf_batch']['table'] = array(
    'group' => t('Salesforce batch'),
    'base' => array(
      'field' => 'id',
      'title' => t('Salesforce batch'),
      'help' => t('Items that have been moved to the batch before sending to Salesforce.'),
    ),
  );

  // SF queue fields
  $data['sf_batch']['id'] = array(
    'title' => t('Primary key: ID'),
    'help' => t('The primary key of the sf_batch table.'),
    'field' => array(
      'handler' => 'queue_api_handler_field_batch_id',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['sf_batch']['type'] = array(
    'title' => t('Object type'),
    'help' => t('The object type.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_in_operator',
      'options callback' => 'springboard_views_sf_drupal_types',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['sf_batch']['created'] = array(
    'title' => t('Created'),
    'help' => t('The date this item was added to the batch.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
  );
  $data['sf_batch']['record_count'] = array(
    'title' => t('Items'),
    'help' => t('Total count of items in this batch.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['sf_batch']['success_count'] = array(
    'title' => t('Successes'),
    'help' => t('Total count of successfuly processed items in this batch.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['sf_batch']['failure_count'] = array(
    'title' => t('Failures'),
    'help' => t('Total count of failed items in this batch.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['sf_batch']['start_time'] = array(
    'title' => t('Start time'),
    'help' => t('The date this batch was first processed.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
  );
  $data['sf_batch']['end_time'] = array(
    'title' => t('End time'),
    'help' => t('The date this batch completed processing.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
  );

  // --------------------------------------------------------------------------
  return $data;
}
