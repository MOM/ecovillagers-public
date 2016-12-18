<?php

/**
 * @file
 * Helper functions for message action webform components.
 */

/**
 * Insert new components on node/add.
 *
 * Called from fundraiser_sustainers_upgrade_node_insert();
 *
 * @param $node
 */
function fundraiser_sustainers_upgrade_insert_components($node) {
  module_load_include('inc', 'webform', 'includes/webform.components');

  // Most of these fields are required for sending data to Salesforce.
  $fields[] = array(
    'nid' => $node->nid,
    'form_key' => 'fsu_uid',
    'pid' => 0,
    'name' => t('Fundraiser Sustainers Upgrade UID'),
    'type' => 'hidden',
    'value' => '',
    'weight' => 13,
    'email' => 1,
  );

  $fields[] = array(
    'nid' => $node->nid,
    'form_key' => 'fsu_did',
    'pid' => 0,
    'name' => t('Fundraiser Sustainers Upgrade Donation ID'),
    'type' => 'hidden',
    'value' => '',
    'weight' => 13,
    'email' => 1,
  );

  $fields[] = array(
    'nid' => $node->nid,
    'form_key' => 'fsu_amount',
    'pid' => 0,
    'name' => t('Fundraiser Sustainers Upgrade Amount'),
    'type' => 'hidden',
    'value' => '',
    'weight' => 13,
    'email' => 1,
  );

  $fields[] = array(
    'nid' => $node->nid,
    'form_key' => 'fsu_url',
    'pid' => 0,
    'name' => t('Fundraiser Sustainers Upgrade URL'),
    'type' => 'hidden',
    'value' => '',
    'weight' => 13,
    'email' => 1,
  );

  $fields[] = array(
    'nid' => $node->nid,
    'form_key' => 'fsu_timestamp',
    'pid' => 0,
    'name' => t('Fundraiser Sustainers Upgrade timestamp'),
    'type' => 'hidden',
    'value' => '',
    'weight' => 13,
    'email' => 1,
  );

  $fields[] = array(
    'nid' => $node->nid,
    'form_key' => 'fsu_nid',
    'pid' => 0,
    'name' => t('Fundraiser Sustainers Upgrade Node ID'),
    'type' => 'hidden',
    'value' => '',
    'weight' => 13,
    'email' => 1,
  );

  $fields[] = array(
    'nid' => $node->nid,
    'form_key' => 'fsu_status_flag',
    'pid' => 0,
    'name' => t('Fundraiser Sustainers Upgrade Status Flag'),
    'type' => 'hidden',
    'value' => '',
    'weight' => 13,
    'email' => 1,
  );

  // The email field is required so that confirmaiton emails have a target.
  $fields[] = array(
    'nid' => $node->nid,
    'form_key' => 'fsu_confirmation_email',
    'pid' => 0,
    'name' => t('Fundraiser Sustainers Confirmation Email Address'),
    'type' => 'hidden',
    'value' => '',
    'weight' => 13,
    'email' => 1,
  );

  $email_nid = variable_get('fundraiser_sustainers_upgrade_default_email_wrapper', NULL);
  if ($email_nid != NULL) {
    $email_node = node_load($email_nid);
  }

  $subject = !empty($email_node->email_wrapper_subject[LANGUAGE_NONE][0]['value']) ? $email_node->email_wrapper_subject[LANGUAGE_NONE][0]['value'] : 'default';
  $from = !empty($email_node->email_wrapper_from_name[LANGUAGE_NONE][0]['value']) ? $email_node->email_wrapper_from_name[LANGUAGE_NONE][0]['value'] : 'default';
  $address = !empty($email_node->email_wrapper_from_email[LANGUAGE_NONE][0]['value']) ? $email_node->email_wrapper_from_email[LANGUAGE_NONE][0]['value'] : 'default';
  $html = !empty($email_node->email_wrapper_html_message[LANGUAGE_NONE][0]['value']) ? $email_node->email_wrapper_html_message[LANGUAGE_NONE][0]['value'] : '';
  $text = !empty($email_node->email_wrapper_text_message[LANGUAGE_NONE][0]['value']) ? $email_node->email_wrapper_text_message[LANGUAGE_NONE][0]['value'] : '';

  // Add the components to the Webform.
  foreach ($fields as $field) {

    // Don't insert fields if cloning.
    if (!isset($node->clone_from_original_nid)) {
      $cid = webform_component_insert($field);

      // Set the email field as the webform_emails default.
      if ($field['form_key'] == 'fsu_confirmation_email') {
        $exists = db_query("SELECT nid FROM {webform_emails} WHERE nid = :nid AND eid = 1", array(':nid' => $node->nid))->fetchField();
        if (empty($exists)) {
          $record = array(
            'nid' => $node->nid,
            'eid' => 1,
            'email' => (string) $cid,
            'subject' => $subject,
            'from_name' => $from,
            'from_address' => $address,
            'excluded_components' => '',
            'template' => 'default',
          );
          drupal_write_record('webform_emails', $record);
        }
      }
    }
  }

  if (!isset($node->clone_from_original_nid)) {
    // Set up the default Email Wrapper for this node.
    if ($email_nid != NULL) {
      $settings = array(
        'nid' => $node->nid,
        'eid' => 1,
        'tid' => $email_nid,
        'bcc_email' => '',
        'html_message' => $html,
        'html_message_format' => 'filtered_html',
        'text_message' => $text,
        'extra' => serialize(array()),
      );
      email_wrappers_save_settings($node->nid, 1, $settings);
    }
  }
}

