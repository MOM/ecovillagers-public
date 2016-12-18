<?php

/**
 * @file
 * Administration page callbacks for the salesforce namespace module.
 */

/**
 * Page callback for the admin form.
 */
function salesforce_namespace_settings() {
  $form['salesforce_namespace_namespace'] = array(
    '#title' => t('Namespace to use for this site'),
    '#type' => 'textfield',
    '#description' => t('The value entered here will be appended to the value
      of all external id fields when an object is exported. This will prevent
      id collisions when more than one site is connected to the same org. Once
      this is set it should not be changed.'),
    '#default_value' => variable_get('salesforce_namespace_namespace', '0001'),
    '#size' => 10,
    '#maxlength' => 10,
  );

  return system_settings_form($form);
}
