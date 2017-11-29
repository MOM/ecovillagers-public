<?php
/**
 * @file
 * Provides views table data for fundraiser related tables.
 */

/**
 * Implements hook_views_data().
 */
function springboard_views_fundraiser_views_data() {
  $data = array();
  /**
   * Fundraiser table metadata.
   */
  $data['fundraiser']['table'] = array(
    'group' => t('Fundraiser donation forms'),
    'join' => array(
      'node' => array(
        'left_field' => 'nid',
        'field' => 'nid',
      ),
    ),
    'base' => array(
      'field' => 'nid',
      'title' => t('Fundraiser donation forms'), 
      'help' => t('Contains Fundraiser-specific information for donation forms.'), 
      'weight' => -10,
    ),
  );
  
  $data['fundraiser']['nid'] = array(
    'title' => t('Fundraiser node'),
    'help' => t('Fundraiser node related to a form.'),
    'relationship' => array(
      'base' => 'node',
      'field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('Fundraiser node'),
    ), 
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  
  $data['fundraiser']['gateways'] = array(
    'title' => t('Gateway'),
    'help' => t('The payment gateway the donation form uses to process credit cards.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'fundraiser_handler_filter_fundraiser_gateways',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['fundraiser']['receipt_email_from'] = array(
    'title' => t('Receipt email from'),
    'help' => t('The name that will appear in the from line in the receipt email.'),
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
  );
  $data['fundraiser']['receipt_email_address'] = array(
    'title' => t('Receipt email address'),
    'help' => t('The from email address that will be used in the receipt email.'),
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
  );
  $data['fundraiser']['receipt_email_subject'] = array(
    'title' => t('Receipt email subject'),
    'help' => t('The subject line of the receipt email.'),
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
  );
  $data['fundraiser']['receipt_email_message'] = array(
    'title' => t('Receipt email message'),
    'help' => t('The message that will appear in the receipt email.'),
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
  );
  $data['fundraiser']['donation_amounts'] = array(
    'title' => t('Donation amounts'),
    'help' => t('Ask amounts to be displayed on the donation form.'),
    'field' => array(
      'handler' => 'fundraiser_handler_field_donation_amounts',
    ),
  );
  $data['fundraiser']['show_other_amount'] = array(
    'title' => t('Show other amount'),
    'help' => t('True or false, whether the donation form allows other amounts.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['fundraiser']['minimum_donation_amount'] = array(
    'title' => t('Minimum donation amount'),
    'help' => t('The minimum donation amount the donation form will accept.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  /**
   * Fundraiser_donation table metadata. Relationships to fundraiser node, and donationg user.
   */
  $data['fundraiser_donation']['table'] = array(
    'group' => t('Fundraiser donations'),
    'base' => array(
      'field' => 'did',
      'title' => t('Donations'),
      'help' => t('Donations made.'),
    ),
    'join' => array(
      'node' => array(
        'left_field' => 'nid',
        'field' => 'nid',
      ),
      'user' => array(
        'left_field' => 'uid',
        'field' => 'uid',
      ),
      'commerce_order' => array(
        'left_field' => 'did',
        'field' => 'order_id',
      ),
    ),
  );
  $data['fundraiser_donation']['did'] = array(
    'title' => t('Commerce order'),
    'help' => t('Commerce order related to the donation.'),
    'relationship' => array(
      'base' => 'commerce_order',
      'base field' => 'order_id',
      'handler' => 'views_handler_relationship',
      'label' => t('Commerce order'),
    ),
  );
  $data['fundraiser_donation']['nid'] = array(
    'title' => t('Fundraiser node'),
    'help' => t('Fundraiser node related to a donation.'),
    'relationship' => array(
      'base' => 'node',
      'field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('Fundraiser node'),
    ), 
  );

  // Webform submission.
  $data['fundraiser_donation']['sid'] = array(
    'title' => t('Webform Submission'),
    'help' => t('Webform submission related to a donation.'),
    'relationship' => array(
      'base' => 'webform_submissions',
      'base field' => 'sid',
      'handler' => 'views_handler_relationship',
      'label' => t('Webform Submission'),
    ),
  );

  $data['fundraiser_donation']['uid'] = array(
    'title' => t('Donating user'),
    'help' => t('Donating user related to a donation.'),
    'relationship' => array(
      'base' => 'users',
      'base field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('Donating user'),
    ),
  );
  $data['fundraiser_donation']['status'] = array(
    'title' => t('Status'),
    'help' => t('Donation status.'),
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
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['fundraiser_donation']['amount'] = array(
    'title' => t('Donation amount'),
    'help' => t('The amount donated.'),
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
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['fundraiser_donation']['currency'] = array(
    'title' => t('Currency'),
    'help' => t('Donation currency type.'),
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
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['fundraiser_donation']['gateway'] = array(
    'title' => t('Gateway'),
    'help' => t('The payment gateway used on this donation.'),
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
  );
  $data['fundraiser_donation']['txn_id'] = array(
    'title' => t('Transaction ID'),
    'help' => t('The transaction ID used on this donation.'),
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
  );
  $data['fundraiser_donation']['form_url'] = array(
    'title' => t('Form URL'),
    'help' => t('The URL of the donation form.'),
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
  );
  $data['fundraiser_donation']['created'] = array(
    'title' => t('Created time'),
    'help' => t('The time that the donation was submitted.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  $data['fundraiser_donation']['changed'] = array(
    'title' => t('Changed time'),
    'help' => t('The time that the donation was last updated.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  $data['fundraiser_donation']['unique_id'] = array(
    'title' => t('Unique ID'),
    'help' => t('A unique value generated from current time and order_id.'),
    'field' => array(
      'handler' => 'springboard_views_views_handler_field',
    ),
  );
  $data['fundraiser_donation']['extra_props'] = array(
    'title' => t('Extra Props'),
    'help' => t('Field which returns a serialized array containing this donation\'s extra props.'),
    'field' => array(
      'handler' => 'springboard_views_views_handler_field',
    ),
  );

  /**
   * Fundraiser_tracking table metadata. Left joined to the charged back donation.
   */
  $data['fundraiser_refund']['table'] = array(
    'group' => t('Fundraiser refunds'),
    'join' => array(
      'donation' => array(
        'left_field' => 'did',
        'field' => 'refund_id',
      ),
    ),
  );
  $data['fundraiser_refund']['refund_id'] = array(
    'title' => t('Refund ID'),
    'help' => t('References a single refund.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['fundraiser_refund']['did'] = array(
    'title' => t('Receipt ID'),
    'help' => t('References a single refund receipt.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['fundraiser_refund']['amount'] = array(
    'title' => t('Refund amount'),
    'help' => t('Amount of a single refund.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['fundraiser_refund']['txn_id'] = array(
    'title' => t('Refund transaction ID'),
    'help' => t('The transaction ID of a single refund.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['fundraiser_refund']['reason'] = array(
    'title' => t('Refund reason'),
    'help' => t('The reason for a refund.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  /**
   * Fundraiser_tracking table metadata. Left joined to the tracked fundraiser node.
   */
  $data['fundraiser_tracking']['table'] = array(
    'group' => t('Fundraiser tracking'),
    'join' => array(
      'node' => array(
        'left_field' => 'nid',
        'field' => 'nid',
      ),
    ),
  );
  $data['fundraiser_tracking']['pageviews'] = array(
    'title' => t('Page views'),
    'help' => t('Number of times the donation form has been viewed.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['fundraiser_tracking']['conversions'] = array(
    'title' => t('Conversions'),
    'help' => t('Number of times the donation form has been submitted successfully.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['fundraiser_tracking']['local_failures'] = array(
    'title' => t('Local failures'),
    'help' => t('Number of times form submission has resulted in form_set_error().'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['fundraiser_tracking']['gateway_failures'] = array(
    'title' => t('Gateway failures'),
    'help' => t('Number of times submission has resulted in a failure reported by the payment gateway.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  return $data;
}
