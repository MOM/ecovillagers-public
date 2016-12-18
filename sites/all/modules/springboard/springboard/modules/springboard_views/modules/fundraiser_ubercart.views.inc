<?php
/**
 * @file
 * Provides views table data for fundraiser related tables.
 */

/**
 * Implements hook_views_data().
 */
function springboard_views_fundraiser_ubercart_views_data() {
  $data = array();
  $data['fundraiser_donation']['did'] = array(
    'title' => t('Donation order'),
    'help' => t('Ubercart order related to a donation.'),
    'relationship' => array(
      'base' => 'uc_orders',
      'base field' => 'order_id',
      'handler' => 'views_handler_relationship',
      'label' => t('Donation order'),
    ),
  );
  /**
   * Ubercart has already defined it's fieldset so we just add the relationship.
   */
  return $data;
}
