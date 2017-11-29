<?php
/**
 * @file
 * Secure autofill admin functions
 */

/**
 * System settings form for secure autofill.
 */
function secure_prepopulate_admin_settings($form, &$form_state) {
  $form = array();

  $form['secure_prepopulate_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Encryption key'),
    '#description' => t('To use 128 bit encryption enter a 16 character (128 bit) AES key. 256 bit encryption requires a 32 character key (256 bits).'),
    '#default_value' => variable_get('secure_prepopulate_key', ''),
  );

  $form['secure_prepopulate_iv'] = array(
    '#type' => 'textfield',
    '#title' => t('Initialization vector'),
    '#description' => t('A 16 character (128 bit) initialization vector. The initialization vector (IV) is a fixed-size input to a cryptographic primitive ' .
      'that is typically required to be random or pseudorandom.'),
    '#default_value' => variable_get('secure_prepopulate_iv', ''),
  );

  $form['dynamic_gift_strings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Dynamic gift string settings'),
    '#weight' => 1,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['dynamic_gift_strings']['secure_prepopulate_global_gift_strings'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable persistent gift strings'),
    '#default_value' => variable_get('secure_prepopulate_global_gift_strings', 0),
    '#description' => t("Display the user's persistent gift string on all eligible forms."),
  );

  $form['dynamic_gift_strings']['secure_prepopulate_dynamic_gift_strings_cookie_lifetime'] = array(
    '#type' => 'textfield',
    '#title' => t('Persistent gift string cookie lifetime'),
    '#default_value' => variable_get('secure_prepopulate_dynamic_gift_strings_cookie_lifetime', '1 year'),
    '#description' => t('How long the persistent gift string cookie should persist for each user. "1 year", "2 months", "5 days" are all acceptable values.'),
    '#states' => array(
      'visible' => array(
        ':input[name=secure_prepopulate_global_gift_strings]' => array('checked' => TRUE),
      ),
    ),
  );


  $form['secure_prepopulate']['secure_prepopulate_expiration_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Secure autofill expiration settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['secure_prepopulate']['secure_prepopulate_expiration_settings']['secure_prepopulate_toggle_expiration']= array(
    '#type' => 'checkbox',
    '#title' => t('Autofill tokens never expire'),
    '#description' => t('Check this setting to allow the pre-population token to be used on multiple site visits.'),
    '#default_value' => variable_get('secure_prepopulate_toggle_expiration', 0),
  );

  $form['secure_prepopulate']['secure_prepopulate_expiration_settings']['secure_prepopulate_expired_date_limit'] = array(
    '#type' => 'textfield',
    '#size' => 6,
    '#title' => t('Number of days before entries are cleared from the expired table'),
    '#description' => t('Clean out entries from the expired table that are older than the given amount of days.'),
    '#default_value' => variable_get('secure_prepopulate_expired_date_limit', 30),
    '#states' => array( // Disable this field if "pre-populated tokens never expire" is checked; otherwise enable.
      'disabled' => array(
        ':input[name="secure_prepopulate_toggle_expiration"]' => array('checked' => TRUE),
      ),
      'enabled' => array(
        ':input[name="secure_prepopulate_toggle_expiration"]' => array('checked' => FALSE),
      ),
    ),
  );

  // Custom "not me" message.
  $form['secure_prepopulate_not_me'] = array(
    '#type' => 'textarea',
    '#title' => t("'Not Me' Message"),
    '#weight' => 100,
    '#description' => t("Enter custom message for 'Not Me.' FIRSTNAME will be replaced by the first name from the secure autofill string. The 'Not Me' link must include the notme ID."),
    '#default_value' => variable_get('secure_prepopulate_not_me', "<div id='welcome-back'><span class='welcome-back-name'>Welcome back, <span class='welcome-back-name'>FIRSTNAME</span>. Not FIRSTNAME? <a id='notme' href='javascript:void(0)'>Click here</span></div>"),
  );

  return system_settings_form($form);
}

/**
 * Settings validation routine.
 */
