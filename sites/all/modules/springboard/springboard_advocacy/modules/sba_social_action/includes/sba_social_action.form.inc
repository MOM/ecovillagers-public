<?php

/**
 * @file
 * Helper functions for building social action client forms.
 */

/**
 * Social action webform alterations.
 *
 * Add the message entities to the action webform node view
 * and message preview page.
 * Attach CSS and JS to Action nodes.
 * Define custom submit and validate hooks.
 *
 * @param $form
 * @param $form_state
 */
function sba_social_action_additional_elements(&$form, &$form_state) {
  // Override core's theme_form in order to remove <form> tag
  // and use it in a template variable defined in
  // sba_social_action_build_preprocess and
  // theme_social_action_form_layout_form
  if (!empty($form['#theme_wrappers']) && !empty($form['#node']->form_layouts) && $form['#node']->form_layouts != 'one_column') {
    foreach ($form['#theme_wrappers'] as $key => $wrapper) {
      if ($wrapper == 'form') {
        unset($form['#theme_wrappers'][$key]);
      }
    }
    $form['#theme_wrappers'][] = array('social_action_form_layout_form');
  }

  // Attach the JS and CSS.

  // Is form layouts enabled?
  if (!empty($form['#node']->form_layouts) && $form['#node']->form_layouts != 'one_column') {
    $form['#attached']['css'][] = drupal_get_path('module', 'sba_social_action')
      . '/css/social-action-form-layouts.css';
  }
  else {
    $form['#attached']['css'][] = drupal_get_path('module', 'sba_social_action')
      . '/css/social-no-form-layouts.css';
  }

  $form['smarty_geo'] = array(
    '#type' => 'value',
    '#value' => '',
  );

  $form['webform_flat'] = array(
    '#type' => 'value',
    '#value' => array(),
  );

  // Create a container on the form for all messages.
  $form['sba_messages'] = array(
    '#type' => 'container',
    '#tree' => TRUE,
    '#attributes' => array(
      'id' => array('sba-messages-form'),
    ),
    '#weight' => -10

  );


  $form['submitted']['multiflow'] = array(
    '#type' => 'fieldset',
    '#title' => t('Step 1 of 2'),
    '#attributes' => array('class' => array('sba-message')),
    '#weight' => -100

  );

  // Create a set of fields for each message assigned to the form.
  $districted = FALSE;
  foreach ($form['#node']->messages as $message) {
    sba_social_action_message_form($form['sba_messages'], $message, $message->type, $districted);
  }
  // value of districted can change after being passed by reference above.
  if ($districted == FALSE) {
    // Hide the address fields. Use webform user to find them.
    $node = $form['#node'];
    $components = $node->webform['components'];
    $component_hierarchy = webform_user_parse_components($node->nid, $components);
    $sbp_address = &_webform_user_find_field($form, $component_hierarchy['sbp_address']);
    $sbp_address_line_2 = &_webform_user_find_field($form, $component_hierarchy['sbp_address_line_2']);
    $sbp_city = &_webform_user_find_field($form, $component_hierarchy['sbp_city']);
    $sbp_state = &_webform_user_find_field($form, $component_hierarchy['sbp_state']);
    $sbp_zip = &_webform_user_find_field($form, $component_hierarchy['sbp_zip']);
    $sbp_address['#access'] = FALSE;
    $sbp_address_line_2['#access'] = FALSE;
    $sbp_city['#access'] = FALSE;
    $sbp_state['#access'] = FALSE;
    $sbp_zip['#access'] = FALSE;
  }

  $form['districted'] = array(
    '#type' => 'value',
    '#value' => $districted,
  );

  $form['#validate'][] = 'sba_social_action_form_validate';
  array_unshift($form['#submit'], 'sba_social_action_form_submit');
}

/**
 * Build a form to represent each message attached to the action webform node.
 *
 * @param array $form
 *   The webform client form.
 * @param object $message
 *   The message entity.
 * @param boo
 *    Whether this webform has multiple messages.
 */
