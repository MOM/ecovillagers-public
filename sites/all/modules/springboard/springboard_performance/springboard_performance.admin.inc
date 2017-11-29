<?php

/**
 * @file
 * Admin functions and callbacks for springboard_performance module.
 */


/**
 * Form callback for admin settings form.
 */
function springboard_performance_admin_settings_form() {
  $form = array();

  $form['springboard_performance_disable_field_cache'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable field cache'),
    '#description' => t('Disable storing field values in cache_field.'),
    '#default_value' => variable_get('springboard_performance_disable_field_cache', TRUE),
  );
  $form['springboard_performance_disable_commerce_order_locking'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable commerce_order locking'),
    '#description' => t('Disable commerce_order pessimistic locking. See !url for more information.',
      array('!url' => l(t('this d.o thread'), 'https://www.drupal.org/node/2240427#comment-11399745'))),
    '#default_value' => variable_get('springboard_performance_disable_commerce_order_locking', FALSE),
  );

  return system_settings_form($form);
}