function secure_prepopulate_admin_settings_validate(&$form, $form_state) {
  if (mb_strlen($form_state['values']['secure_prepopulate_key']) != 32 && mb_strlen($form_state['values']['secure_prepopulate_key']) != 16) {
    form_set_error('secure_prepopulate_key', 'Key must be either 128 bits (16 bytes) or 256 bits (32 bytes) in length.');
  }
  if (mb_strlen($form_state['values']['secure_prepopulate_iv']) != 16) {
    form_set_error('secure_prepopulate_iv', 'Initialization vector must be either 128 bits (16 bytes) in length.');
  }
  if (!is_numeric($form_state['values']['secure_prepopulate_expired_date_limit'])) {
    form_set_error('secure_prepopulate_expired_date_limit', 'Expired date limit must be numeric.');
  }
}


/**
 * Token Generator form.
 */
function secure_prepopulate_token_generator($form, $form_state) {

  $default_country = isset($form_state['values']['country']) ? $form_state['values']['country'] : 'US';
  $state_options = array();

  $form['secure_prepopulate'] = array(
    '#type' => 'fieldset',
    '#title' => t('Secure Pre-populate Token'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  // TODO: add user select box to import settings from existing user account.

  $form['secure_prepopulate']['first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First name'),
    '#size' => 20,
  );
  // last_name
  $form['secure_prepopulate']['last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#size' => 20,
  );
  // email
  $form['secure_prepopulate']['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#size' => 50,
  );
  // address
  $form['secure_prepopulate']['address'] = array(
    '#type' => 'textfield',
    '#title' => t('Address'),
  );
  // address_line_2
  $form['secure_prepopulate']['address_line_2'] = array(
    '#type' => 'textfield',
    '#title' => t('Address 2'),
  );
  // city
  $form['secure_prepopulate']['city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
  );

  // country
  $form['secure_prepopulate']['country'] = array(
    '#type' => 'textfield',
    '#title' => t('Country'),
  );

  // state
  $form['secure_prepopulate']['state'] = array(
    '#type' => 'textfield',
    '#title' => t('State or province'),
  );

  // zip
  $form['secure_prepopulate']['zip'] = array(
    '#type' => 'textfield',
    '#title' => t('Postal code'),
    '#size' => 10,
  );

  $form['dynamic_gift_strings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Dynamic Gift Strings Token'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['dynamic_gift_strings']['amounts'] = array(
    '#title' => t('Ask amounts'),
    '#type' => 'textfield',
    '#description' => t('Enter the ask amounts you want to show here. Values should be comma-separated. Example: 27,47,97'),
    '#size' => 50,
  );
  $form['dynamic_gift_strings']['default_amount'] = array(
    '#title' => t('Default amount'),
    '#type' => 'textfield',
    '#description' => t('If you want one of the supplied amounts to be selected by default, enter that value here.'),
    '#size' => 5,
  );
  if (module_exists('fundraiser_sustainers')) {
    $form['dynamic_gift_strings']['recurring_amounts'] = array(
      '#title' => t('Recurring ask amounts'),
      '#type' => 'textfield',
      '#description' => t('Enter the ask amounts you want to show here. Values should be comma-separated. Example: 27,47,97'),
      '#size' => 50,
    );
    $form['dynamic_gift_strings']['recurring_default'] = array(
      '#title' => t('Recurring default amount'),
      '#type' => 'textfield',
      '#description' => t('If you want one of the supplied amounts to be selected by default, enter that value here.'),
      '#size' => 5,
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Generate token'),
  );
  $form['#submit'][] = 'secure_prepopulate_token_generator_submit';
  return $form;
}

function secure_prepopulate_token_generator_submit($form, $form_state) {
  if ($af = secure_prepopulate_generate_af_string($form_state['values'])) {
    drupal_set_message('af token generated:');
    drupal_set_message($af);
  }
  if ($gs = secure_prepopulate_generate_gs_string($form_state['values'])) {
    drupal_set_message('gs token generated:');
    drupal_set_message($gs);
  }
}


/**
 * Generate an af query string based on values submitted by the token generator form.
 */
function secure_prepopulate_generate_af_string($input) {
  $keys = array(
    'first_name',
    'last_name',
    'email',
    'address',
    'address_line_2',
    'city',
    'country',
    'state',
    'zip',
  );
  $query_str = array();
  foreach ($keys as $key) {
    if (isset($input[$key]) && $input[$key]) {
      $query_str[] = $key . '=' . $input[$key];
    }
  }
  if (!count($query_str)) {
    return FALSE;
  }
  $query_str = implode('&', $query_str);
  $crypt = secure_prepopulate_encrypt($query_str);
  return 'af=' . urlencode($crypt);
}

function secure_prepopulate_generate_gs_string($input) {
  $query_str = '';
  if (!empty($input['amounts'])) {
    $query_str .= 'amounts=' . str_replace(',', '|', $input['amounts']);
    if (!empty($input['default_amount'])) {
      $query_str .= '&default=' . $input['default_amount'];
    }
  }
  if (!empty($input['recurring_amounts'])) {
    if (!empty($query_str)) $query_str .= '&';
    $query_str .= 'recurring_amounts=' . str_replace(',', '|', $input['recurring_amounts']);
    if (!empty($input['recurring_default'])) {
      $query_str .= '&recurring_default=' . $input['recurring_default'];
    }
  }
  if (!empty($query_str)) {
    $crypt = secure_prepopulate_encrypt($query_str);
    return 'gs=' . urlencode($crypt);
  } else {
    return FALSE;
  }
}

/**
 * Generate and display test URLs using tokens derived from test values set on the test generator form.
 */
function _secure_prepopulate_generate_test_urls($target_form_prefix) {  $form_defaults = _secure_prepopulate_get_test_generator_defaults();
  $sec_pop_vals = variable_get('sec_pop_test_gen_values', $form_defaults['secure_prepopulate']);
  $dyn_gift_vals = variable_get('dyn_gift_test_gen_values', $form_defaults['dynamic_gift_strings']);
  $urls = array();
  $output = '';

  // Define test URLs
  $test_url_options = array();
  $test_url_options[] = array(
    'descr' => t('Secure Autofill section information + ask amounts with default + recurring amounts with default'),
    'exclude_fields' => array());
  $test_url_options[] = array(
    'descr' => t('Secure Autofill section information + ask amounts with default + recurring amounts without default'),
    'exclude_fields' => array('recurring_default'));
  $test_url_options[] = array(
    'descr' => t('Secure Autofill section information + ask amounts with default + no recurring amounts'),
    'exclude_fields' => array('recurring_amounts', 'recurring_default'));
  $test_url_options[] = array(
    'descr' => t('Secure Autofill section information + ask amounts without default + recurring amounts with default'),
    'exclude_fields' => array('default_amount'));
  $test_url_options[] = array(
    'descr' => t('Secure Autofill section information + ask amounts without default + recurring amounts without default'),
    'exclude_fields' => array('default_amount', 'recurring_default'));
  $test_url_options[] = array(
    'descr' => t('Secure Autofill section information + ask amounts without default + no recurring amounts'),
    'exclude_fields' => array('default_amount', 'recurring_amounts', 'recurring_default'));
  $test_url_options[] = array(
    'descr' => t('Secure Autofill section information + no ask amounts + recurring amounts with default'),
    'exclude_fields' => array('amounts', 'default_amount'));
  $test_url_options[] = array(
    'descr' => t('Secure Autofill section information + no ask amounts + recurring amounts without default'),
    'exclude_fields' => array('amounts', 'default_amount', 'recurring_default'));
  $test_url_options[] = array(
    'descr' => t('Secure Autofill section information only'),
    'exclude_fields' => array('amounts', 'default_amount', 'recurring_amounts', 'recurring_default'));

  // Generate the token for secure populate fields:
  if ($af = secure_prepopulate_generate_af_string($sec_pop_vals)) {
    $sec_pop_token = substr($af, 3);
  }

  // Generate the dynamic gift strings tokens for each test link, then render the link:
  foreach ($test_url_options as $options) {
    $test_options = $dyn_gift_vals;
    foreach ($options['exclude_fields'] as $exclude_field) {
      if (isset($test_options[$exclude_field])) {
        unset($test_options[$exclude_field]);
      }
    }
    if ($gs = secure_prepopulate_generate_gs_string($test_options)) {
      $dyn_gift_token = substr($gs, 3);
      $output .= '<a href="/' .  $target_form_prefix . '?gs=' . $dyn_gift_token . '&af=' . $sec_pop_token . '">' . $options['descr'] . '</a><br />';
    }
  }

  return $output;
}

/**
 * The Test URL generation form.
 */
function secure_prepopulate_test_url_generator_form($form, &$form_state) {
  drupal_set_title('Secure Autofill Test Generator');
  $form = array();

  // Do not display the form if either the Encryption Key or Initialization vector are missing:
  $encryption_key = variable_get('secure_prepopulate_key', '');
  $init_vector = variable_get('secure_prepopulate_iv', '');
  if (!$encryption_key || !$init_vector) {
    $form['missing_fields'] = array(
      '#type' => 'markup',
      '#markup' => t('Please ensure both the Encryption Key and the Initialization Vector are set on the Secure Autofill settings page.'),
    );
    return $form;
  }


  $form_defaults = _secure_prepopulate_get_test_generator_defaults();
  $target_form_prefix = variable_get('dync_gift_test_get_url_prefix', 'springboard/node/2');
  // List the test URLs:
  $form['test_urls'] = array(
    '#title' => t('Test URLs:'),
    '#type' => 'fieldset',
    '#description' => _secure_prepopulate_generate_test_urls($target_form_prefix),
  );

  // Allow the secure prepopulate used in the test URLs to be changed:
  $form['sec_pop_values'] = array(
    '#title' => t('Secure-Autofill Test Values'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $sec_pop_vals = variable_get('sec_pop_test_gen_values', $form_defaults['secure_prepopulate']);
  foreach ($sec_pop_vals as $form_key => $default_value) {
    $form['sec_pop_values'][$form_key] = array(
     '#title' => $form_key,
     '#type' => 'textfield',
     '#default_value' => $default_value,
    );
  }

  // Allow the dynamic gift string values used in the test URLs to be changed:
  $form['dyn_gift_values'] = array(
    '#title' => t('Dynamic Gift String Test Values'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $dyn_gift_vals = variable_get('dyn_gift_test_gen_values', $form_defaults['dynamic_gift_strings']);
  $dyn_gift_descrs = array(
    'amounts' => t('Enter the ask amounts to be used as a comma-delimited; for example: 27,200,3000'),
    'recurring_amounts' => t('Enter the recurring ask amounts to be used as a comma-delimited list; for example: 27,200,3000'),
  );
  foreach ($dyn_gift_vals as $form_key => $default_value) {
    $form['dyn_gift_values'][$form_key] = array(
      '#title' => $form_key,
      '#type' => 'textfield',
      '#default_value' => $default_value,
    );
    if (isset($dyn_gift_descrs[$form_key])) {
      $form['dyn_gift_values'][$form_key]['#description'] = $dyn_gift_descrs[$form_key];
    }
  }

  $form['test_url_prefix'] = array(
    '#title' => 'Target form path',
    '#type' => 'textfield',
    '#default_value' => $target_form_prefix,
    '#required' => TRUE,
    '#description' => 'The path of the form to be tested; for example: springboard/node/2',
  );

  $form['submit'] = array(
    '#value' => t('Update Test URLs'),
    '#type' => 'submit',
  );
  return $form;
}

/**
 * For submit function for the test url generator.
 */
function secure_prepopulate_test_url_generator_form_submit($form, &$form_state) {
  $form_keys = _secure_prepopulate_get_test_generator_defaults();
  $new_sec_pop_defaults = array();
  foreach ($form_keys['secure_prepopulate'] as $key => $default_value) {
    if (isset($form_state['values'][$key])) {
      $new_sec_pop_defaults[$key] = $form_state['values'][$key];
    }
  }
  variable_set('sec_pop_test_gen_values', $new_sec_pop_defaults);

  $new_dyn_gift_defaults = array();
  foreach ($form_keys['dynamic_gift_strings'] as $key => $default_value) {
    if (isset($form_state['values'][$key])) {
      $new_dyn_gift_defaults[$key] = $form_state['values'][$key];
    }
  }
  variable_set('dyn_gift_test_gen_values', $new_dyn_gift_defaults);
  variable_set('dync_gift_test_get_url_prefix', $form_state['values']['test_url_prefix']);

  drupal_set_message('Test generator values have been updated.');
}


/**
 * Helpful function to return the list of field + default values for the test url generator:
 */
function _secure_prepopulate_get_test_generator_defaults() {
  return array(
    'secure_prepopulate' => array(
      'first_name' => 'Jane',
      'last_name' => 'Public',
      'email' => 'jane.q.public@example.com',
      'address' => '123 Lois Lane',
      'address_line_2' => 'Apt. 7',
      'city' => 'New York',
      'country' => 'US',
      'state' => 'NY',
      'zip' => '10005'
    ),
    'dynamic_gift_strings' => array(
      'amounts' => '10,20,50,100,200,2000',
      'default_amount' => '50',
      'recurring_amounts' => '10,20,50,100,200,2000',
      'recurring_default' => '20',
    ),
  );
}

