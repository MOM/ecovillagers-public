<?php

/**
 * @file
 * Admin settings screens and associated helper functions.
 */

/**
 * Admin settings form.
 */
function springboard_api_admin_settings($form, $form_state) {
  $available_services = springboard_api_list_management_services();
  $options = array_merge(array('0' => t('- select -')), $available_services);
  $form['springboard_api_management_service'] = array(
    '#type' => 'select',
    '#title' => t('API Management Service'),
    '#description' => t('Select which API management service you would like to use.'),
    '#options' => $options,
    '#default_value' => variable_get('springboard_api_management_service', 0),
  );
  // TODO: link to http://enable-cors.org/
  $form['cors'] = array(
    '#type' => 'fieldset',
    '#title' => t('CORS settings'),
    '#description' => t('Certain API client applications may need to POST data cross-domain. To accomplish this !link. If your site administrator is unable to enable CORS on the server due to access restrictions, enabling it here may work.', array('!link' => l(t('CORS must be enabled'), 'http://enable-cors.org/'))),
  );
  $form['cors']['springboard_api_enable_cors'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable CORS'),
    '#return_value' => TRUE,
    '#default_value' => variable_get('springboard_api_enable_cors', FALSE),
  );
  // Additional plugin-specific settings.
  $plugins = springboard_api_get_available_plugins();
  foreach ($plugins as $plugin) {
    if (isset($plugin['admin_settings']) && function_exists($plugin['admin_settings'])) {
      $func = $plugin['admin_settings'];
      $func($form, $form_state);
    }
  }
  return system_settings_form($form);
}
