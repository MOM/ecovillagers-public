<?php

/**
 * Gets Zip+4 from Smarty streets.
 *
 * Builds a user contact array with zip, county and lat/long.
 * Gets the messages associated with the webform and prepares them for sending
 * to the API.
 * Merges the contact, messages, and form_id and sends to the target resolver.
 *
 * @param array $user_message
 *    Message submitted by the user.
 * @param array $form_state
 *   The submitted form state.
 */
function sba_social_action_send_message(array $user_message, array $form_state, $account) {
  $values = $form_state['values'];
  $webform_values = $values['webform_flat'];
  $zip = '';
  $response = '';
  $districted = $values['districted'];

  // Get the zip+4 from smarty streets.
  $geo = !empty($form_state['values']['smarty_geo']) ? $form_state['values']['smarty_geo'] : array();

  if (!empty($geo) && !empty($geo['zip']) && !empty($geo['plus4'])) {
    $zip = $geo['zip'] . '-' . $geo['plus4'];
  }

  // We've got a full zip, so we can prepare the submission to send
  // to the resolver.
  if (($districted && !empty($zip)) || !$districted) {
    // Build the contact array.
    $contact = sba_social_action_build_contact($webform_values, $zip, $geo, $districted, $account);

    // Build the message array.
    $message_build = sba_social_action_build_messages($user_message);
    // Build the submission array.
    $submission = array(
      'contact' => $contact,
      'form_id' => $values['advocacy_id'],
      'messages' => $message_build,
      'message_edited' => $webform_values['sba_user_edit_flag'],
      'multiflow' => 'step_one'
    );

    // Send submission to API Client.
    $api_call = springboard_advocacy_api_call();
    $response = $api_call->invokeClientMethod('resolveTargets', $submission);
    if (isset($response->data)) {
      // We got a valid response, build the confirmation message array.
      sba_social_action_set_confirmation_session_vars($response->data, $contact);
    }
  }
  return !empty($response->data) ? $response->data : NULL;
}

/**
 * Loads the messages associated with this webform.
 *
 * Formats them into an array for the target resolver.
 *
 * @param array $user_message
 *   The submitted messages.
 *
 * @return array
 *   Messages formatted for the API call.
 */
function sba_social_action_build_messages(array $user_message) {
  $all_messages = entity_load('sba_message', array_keys($user_message));
  $messages = array();
  $x = 0;

  foreach ($all_messages as $message) {
    $message_wrapper = entity_metadata_wrapper('sba_message', $message);
    $message_unique_id = $message->data['message_id'];
    $weight = !empty($message->data['precedence']) ? $message->data['weight'] : $x++;
    $undistricted = !$message_wrapper->field_sba_target_options->value();
    $messages[$weight] = array(
      'message_id' => $message_unique_id,
      'subject' => isset($user_message[$message->sba_message_id]['subject']) ? $user_message[$message->sba_message_id]['subject'] : '',
      'body' => $user_message[$message->sba_message_id]['body'],
      'topic' => '',
      'precedence' => !empty($message->data['precedence']) ? 1 : 0,
      'undistricted' => $undistricted,
    );
  }
  ksort($messages);
  return $messages;
}

/**
 * Merges the webform users contact data with data returned from smarty streets.
 *
 * Preparation for sending to target resolver.
 *
 * @param array $values
 *    Springboard Profile Values.
 * @param string $zip
 *   A zip + 4 code.
 * @param array $geo
 *   Array of address data returned from Smarty Streets lookup.
 *
 * @return array
 *   Contact's profile data plus smarty data.
 */
