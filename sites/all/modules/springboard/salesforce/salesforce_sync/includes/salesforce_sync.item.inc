<?php

/**
 * @file
 * Helper for constructing common Salesforce objects.
 */

/**
 * Helper class to build the base structure of a sync item.
 */
class SalesforceSyncItem {

  /**
   * Constructs a SalesforceSyncItem.
   *
   * @param string $object_type
   *   The type of object the item is as it lives in Salesforce, such as
   *   'Contact' or 'Opportunity'.
   * @param string $operation
   *   The operation to perform against the target system.  The supported
   *   options are 'CREATE', 'UPSERT', 'UPDATE', 'DELETE' and 'UNDELETE'.
   * @param array $sync_rules
   *   Instructions for how the item should syncronize with its consumer.  It is
   *   formatted as follows:
   *   <code>
   *     $sync_rules = array(
   *       'FirstName' => SALESFORCE_SYNC_RULE_ALWAYS,
   *       'Email' => SALESFORCE_SYNC_RULE_BLANK,
   *     );
   *   </code>
   * @param string $dedupe_field
   *   The field with which whose value identifies this record as a unique item,
   *   such as 'Email' or 'Name'.
   */
  public function __construct($object_type = '', $operation = NULL, $sync_rules = array(), $dedupe_field = NULL) {
    $this->sobject = new SalesforceObject($object_type);
    $this->setObjectType($object_type);
    $this->setDedupeField($dedupe_field);
    $this->setOperation($operation);
    $this->sync_rules = $sync_rules;
  }

  /**
   * Wrapper for the sobject to set the Salesforce Id.
   *
   * @param string $id
   *   The Salesforce id of the item.
   */
  public function setId($id) {
    $this->sobject->setId($id);
  }

  /**
   * Helper to set the object type.
   *
   * @param string $object_type
   *   The Salesforce object to set.
   */
  public function setObjectType($object_type) {
    $this->object_type = $object_type;
    $this->sobject->setObjectType($object_type);
  }

  /**
   * Wrapper for the sobject to set the record type.
   *
   * @param string $record
   *   The type of record to set.
   */
  public function setRecord($record) {
    $this->sobject->setRecord($record);
  }

  /**
   * Wrapper for the sobject to set the record type.
   *
   * @param string $record
   *   The type of record to set.
   */
  public function setRecordType($record) {
    $this->sobject->setRecordType($record);
  }

  /**
   * Wrapper for the sobject to set the recordTypeId.
   *
   * @param string $record_type_id
   *   The recordTypeId to set.
   */
  public function setRecordTypeId($record_type_id) {
    $this->sobject->setRecordTypeId($record_type_id);
  }

  /**
   * Helper to set the operation.
   *
   * @param string $operation
   *   The operation to perform against Salesforce: CREATE, UPSERT, UPDATE,
   *   DELETE or UNDELETE
   */
  public function setOperation($operation) {
    $this->operation = $operation;
  }

  /**
   * Helper to set the dedupe field.
   *
   * @param string $dedupe_field
   *   The Salesforce field to be the dedupe field.
   */
  public function setDedupeField($dedupe_field) {
    $this->dedupe_field = $dedupe_field;
  }

  /**
   * Wrapper for the sobject to add a field to the fields array.
   *
   * @param string $field_name
   *   The Salesforce machine name of the field.
   * @param string $field_value
   *   Value of the field to set.
   */
  public function addField($field_name, $field_value) {
    $this->sobject->addField($field_name, $field_value);
  }

  /**
   * Wrapper for the sobject to add a field to the fieldsToNull array.
   *
   * @param string $field_name
   *   The Salesforce machine name of the field.
   */
  public function addFieldToNull($field_name) {
    $this->sobject->addFieldToNull($field_name);
  }
}

/**
 * Helper class to build the base structure of a sObject.
 */
class SalesforceObject {

  /**
   * Unique identifier provided by Salesforce.
   *
   * @var string
   */
  public $Id;

  /**
   * Type of object in Salesforce, such as 'Contact' or 'Opportunity'.
   *
   * @var string
   */
  public $type;

  /**
   * Subtype of the object type in Salesforce.  Not all have a record.
   *
   * @var type
   */
  public $record;

  /**
   * Values of the fields for this record.
   *
   * The array is formatted as follows:
   *   <code>
   *     $fields = array(
   *       'FirstName' => 'John',
   *       'LastName' => 'Doe',
   *       'Email' => 'john.doe@example.com',
   *     );
   *   </code>
   *
   * @var array
   */
  public $fields = array();

  /**
   * Instructions to Salesforce for which fields to null.
   *
   * The array is an unassociated array of field names, such as:
   *   <code>
   *     $fieldsToNull = array(
   *       'FirstName',
   *       'LastName',
   *       'Email',
   *     );
   *   </code>
   *
   * @var type
   */
  public $fieldsToNull = array();

