<?php

/**
 * @file
 * Manages webform to Salesforce mappings.
 */

/**
 * Install the fieldmap.
 */
function _fundraiser_sustainers_upgrade_salesforce_install() {
  fundraiser_sustainers_upgrade_webform_fieldmap();
}

/**
 * Implements hook_uninstall().
 */
function fundraiser_sustainers_upgrade_salesforce_uninstall() {

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'salesforce_genmap_map');
  $query->propertyCondition('module', 'fundraiser_sustainers_upgrade');
  // This should use the constant, but it doesn't work.
  $query->propertyCondition('nid', -40);
  $result = $query->execute();
  if (!empty($result)) {
    $mids = array_keys($result['salesforce_genmap_map']);
    entity_delete('salesforce_genmap_map', $mids[0]);
  }
}


/**
 * Create the sustainers upgrade fieldmap.
 */
function fundraiser_sustainers_upgrade_webform_fieldmap() {
  // Create default SF map insert into table.
  $map = array();
  $map = entity_create('salesforce_genmap_map', $map);
  $map->nid = -40;
  $map->map_handler = 'webform';
  $map->salesforce_object_type = 'Sustainers_Upgrade__c';
  $object_type = '';
  module_load_include('inc', 'salesforce_genmap', 'includes/salesforce_genmap.map');
  $map->salesforce_record_type = $object_type;
  $map->field_map = array(
    'webform_map' => array(
      'fsu_amount' => 'Upgrade_Amount__c',
      'fsu_did' => 'Donation_ID__c',
      'fsu_uid' => 'User_ID__c',
      'fsu_status_flag' => 'Status_Flag__c',
      'fsu_timestamp' => 'Timestamp__c',
      'fsu_form_id' => 'Form_ID__c',
      'fsu_url' => 'Form_URL__c',
      'referrer' => 'Referrer__c',
      'initial_referrer' => 'Initial_Referrer__c',
      'ms' => 'Market_Source__c',
      'user_agent' => 'User_Agent__c',
      'utm_content' => 'UTM_content__c',
      'utm_medium' => 'UTM_medium__c',
      'utm_source' => 'UTM_source__c',
      'utm_term' => 'UTM_term__c',
    ),
  );
  $map->sync_options = array(
    'insert' => 'insert',
    'update' => 'update',
    'delete' => 'delete',
  );
  $map->status = 1;
  $map->module = 'fundraiser_sustainers_upgrade';
  salesforce_genmap_save_map($map, 'webform');
}
