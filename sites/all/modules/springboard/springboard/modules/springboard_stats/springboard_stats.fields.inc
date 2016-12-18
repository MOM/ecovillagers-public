<?php
/**
 * @file
 * springboard_stats.fields.inc
 */

/**
 * Add stats fields to a webform node type.
 *
 * @param $type String
 *    The node type
 * @param $fundraiser_specific Boolean
 *    True if fundraiser-specific stats fields should be added. False if fields generic to all webform types should be.
 */
function _springboard_stats_add_default_fields($type, $fundraiser_specific = FALSE) {
  module_load_include('inc', 'field', 'field.crud');
  module_load_include('inc', 'field', 'field.info');
  
  $fields = $fundraiser_specific ? _springboard_stats_fundraiser_fields_settings($type) : _springboard_stats_webform_fields_settings($type);
  foreach ($fields as $field_name => $field) {
    // If the field doesn't exist create it.
    if (!field_info_field($field_name)) {
      field_create_field($field['field_config']);
    }
    // Before adding the field, check that it doesn't exist on the node type.
    if (!field_info_instance('node', $field_name, $type)) {
      field_create_instance($field['field_instance']);
    }
  }
}

/**
 * Returns an array of field configurations
 *
 * @param $type String
 *    The type of node these fields will be added to, used to populate the bundle property
 */