/**
 * Like it says, prevent deletion in the webform UI of these fields.
 *
 * Called from fundraiser_sustainers_upgrade_form_webform_component_delete_form_alter().
 *
 * @param $form
 * @param $form_state
 */
function fundraiser_sustainers_upgrade_prevent_component_delete(&$form, &$form_state) {

  $required_fields = fundraiser_sustainers_upgrade_locked_fields();
  $cid = $form['component']['#value']['cid'];
  $component = $form['node']['#value']->webform['components'][$cid];

  if (in_array($component['form_key'], $required_fields)) {
    $message = t('<strong>!name</strong> is a required field and cannot be deleted from this form.',
      array('!name' => $component['name']));
    $form['description']['#markup'] = $message;
    unset($form['actions']['submit']);
  }
}

/**
 * Implements hook_form_webform_components_form_alter().
 *
 * Disable un-mandatory of certain profile fields.
 */
function fundraiser_sustainers_upgrade_form_webform_components_form_alter(&$form, &$form_state, $form_id) {
  if ($form['#node']->type == 'fundraiser_sustainers_upgrade') {
    fundraiser_sustainers_upgrade_component_overview_lock($form);
  }
}

/**
 * Lock down edit forms.
 *
 * Called from fundraiser_sustainers_upgrade_form_webform_component_edit_form_alter().
 * @param $form
 */
function fundraiser_sustainers_upgrade_component_edit_lock(&$form) {
  $locked_fields = fundraiser_sustainers_upgrade_locked_fields();
  if (in_array($form['form_key']['#default_value'], $locked_fields)) {
    // Check the node type.
    $form['form_key']['#disabled'] = TRUE;
    $form['validation']['mandatory']['#disabled'] = TRUE;
  }
}

/**
 * Lock down editing on the overview form.
 * * Called from fundraiser_sustainers_upgrade_form_webform_components_form_alter().

 *
 * @param $form
 */
function fundraiser_sustainers_upgrade_component_overview_lock(&$form) {
  $locked_fields = fundraiser_sustainers_upgrade_locked_fields();
  foreach ($form['#node']->webform['components'] as $cid => $component) {
    if (in_array($component['form_key'], $locked_fields) && $component['form_key'] != 'sbp_phone') {
      $form['components'][$cid]['mandatory']['#disabled'] = TRUE;
    }
  }
}

/**
 * Locked fields helper.
 *
 * @return array
 */
function fundraiser_sustainers_upgrade_locked_fields() {
  $locked_fields = array(
    'fsu_did',
    'fsu_uid',
    'fsu_amount',
    'fsu_url',
    'fsu_nid',
    'fsu_timestamp',
    'fsu_status_flag',
    'fsu_confirmation_email',
  );
  return $locked_fields;
}

/**
 * Implements hook_form_FORMID_alter().
 *
 * Disable deletion of required advocacy webform fields.
 */
function fundraiser_sustainers_upgrade_form_webform_component_delete_form_alter(&$form, &$form_state, $form_id) {
  if ($form['node']['#value']->type == 'sustainers_upgrade_form') {
    fundraiser_sustainers_upgrade_prevent_component_delete($form, $form_state);
  }
}

/**
 * Implements hook_form_webform_component_edit_form_alter().
 *
 * Disable form-key editing and un-mandatory of certain profile fields.
 */
function fundraiser_sustainers_upgrade_form_webform_component_edit_form_alter(&$form, &$form_state, $form_id) {
  $node = node_load($form['nid']['#value']);
  if ($node->type == 'sustainers_upgrade_form') {
    fundraiser_sustainers_upgrade_component_edit_lock($form);
  }
}
