<?php

/**
 * @file
 * Defines default tax components and rules.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_cybersource_default_rules_configuration() {
  $rules = array();

  // Create a new product pricing rule.
  $rule = rules_reaction_rule();

  $rule->label = t('Calculate taxes via CyberSource');
  $rule->active = TRUE;

  // Add the action to calculate taxes for the line item via CyberSource.
  $rule
    ->event('commerce_product_calculate_sell_price')
    ->condition(rules_condition('data_is', array(
      'data:select' => 'commerce-line-item:order:state',
      'op' => '==',
      'value' => 'cart',
    ))->negate())
    ->condition('commerce_order_is_cart', array(
      'commerce_order:select' => 'commerce-line-item:order',
    ))
    ->action('commerce_cybersource_calculate_line_item_taxes', array(
        'commerce_line_item:select' => 'commerce-line-item',
        'instance_id' => 'cybersource_soap_cc|commerce_payment_cybersource_soap_cc',
      ));

  $rules['commerce_cybersource_calculate_taxes'] = $rule;

  return $rules;
}