function sba_social_action_build_contact(array $values, $zip, array $geo = array(), $districted, $account) {

  $line_2 = !empty($values['sbp_address_line_2']) ? $values['sbp_address_line_2'] . "\n " : '';

  $contact = array(
    'first_name' => $values['sbp_first_name'],
    'last_name' => $values['sbp_last_name'],
    'email' => $values['mail'],
   );

  if ($districted) {
    $contact += array(
      'address' => $values['sbp_address'],
      'address_line_2' => $values['sbp_address_line_2'],
      'city' => $values['sbp_city'],
      'state' => $values['sbp_state'],
      'zip' => $zip,
      'full_address' => $values['sbp_address'] . "\n" . $line_2 . $values['sbp_city'] . ", " . $values['sbp_state'] . " " . $zip,
      'county' => isset($geo['county']) ? $geo['county'] : '',
      'fips' => isset($geo['fips']) ? $geo['fips'] : '',
      'latitude' => isset($geo['latitude']) ? $geo['latitude'] : '',
      'longitude' => isset($geo['longitude']) ? $geo['longitude'] : '',
    );
  }
  else {
    // To make it past the TargetResolverController validator function
    // send profile or dummy values.
    if (!empty($account)) {
      $zip_field = field_get_items('user', $account, 'sbp_zip_plus_four');
      $address_field = field_get_items('user', $account, 'sbp_address');
      $city_field = field_get_items('user', $account, 'sbp_city');
      $state_field = field_get_items('user', $account, 'sbp_state');
    }

    $zip = !empty($zip_field[0]['value']) ? $zip_field[0]['value'] : '12345-1234';
    $address = !empty($address_field[0]['value']) ? $address_field[0]['value'] : 'Any Street';
    $city = !empty($city_field[0]['value']) ? $city_field[0]['value'] : 'Any Town';
    $state = !empty($state_field[0]['value']) ? $state_field[0]['value'] : 'NY';

    $contact += array(
      'address' => $address,
      'address_line_2' => '',
      'city' => $city,
      'state' => $state,
      'zip' => $zip,
      'full_address' => '',
      'county' => isset($geo['county']) ? $geo['county'] : '',
      'fips' => isset($geo['fips']) ? $geo['fips'] : '',
      'latitude' => isset($geo['latitude']) ? $geo['latitude'] : '',
      'longitude' => isset($geo['longitude']) ? $geo['longitude'] : '',
    );
  }
  return $contact;
}

/**
 * Create session vars to hold data for use by confirmation theming functions.
 *
 * The session variables are passed through their theming functions
 * from hook_tokens().
 *
 * @param object $response
 *   The API response.
 */
function sba_social_action_set_confirmation_session_vars($response, $contact) {
  if (!empty($response->messages)) {
    $_SESSION['deliverable_social_messages'] = array();
    $_SESSION['undeliverable_social_messages'] = array();
    $_SESSION['social_form_details'] = array(
      'action_id' => isset($response->alert_id) ? $response->alert_id: '',
      'account_id' => isset($response->account_id) ? $response->account_id : '',
    );

    $_SESSION['social_contact'] = $contact;
    $status = sba_social_action_get_message_statuses($response);
    unset($status['success']['target_count']);
    if (!empty($status['success'])) {
      $messages = array();
      $count_messages = count($status['success']);
      $count_targets = 0;
      $x = 0;
      foreach ($status['success'] as $id => $message) {
        foreach ($message['people'] as $key => $person) {
          $count_targets++;
          $messages[$x]['person'] = $person;
          $messages[$x]['subject'] = $status['success'][$id]['subject'];
          $messages[$x]['body'] = $status['success'][$id]['body'];
          $messages[$x]['targets'] = $message['targets'][$key];
          // Needed for step-two forms.
          $messages[$x]['message_id'] = $id;
          //$messages[$x]['precedence'] = $status['success'][$id]['precedence'];
          $x++;
        }
      }
      $_SESSION['deliverable_social_messages'] =
        array(
          'messages' => $messages,
          'target_count' => $count_targets,
          'message_count' => $count_messages,
        );
    }
    unset($status['hold']['target_count']);
    $messages = array();
    $y = 0;
    if (!empty($status['hold'])) {
      foreach ($status['hold'] as $id => $message) {
        foreach ($message['people'] as $key => $person) {
          $messages[$y]['person'] = $person;
          $messages[$y]['body'] = $status['hold'][$id]['body'];
          $messages[$y]['subject'] = $status['hold'][$id]['subject'];
          $messages[$y]['targets'] = $message['targets'][$key];
          $messages[$y]['message_id'] = $id;
          //$messages[$y]['precedence'] = $status['hold'][$id]['precedence'];
          $messages[$y]['hold'] = TRUE;
          $y++;
        };
      }
    }
  }
}


/**
 * Split up the "deliverable" response into "success" and "hold".
 *
 * Some deliverable target webforms may be temporarily out of action and
 * the target object in the response will have a "webform_status" property
 * set to "hold". If so, we split those off into a separate array for display
 * on the confirmation page.
 *
 * @param object $response
 *   The API server response.
 *
 * @return array
 *   An array of messages.
 */
