<?php

/**
 * @file
 * Rules integration for CyberSource tax calculation.
 *
 * @addtogroup rules
 * @{
 */


/**
 * Implements hook_rules_action_info().
 */
function commerce_cybersource_rules_action_info() {
  $actions = array();

  $actions['commerce_cybersource_calculate_line_item_taxes'] = array(
    'label' => t('Calculate taxes via CyberSource'),
    'parameter' => array(
      'commerce_line_item' => array(
        'type' => 'commerce_line_item',
        'label' => t('Line item'),
      ),
      'instance_id' => array(
        'type' => 'text',
        'label' => t('CyberSource instance'),
        'help' => t('Select the payment method instance you have created to enable CyberSource with tax calculation on your site.'),
        'options list' => 'commerce_cybersource_instance_options_list',
      ),
    ),
    'group' => t('Commerce CyberSource'),
  );

  return $actions;
}

/**
 * Options list callback: returns an array of CyberSource instances keyed by
 * payment method instance ID.
 */
function commerce_cybersource_instance_options_list() {
  $event = rules_get_cache('event_commerce_payment_methods');

  // Build an options array of all CyberSource payment methods instances.
  $options = array();

  // Only build the options array if payment method Rules are enabled.
  if (!empty($event)) {
    $method_id = 'cybersource_soap_cc';

    // Look for a Rule enabling this payment method.
    foreach ($event->getIterator() as $rule) {
      foreach ($rule->actions() as $action) {
        // If an action is found, add its instance to the options array.
        if ($action->getElementName() == 'commerce_payment_enable_' . $method_id) {
          $instance_id = commerce_payment_method_instance_id($method_id, $rule);

          $options[$instance_id] = check_plain($rule->label());
        }
      }
    }
  }

  return $options;
}

/**
 * @}
 */