function sba_social_action_message_form(&$form, $message, $message_entity_type, &$districted = NULL) {
  // Get some message values via an entity wrapper.
  $wrapper = entity_metadata_wrapper('sba_message', $message);
  $message_body = $alternate_options = $description = '';
  $message_editable = $required_message = $prepend = FALSE;

  if ($message_entity_type == 'sba_social_action_twitter_message') {
    $first_tweet = !empty($wrapper->field_sba_twitter_message->value()[0]) ? $wrapper->field_sba_twitter_message->value()[0] : '';
    $message_body = check_plain($first_tweet);
    $message_editable = $wrapper->field_sba_twitter_editable->value() == 'Not editable' ? FALSE : TRUE;
    $required_message = $wrapper->field_sba_twitter_editable->value() == 'Editing is required' ? TRUE : FALSE;
    $alternate_options = $wrapper->field_sba_show_additional->value();
    $prepend = $wrapper->field_sba_prepend_target_name->value();
    $description = 'You may customize this tweet. You have <span class="counter"></span> characters left.';
  }

  $preview_form = empty($form) ? TRUE : FALSE;
  $access = TRUE;
  if (!$preview_form) {
    $access = FALSE;
  }

  if($districted == FALSE) {
    $districted = empty($wrapper->field_sba_target_options->value()) ? FALSE : TRUE;
  }

  $form['message'][$message->sba_message_id] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('sba-message')),
  );

  $this_message =& $form['message'][$message->sba_message_id];

  $this_message['message_id'] = array(
    '#type' => 'value',
    '#value' => $message->data['message_id'],
  );

  $this_message['sba_message_id'] = array(
    '#type' => 'value',
    '#value' => $message->sba_message_id,
  );

  $this_message['sba_message_type'] = array(
    '#type' => 'value',
    '#value' => $message_entity_type,
  );

  $this_message['body'] = array(
    '#type' => 'value',
    '#value' => $message_body,
  );

  if ($preview_form) {
    $this_message['alternate_options'] = array(
      '#type' => 'value',
      '#value' => $alternate_options,
    );

    $this_message['prepend'] = array(
      '#type' => 'value',
      '#value' => $prepend,
    );

    if ($required_message) {
      $required = TRUE;
    }
    else {
      $required = FALSE;
    }

    if(!$message_editable) {
      $this_message['body_show'] = array(
        '#type' => 'item',
        '#title' => '',
        '#markup' => $message_body,
        '#access' => $access,
        '#prefix' => '<div class="uneditable-message-preview">',
        '#suffix' => '</div>'
      );
    }
    else {
      $this_message['edited_body'] = array(
        '#type' => 'textarea',
        '#default_value' => $message_body,
        '#description' => $description,
        '#required' => $required,
        '#access' => $access,
        '#rows' => 2
      );
    }
  }

  $this_message['body_required'] = array(
    '#type' => 'value',
    '#value' => $required_message,
  );
}


/**
 * Validation handler for social action forms.
 *
 * Checks whether editing of subject or body is required.
 * Calls Smarty Streets API and injects response values into form state.
 * Flattens the webform submission tree and injects flattened values into
 * form state for use by the message sending functions
 * in sba_social_action.webform.inc
 *
 * @param $form
 * @param $form_state
 */