  /**
   * Constructs a sObject.
   *
   * @param string $object_type
   *   The type of object the item is as it lives in Salesforce, such as
   *   'Contact' or 'Opportunity'.
   * @param array $fields
   *   An array of field names and values of the names for this record.  It is
   *   formatted as follows:
   *   <code>
   *     $fields = array(
   *       'FirstName' => 'John',
   *       'LastName' => 'Doe',
   *       'Email' => 'john.doe@example.com',
   *     );
   *   </code>
   * @param string $record
   *   Subtype of the object type.
   */
  public function __construct($object_type = '', $fields = array(), $record = NULL) {
    $this->fields = $fields;
    $this->setType($object_type);
    $this->setRecord($record);
  }

  /**
   * Helper to set the Id.
   *
   * @param string $id
   *   The Salesforce Id to set.
   */
  public function setId($id) {
    $this->Id = $id;
  }

  /**
   * Helper to set the object type.
   *
   * @param string $object_type
   *   The type of object type to set.
   */
  public function setType($object_type) {
    $this->type = $object_type;

    // Set the record type once again to ensure the record type id is valid.
    if (!empty($this->record)) {
      $this->setRecord($this->record);
    }
  }

  /**
   * Wrapper for setType().
   */
  public function setObjectType($object_type) {
    $this->setType($object_type);
  }

  /**
   * Helper to set the record type.
   *
   * @param string $record
   *   The type of record to set.
   */
  public function setRecord($record) {
    $this->record = $record;

    // The SOAP partner does not pull the record type from the object, but
    // rather the RecordTypeId from the fields array.  Setting the RecordTypeId
    // to ensure the record type is properly recorded.
    if (isset($this->fields['RecordTypeId'])) {
      unset($this->fields['RecordTypeId']);
    }
    if ($this->recordTypeIdFieldExists()) {
      $sfapi = salesforce_get_api();
      if ($sfapi->isAuthorized()) {
        // NOTE: objectDescribe() is cached.
        $object = $sfapi->objectDescribe($this->type);
        if (isset($object['recordTypeInfos'])) {
          foreach ($object['recordTypeInfos'] as $info) {
            if ($info['name'] == $record) {
              $this->fields['RecordTypeId'] = $info['recordTypeId'];
            }
          }
        }
      }
    }
  }

  /**
   * Wrapper for setRecord().
   */
  public function setRecordType($record) {
    $this->setRecord($record);
  }

  /**
   * Helper to set the record type by RecordTypeId.
   *
   * @param string $record_type_id
   *   The recordTypeId to set.
   */
  public function setRecordTypeId($record_type_id) {
    if ($this->recordTypeIdFieldExists()) {
      $this->fields['recordTypeId'] = $record_type_id;
    }

    // Set the record type to what coresponds with the id.
    $this->record = NULL;
    if (!empty($this->type)) {
      $sfapi = salesforce_get_api();
      if ($sfapi->isAuthorized()) {
        // NOTE: objectDescribe() is cached.
        $object = $sfapi->objectDescribe($this->type);
        if (isset($object['recordTypeInfos'])) {
          foreach ($object['recordTypeInfos'] as $info) {
            if ($info['recordTypeId'] == $record_type_id) {
              $this->record = $info['name'];
            }
          }
        }
      }
    }
  }

  /**
   * Helper to add a field to the fields array.
   *
   * @param string $field_name
   *   The Salesforce machine name of the field.
   * @param string $field_value
   *   Value of the field to set.
   */
  public function addField($field_name, $field_value) {
    $this->fields[$field_name] = $field_value;
  }

  /**
   * Helper to add a field to the fieldsToNull array.
   *
   * @param string $field_name
   *   The Salesforce machine name of the field.
   */
  public function addFieldToNull($field_name) {
    if (!in_array($field_name, $this->fieldsToNull)) {
      $this->fieldsToNull[] = $field_name;
    }
  }

  /**
   * Helper to check that the object type has a RecordTypeId field.
   */
  protected function recordTypeIdFieldExists() {
    // The RecordTypeId field is dynamically created and removed by Salesforce.
    // Even if there is a master record type and no custom records types, if the
    // user deleted custom record types Salesforce would have automatically
    // removed the RecordTypeId field.
    if (!empty($this->type)) {
      $sfapi = salesforce_get_api();
      if ($sfapi->isAuthorized()) {
        // NOTE: objectDescribe() is cached.
        $object = $sfapi->objectDescribe($this->type);
        foreach ($object['fields'] as $field) {
          if ($field['name'] == 'RecordTypeId') {
            return TRUE;
          }
        }
      }
    }
    return FALSE;
  }
}
