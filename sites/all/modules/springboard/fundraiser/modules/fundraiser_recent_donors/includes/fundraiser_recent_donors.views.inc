<?php

/**
 * @file
 * Defines "Springboard Donations Opt In" Views.
 */

/**
 * Implements hook_views_data().
 */
function fundraiser_recent_donors_views_data() {
  $data['fundraiser_donor_opt_in']['table'] = array(
    'group' => t('Fundraiser'),
    'base' => array(
      'title' => t('Springboard Donations Opt In'),
      'help' => t('Displays donations from users who checked the opt-in box,') . ' ' .
        t('granting permission to display those donations.'),
    ),
    'join' => array(
      'node' => array(
        'left_field' => 'nid',
        'field' => 'nid',
      ),
      'webform_submissions' => array(
        'left_field' => 'sid',
        'field' => 'sid',
      ),
      'commerce_order' => array(
        'left_field' => 'did',
        'field' => 'did',
      ),
    ),
  );
  $data['fundraiser_donor_opt_in']['nid'] = array(
    'title' => t('Donation opt-in: node'),
    'help' => t('Node from which a donation was made.'),
    'relationship' => array(
      'base' => 'node',
      'base field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('Donation node'),
    ),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  $data['fundraiser_donor_opt_in']['sid'] = array(
    'title' => t('Donation opt-in: submission'),
    'help' => t('Webform submission associated with donation opt-in record.'),
    'relationship' => array(
      'base' => 'webform_submissions',
      'base field' => 'sid',
      'handler' => 'views_handler_relationship',
      'label' => t('Donation opt-in submission'),
    ),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  $data['fundraiser_donor_opt_in']['did'] = array(
    'title' => t('Donation opt-in: Commerce order ID'),
    'help' => t('Commerce order associated with donation opt-in record.'),
    'relationship' => array(
      'base' => 'commerce_order',
      'base field' => 'order_id',
      'handler' => 'views_handler_relationship',
      'label' => t('Donation opt-in commerce order'),
    ),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  $data['fundraiser_donor_opt_in']['created'] = array(
    'title' => t('Donation opt-in: Timestamp'),
    'help' => t('Timestamp when a donor opted in to having their donation displayed.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  return $data;
}