function sba_social_action_get_message_statuses($response) {

  $messages = array();
  $message_success = array();
  $message_hold = array();
  $success_count = 0;
  $hold_count = 0;

  foreach ($response->messages as $id => $message) {
    if (!empty($message->deliverable)) {
      $messages[$id]['deliverable'] = $message->deliverable;
      $messages[$id]['subject'] = $message->message->subject;
      $messages[$id]['body'] = $message->message->body;
    }
  }

  foreach ($messages as $id => $message) {
    foreach ($messages[$id]['deliverable'] as $target) {
      // Filter the largish target object in the response down to
      // a few select properties, in an array
      $target_details = sba_social_action_get_target_details($target);

      // Split into success and hold arrays.
      if (!empty($target->twitter)) {
        $success_count++;
        $message_success['target_count'] = $success_count;
        $message_success[$id]['people'][] = $target_details;
        $message_success[$id]['subject'] = isset($messages[$id]['subject']) ? $messages[$id]['subject'] : '';
        $message_success[$id]['body'] = $messages[$id]['body'];
        $message_success[$id]['targets'][] = $target;
      }
      else {
        $hold_count++;
        $message_hold['target_count'] = $hold_count;
        $message_hold[$id]['people'][] = $target_details;
        $message_hold[$id]['subject'] = isset($messages[$id]['subject']) ? $messages[$id]['subject'] : '';
        $message_hold[$id]['body'] = $messages[$id]['body'];
        $message_hold[$id]['targets'][] = $target;
      }
    }
  }

  return array('success' => $message_success, 'hold' => $message_hold);
}

/**
 * Creates an array of recipients for each message.
 *
 * An array with name and organization details
 * that eventually gets converted to a readable string in the
 * confirmation theme function.
 *
 * @param object $target
 *   A target object extracted from the API response.
 *
 * @return array
 *   An array containing a subset of target properties.
 */
function sba_social_action_get_target_details($target) {

  $name = array();
  $target_details = array();

  if (!empty($target->salutation)) {
    $name[] = $target->salutation;
  }
  if (!empty($target->first_name)) {
    $name[] = $target->first_name;
  }
  if (!empty($target->last_name)) {
    $name[] = $target->last_name;
  }

  $target_details['name'] = implode(' ', $name);

  if (!empty($target->party)) {
    $target_details['party'] = check_plain($target->party);
  }
  if (!empty($target->state) && empty($target->district_name)) {
    $target_details['state'] = check_plain($target->state);
  }
  if (!empty($target->district_name)) {
    $target_details['district'] = check_plain($target->district_name);
  }

  if (!empty($target->twitter)) {
    $url = parse_url($target->twitter);
    $target_details['twitter'] = check_plain(substr($url['path'], 1));
  }
  if (!empty($target->facebook)) {
    $url = parse_url($target->facebook);
    $target_details['facebook'] = check_plain(substr($url['path'], 1));
  }
  if (!empty($target->website)) {
    $target_details['website'] = $target->website;
  }

  $target_details['organization'] = !empty($target->organization) ? check_plain($target->organization) : '';

  if (!empty($target->title)) {
    $target_details['title'] = check_plain($target->title);
  }

  return $target_details;
}

/**
 * Theme a target for the preview page.
 *
 * @param $vars
 * @return string
 */
function theme_sba_social_action_person_details(&$vars) {
  $output = '';
  $target = $vars['message']['person'];
  $person = isset($target['name_with_webform_url']) ? $target['name_with_webform_url'] : $target['name'];
  if ($vars['type'] == 'sba_social_action_twitter_message' && isset($target['twitter'])) {
    //$person .= ' (<span class="twitter-handle">@' . $target['twitter'] . '</span>)';
  }
  $title = isset($target['title']) ? ' ' . $target['title']  : '' ;
  $party = isset($target['party']) ? ' (' . $target['party'] . ')' : '';
  $organization = !empty($target['organization']) ? $target['organization'] : '';
  $separator = !empty($title) && !empty($organization) ? ', ' : ' ';
  $state = isset($target['district']) && $vars['message']['targets']->class_name == 'Legislator' ? $vars['message']['targets']->state : '';
  if (empty($state) && $target['title'] == 'Governor') {
    $state = ' ' . $target['state'];
    $separator = ', ';
  }
  $state = $state == 'Al' ? '' : $state;
  // Custom targets and executive branch.
  $non_legislative_organization = !empty($organization)  ? $title . $separator . $organization :  $title . $separator . $state;
  // Legislators. Backward compatible with Target db structure pre-fall 2015 release;
  $legislative_organization = isset($target['district']) && !empty($title) ? $title . ', ' .  $state  : $organization;

  $affiliation = isset($target['district'])  ? $legislative_organization : $non_legislative_organization;
  $output .= $person;
  if(!empty($affiliation)) {
    $output .= $party;
    $output .= '<br />' . $affiliation;
  }
  return $output;
}