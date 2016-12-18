<?php

/**
 * @file
 */

/**
 * Admin settings form for Webform Confirmation Alias.
 *
 * Provides interface to bulk add aliases to existing webforms.
 * Also, allows site admins to set the confirmation 'append' text, site-wide.
 */
function webform_confirmation_alias_admin_settings() {
  global $base_url;
  
  // Display warning message letting the admin know that forms must be aliased for this to work.
  $options = array(
    'attributes' => array(
      'target' => '_blank',
    ),
  );
  $message = t('These settings will only affect forms that have URL aliases. See information on !drupalorg and !pathauto for more information.', array(
    '!drupalorg' => l('Drupal.org', 'https://drupal.org/node/120631', $options),
    '!pathauto' => l('the Pathauto module', 'https://drupal.org/project/pathauto', $options)
  ));
  drupal_set_message($message, 'warning');
  
  // Now generate the form.
  $form['generate_aliases'] = array(
    '#type' => 'fieldset',
    '#title' => t('Bulk Generate Aliases'),
    '#description' => '<p>' . t('This module generates url "aliases" for webform confirmation URLs. Only forms with the default "confirmation page" setting will be affected 
      by this module. <br />Click on the button below to generate aliases for all existing forms or to update all forms if you changed the text in the field below.') . '</p>',
  );
    $form['generate_aliases']['generate'] = array(
      '#type' => 'submit',
      '#value' => t('Bulk Generate'),
      '#submit' => array('webform_confirmation_alias_bulk_generate_aliases'),
    );
  
  $form['general_module_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('URL Alias settings'),
  );
    $form['general_module_settings']['webform_confirmation_alias_append'] = array(
      '#attributes' => array('class' => array('format-numeric')),
      '#required' => TRUE,
      '#size' => 40,
      '#type' => 'textfield',
      '#title' => t('Text to Append to Create the Confirmation URL'),
      '#description' => 'Enter the text to append to the form URL when generating the confirmation URL (e.g. "thank-you" or "success").<br />For example, if you choose "success", a form whose URL is "' . $base_url . '/donate" will have the confirmation URL of "' . $base_url . '/donate/thank-you".',
      '#default_value' => variable_get('webform_confirmation_alias_append', 'thank-you'),
    );
    $form['general_module_settings']['webform_confirmation_alias_bulkupdate'] = array(
      '#attributes' => array('class' => array('format-numeric')),
      '#required' => FALSE,
      '#type' => 'checkbox',
      '#title' => t('Update confirmation aliases for all existing forms?'),
      '#default_value' => 0,
      '#description' => 'Checking this box will activate the "Bulk Generate" function. If you leave this unchecked, your changes will only affect future forms.',
    );
    
    // Second submit handler to check whether we should bulk generate aliases.
    $form['#submit'][] = 'webform_confirmation_alias_second_submitter';

  return system_settings_form($form);
}

/**
 * Second submit handler for confirmation form above.
 * If 'update confirmation aliases' checkbox is checked,
 * it will run the 'Bulk Generate' function.
 */
function webform_confirmation_alias_second_submitter($form, &$form_state) {
  if ($form_state['values']['webform_confirmation_alias_bulkupdate'] == 1) {
    webform_confirmation_alias_bulk_generate_aliases($form, $form_state, $form_state['values']['webform_confirmation_alias_append']);
  }
}

/**
 * Bulk-add url aliases for webform confirmation redirect urls.
 * Called from 'Bulk Generate' button above, as well as the alternate submit handler for the same form.
 * Gets list of webforms that need url aliases for confirmation pages.
 *
 * Procedure: 
 * We're going to query to find all webforms that have <confirmation> as the redirect_url.
 * JOIN to find their alias. We'll use that alias later when we're 
 * inserting/updating the confirmation aliases.
 * Then, we'll add or update each alias, as appropriate.
 */
function webform_confirmation_alias_bulk_generate_aliases($form, $form_state, $confirmation_alias_append = NULL) {
  $count = 0;
    
  // If $confirmation_alias_append wasn't passed in, get its value here.
  if (!isset($confirmation_alias_append)) {
    $confirmation_alias_append = variable_get('webform_confirmation_alias_append', 'thank-you');
  }
  
  $query = db_select('webform', 'w');
  $query->join('url_alias', 'u', 'CONCAT(\'node/\', w.nid) = u.source');
  $query->fields('w', array('nid', 'redirect_url'));
  $query->fields('u', array('source', 'alias'));
  $query->condition('w.redirect_url', '<confirmation>', '=');
  $get_webforms = $query->execute();  
  foreach($get_webforms as $webform) {    
    $count++;
    
    // Now find any existing confirmation aliases. If we find one ($result_count > 0), 
    // update it. If not, insert it.
    if (webform_confirmation_alias_exists($webform->nid) >= 1) {
	    webform_confirmation_alias_update($webform->nid, $webform->alias, $confirmation_alias_append, FALSE);
    } else {
      webform_confirmation_alias_add($webform->nid, $webform->alias, $confirmation_alias_append, FALSE);
    }
  }
  drupal_set_message(t('Added or updated ' . $count . ' confirmation URL aliases.'));
}