function sba_social_action_form_validate(&$form, &$form_state) {
  $components = $form['#node']->webform['components'];
  $component_hierarchy = webform_user_parse_components($form['#node']->nid, $components);
  $form['#hierarchy'] = $component_hierarchy;
  form_load_include($form_state, 'inc', 'springboard_advocacy', 'includes/springboard_advocacy.smarty_streets');
  $webform_values_flat = _springboard_advocacy_webform_submission_flatten($form['#node']->nid, $form_state['values']['submitted']);
  form_set_value($form['webform_flat'], $webform_values_flat, $form_state);

  // If the message is not districted, we'll skip the smarty lookup
  // and substitute bogus values in sba_social_action_build_contact().
  if (!empty($form_state['values']['districted'])) {
    $form_error = &drupal_static('form_set_error');
    if (empty($form_error)) {
      $smarty_geo = springboard_advocacy_smarty_lookup($webform_values_flat);
      if (!empty($smarty_geo) && is_array($smarty_geo)) {
        form_set_value($form['smarty_geo'], $smarty_geo, $form_state);
        if (isset($smarty_geo['zip']) && isset($smarty_geo['plus4'])) {
          $zip_plus_four = &_webform_user_find_field($form, $component_hierarchy['sbp_zip_plus_four']);
          form_set_value($zip_plus_four, $smarty_geo['zip'] . '-' . $smarty_geo['plus4'], $form_state);
        }
      }
      else {
        form_set_error('', t('We could not verify your address. Please check that the street, city, state and zip code information is correct.'));
      }
    }
  }
}

/**
 * Submit handler for social action forms.
 *
 * Capture all messages, combine with contact information and
 * submit to API.
 *
 * @param $form
 * @param $form_state
 */
function sba_social_action_form_submit($form, &$form_state) {

  $_SESSION['deliverable_social_messages'] = array();
  $_SESSION['undeliverable_social_messages'] = array();
  $_SESSION['social_contact'] = array();
  $_SESSION['social_form_details'] = array();
  $_SESSION['social_action_sid'] = FALSE;
  $_SESSION['social_action_completed'] = FALSE;

  $account =  new stdClass();
  if (empty($form_state['values']['districted'])) {
    $account = user_load_by_mail($form_state['values']['submitted']['mail']);
  }

  // Create array of messages to submit for target resolution.
  // Retrieve target social URLs from the response.
  if (isset($form_state['values']['sba_messages'])) {
    $messages = array();
    foreach ($form_state['values']['sba_messages']['message'] as $id => $message) {
      $edited_body = isset($message['edited_body']) ? $message['edited_body'] : '';
      $messages[$id]['body'] = sba_social_action_build_message_bodies($message['sba_message_id'], $message['sba_message_type'], $edited_body);
      //$messages[$id]['subject'] = $message['subject'];
    }
    form_load_include($form_state, 'inc', 'sba_social_action', 'includes/sba_social_action.webform');
    $data = sba_social_action_send_message($messages, $form_state, $account);

    // Calculate the deliverable count for sending to salesforce
    if (!empty($data->messages)) {
      $deliverable = 0;
      foreach ($data->messages as $key => $message) {
        $deliverable += count($message->deliverable);
      }
      $component_hierarchy = $form['#hierarchy'];
      if (isset($component_hierarchy['sba_deliverable_count'])) {
        $sba_deliverable_count = &_webform_user_find_field($form, $component_hierarchy['sba_deliverable_count']);
        form_set_value($sba_deliverable_count, $deliverable, $form_state);
      }
    }
  }
  else {
    drupal_set_message(t('No messages were configured for this action.'));
  }
}


/**
 * Helper function to build message bodies.
 *
 * Combines user edited message data with other static properties
 * to create the final message to deliver to the transaction server.
 *
 * @param int $sba_message_id
 *   The message ID.
 * @param string $message_editable
 *    The user-editable body.
 *
 * @return string
 *   The message in string format.
 */
function sba_social_action_build_message_bodies($sba_message_id, $type, $message_editable) {
  // Load the message entity using the message entity id. We'll use the entity
  // to construct the full message.
  $message = entity_load('sba_message', array($sba_message_id));
  $message = array_shift($message);
  $wrapper = entity_metadata_wrapper('sba_message', $message);
  $user_message = array();
  if ($type == 'sba_social_action_twitter_message') {
    $first_tweet = !empty($wrapper->field_sba_twitter_message->value()[0]) ? $wrapper->field_sba_twitter_message->value()[0] : '';
    if (empty($message_editable)) {
      $user_message[] = $first_tweet;
    }
    else {
      $user_message[] = $message_editable;
    }
  }
  $user_message = implode("\n\n", array_filter($user_message));

  return $user_message;
}
