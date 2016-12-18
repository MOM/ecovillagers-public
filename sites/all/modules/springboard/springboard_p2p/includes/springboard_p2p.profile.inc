<?php

/**
 * @file
 * Pages related to completing the user profile when registering from Facebook.
 */

/**
 * Form for completing profile.
 */
function springboard_p2p_complete_profile_form($form, &$form_state, $account) {
  $form_state['user'] = $account;
  $form['#user'] = $account;
  // Category used by profile module.
  $form['#user_category'] = 'register';

  // Attach the regular user form.
  user_account_form($form, $form_state);

  // Attach the user field form elements.
  $langcode = function_exists('entity_language') ? entity_language('user', $form['#user']) : NULL;
  field_attach_form('user', $account, $form, $form_state, $langcode);

  $required_fields = springboard_p2p_get_required_registration_fields();
  foreach (element_children($form) as $key) {
    if (!empty($required_fields[$key])) {

      // If the user has already filled out a value for this field, hide it.
      if (!springboard_p2p_complete_profile_field_is_empty('user', $account, $key)) {
        $form[$key]['#access'] = FALSE;
      }
      else {
        springboard_p2p_set_registration_field_required($form, $key, TRUE);
        $form[$key]['#weight'] = $required_fields[$key]['weight'];
      }
    }
    else {
      $form[$key]['#access'] = FALSE;
    }
  }

  $form['help'] = array(
    '#markup' => '<p>' . t('Fill out the following fields to complete your profile.') . '</p>',
    '#weight' => -100,
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  form_load_include($form_state, 'inc', 'user', 'user.pages');
  $form['#validate'][] = 'user_profile_form_validate';
  $form['#submit'][] = 'user_profile_form_submit';

  springboard_p2p_campaign_id_form_element($form, $form_state);

  // A flag to tell us later in the process that the user is registering
  // for p2p for the first time.
  $form['registering_for_p2p'] = array(
    '#type' => 'value',
    '#value' => TRUE,
  );

  if (springboard_p2p_should_add_state_and_country_ajax($form)) {
    form_load_include($form_state, 'inc', 'springboard_p2p', 'includes/springboard_p2p.register');
    springboard_p2p_set_country_and_state_defaults_and_options($form, $form_state);
    springboard_p2p_add_state_and_country_ajax($form);
  }

  return $form;
}