function _springboard_stats_webform_fields_settings($type) {
  $fields = array();
  $t = get_t();
  
  // Total Number of Submissions
  $fields['sbstats_count_submissions'] = array(
    'field_config' => array(
      'type' => 'number_integer',
      'cardinality' => 1,
      'locked' => TRUE,
      'settings' => array(
        'min' => '0',
      ),
      'entity_types' => array(),
      'field_name' => 'sbstats_count_submissions',
      'foreign keys' => array(),
      'indexes' => array(),
      'translatable' => FALSE,
    ),
    'field_instance' => array(
      'bundle' => $type,
      'default_value' => 0,
      'description' => $t('The total number of submissions received per form.'),
      'display' => array(
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '2',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'sbstats_count_submissions',
      'label' => $t('Total Number of Submissions'),
      'required' => FALSE,
      'settings' => array(
        'text_processing' => FALSE,
        'user_register_form' => FALSE,
      ),
/*      'widget' => array(
 *        'active' => 1,
 *        'module' => 'text',
 *        'settings' => array(
 *          'size' => '60',
 *        ),
 *        'type' => 'text_textfield',
 *        'weight' => '0',
 *      ),
 */
    ),
  );

  return $fields;
}

/**
 * Returns an array of field configurations
 *
 * @param $type String
 *    The type of node these fields will be added to, used to populate the bundle property
 */
function _springboard_stats_fundraiser_fields_settings($type) {
  $fields = array();
  $t = get_t();
  
  // Dollar Total of Transactions
  $fields['sbstats_total_transactions'] = array(
    'field_config' => array(
      'type' => 'number_decimal',
      'cardinality' => 1,
      'locked' => TRUE,
      'settings' => array(
        'precision' => 10,
        'scale' => 2,
      ),
      'entity_types' => array(),
      'field_name' => 'sbstats_total_transactions',
      'foreign keys' => array(),
      'indexes' => array(),
      'translatable' => FALSE,
    ),
    'field_instance' => array(
      'bundle' => $type,
      'default_value' => 0.0,
      'description' => $t('The dollar total of all payment-received donations per form.'),
      'display' => array(
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
//          'weight' => '2',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
//          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'sbstats_total_transactions',
      'label' => $t('Dollar Total of Transactions'),
      'required' => FALSE,
      'settings' => array(
        'text_processing' => FALSE,
        'user_register_form' => FALSE,
      ),
/*      'widget' => array(
 *        'active' => 1,
 *        'module' => 'text',
 *        'settings' => array(
 *          'size' => '60',
 *        ),
 *        'type' => 'text_textfield',
 *        'weight' => '0',
 *      ),
 */
    ),
  );

  // Total Number of Conversions
  $fields['sbstats_count_conversions'] = array(
    'field_config' => array(
      'type' => 'number_integer',
      'cardinality' => 1,
      'locked' => TRUE,
      'settings' => array(
        'min' => '0',
      ),
      'entity_types' => array(),
      'field_name' => 'sbstats_count_conversions',
      'foreign keys' => array(),
      'indexes' => array(),
      'translatable' => FALSE,
    ),
    'field_instance' => array(
      'bundle' => $type,
      'default_value' => 0,
      'description' => $t('The total number of successful donations received per form.'),
      'display' => array(
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'sbstats_count_conversions',
      'label' => $t('Total Number of Conversions'),
      'required' => FALSE,
      'settings' => array(
        'text_processing' => FALSE,
        'user_register_form' => FALSE,
      ),
    ),
  );

  // Total Number of Sustainers Payments
  $fields['sbstats_count_sustainers'] = array(
    'field_config' => array(
      'type' => 'number_integer',
      'cardinality' => 1,
      'locked' => TRUE,
      'settings' => array(
        'min' => '0',
      ),
      'entity_types' => array(),
      'field_name' => 'sbstats_count_sustainers',
      'foreign keys' => array(),
      'indexes' => array(),
      'translatable' => FALSE,
    ),
    'field_instance' => array(
      'bundle' => $type,
      'default_value' => 0,
      'description' => $t('The total number of successful recurring-donation payments received per form.'),
      'display' => array(
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'sbstats_count_sustainers',
      'label' => $t('Total Number of Sustainers Payments'),
      'required' => FALSE,
      'settings' => array(
        'text_processing' => FALSE,
        'user_register_form' => FALSE,
      ),
    ),
  );

  // Dollar Total of Sustainers Payments
  $fields['sbstats_total_sustainers'] = array(
    'field_config' => array(
      'type' => 'number_decimal',
      'cardinality' => 1,
      'locked' => TRUE,
      'settings' => array(
        'precision' => 10,
        'scale' => 2,
      ),
      'entity_types' => array(),
      'field_name' => 'sbstats_total_sustainers',
      'foreign keys' => array(),
      'indexes' => array(),
      'translatable' => FALSE,
    ),
    'field_instance' => array(
      'bundle' => $type,
      'default_value' => 0,
      'description' => $t('The dollar total of successful recurring-donation payments received per form.'),
      'display' => array(
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'sbstats_total_sustainers',
      'label' => $t('Dollar Total of Sustainers Payments'),
      'required' => FALSE,
      'settings' => array(
        'text_processing' => FALSE,
        'user_register_form' => FALSE,
      ),
    ),
  );

  // Total Number of Failures
  $fields['sbstats_count_failures'] = array(
    'field_config' => array(
      'type' => 'number_integer',
      'cardinality' => 1,
      'locked' => TRUE,
      'settings' => array(
        'min' => '0',
      ),
      'entity_types' => array(),
      'field_name' => 'sbstats_count_failures',
      'foreign keys' => array(),
      'indexes' => array(),
      'translatable' => FALSE,
    ),
    'field_instance' => array(
      'bundle' => $type,
      'default_value' => 0,
      'description' => $t('The total number of payment-failed donations submitted per form.'),
      'display' => array(
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'sbstats_count_failures',
      'label' => $t('Total Number of Failures'),
      'required' => FALSE,
      'settings' => array(
        'text_processing' => FALSE,
        'user_register_form' => FALSE,
      ),
    ),
  );

  // Dollar Total of Failures
  $fields['sbstats_total_failures'] = array(
    'field_config' => array(
      'type' => 'number_decimal',
      'cardinality' => 1,
      'locked' => TRUE,
      'settings' => array(
        'precision' => 10,
        'scale' => 2,
      ),
      'entity_types' => array(),
      'field_name' => 'sbstats_total_failures',
      'foreign keys' => array(),
      'indexes' => array(),
      'translatable' => FALSE,
    ),
    'field_instance' => array(
      'bundle' => $type,
      'default_value' => 0,
      'description' => $t('The dollar total of failed donation payments per form.'),
      'display' => array(
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'sbstats_total_failures',
      'label' => $t('Dollar Total of Failures'),
      'required' => FALSE,
      'settings' => array(
        'text_processing' => FALSE,
        'user_register_form' => FALSE,
      ),
    ),
  );

  // Total Number of Transactions Pending
  $fields['sbstats_count_pending'] = array(
    'field_config' => array(
      'type' => 'number_integer',
      'cardinality' => 1,
      'locked' => TRUE,
      'settings' => array(
        'min' => '0',
      ),
      'entity_types' => array(),
      'field_name' => 'sbstats_count_pending',
      'foreign keys' => array(),
      'indexes' => array(),
      'translatable' => FALSE,
    ),
    'field_instance' => array(
      'bundle' => $type,
      'default_value' => 0,
      'description' => $t('The total number of donations pending payment receipt per form.'),
      'display' => array(
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'sbstats_count_pending',
      'label' => $t('Total Number of Transactions Pending'),
      'required' => FALSE,
      'settings' => array(
        'text_processing' => FALSE,
        'user_register_form' => FALSE,
      ),
    ),
  );

  // Dollar Total of Transactions Pending
  $fields['sbstats_total_pending'] = array(
    'field_config' => array(
      'type' => 'number_decimal',
      'cardinality' => 1,
      'locked' => TRUE,
      'settings' => array(
        'precision' => 10,
        'scale' => 2,
      ),
      'entity_types' => array(),
      'field_name' => 'sbstats_total_pending',
      'foreign keys' => array(),
      'indexes' => array(),
      'translatable' => FALSE,
    ),
    'field_instance' => array(
      'bundle' => $type,
      'default_value' => 0,
      'description' => $t('The dollar total of donations payments pending per form.'),
      'display' => array(
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'sbstats_total_pending',
      'label' => $t('Dollar Total of Transactions Pending'),
      'required' => FALSE,
      'settings' => array(
        'text_processing' => FALSE,
        'user_register_form' => FALSE,
      ),
    ),
  );

  // Total Number of Refunds
  $fields['sbstats_count_refunds'] = array(
    'field_config' => array(
      'type' => 'number_integer',
      'cardinality' => 1,
      'locked' => TRUE,
      'settings' => array(
        'min' => '0',
      ),
      'entity_types' => array(),
      'field_name' => 'sbstats_count_refunds',
      'foreign keys' => array(),
      'indexes' => array(),
      'translatable' => FALSE,
    ),
    'field_instance' => array(
      'bundle' => $type,
      'default_value' => 0,
      'description' => $t('The total number of refunds processed per form.'),
      'display' => array(
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'sbstats_count_refunds',
      'label' => $t('Total Number of Refunds'),
      'required' => FALSE,
      'settings' => array(
        'text_processing' => FALSE,
        'user_register_form' => FALSE,
      ),
    ),
  );

  // Dollar Total of Refunds
  $fields['sbstats_total_refunds'] = array(
    'field_config' => array(
      'type' => 'number_decimal',
      'cardinality' => 1,
      'locked' => TRUE,
      'settings' => array(
        'precision' => 10,
        'scale' => 2,
      ),
      'entity_types' => array(),
      'field_name' => 'sbstats_total_refunds',
      'foreign keys' => array(),
      'indexes' => array(),
      'translatable' => FALSE,
    ),
    'field_instance' => array(
      'bundle' => $type,
      'default_value' => 0,
      'description' => $t('The dollar total of refunds processed per form.'),
      'display' => array(
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'sbstats_total_refunds',
      'label' => $t('Dollar Total of Refunds'),
      'required' => FALSE,
      'settings' => array(
        'text_processing' => FALSE,
        'user_register_form' => FALSE,
      ),
    ),
  );

  return $fields;
}
