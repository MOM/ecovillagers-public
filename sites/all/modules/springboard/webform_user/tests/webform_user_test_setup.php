<?php
/**
 * @file
 * Webform user module setup class for children test cases,.
 */

/**
 * Setup and tear down web class. Does nothing else.
 */
abstract class WebformUserTestSetup extends DrupalWebTestCase {

  /**
   * Implementation of setUp().
   */
  public function setUp($additional_modules = array()) {
    $enable_modules = array(
      'webform_user',
    );

    $enable_modules = array_merge($enable_modules, $additional_modules);

    // Call the parent to set all of the base modules up.
    parent::setUp($enable_modules);

    // Setup the environment to a default standard.
    $this->webformUserSetupUserProfile();
    $this->webformUserCreateType();
    // $this->webformUserCreateNode();
    // Create a webform editor to test creating and editing own content.
    $permissions['editor'] = array(
      'access content',
      'administer nodes',
      'create webform content',
      'create petition content',
      'edit own webform content',
      'edit own petition content',
      'access all webform results',
    );

    // Create a webform admin that will do all node creation.
    $permissions['admin'] = array(
      'access content',
      'administer nodes',
      'create webform content',
      'create petition content',
      'edit any webform content',
      'access all webform results',
      'edit all webform submissions',
      'delete all webform submissions',
      'administer users',
      'administer user map',
      'alter webform components',
      'configure webform settings',
      'configure webform emails',
    );

    // Make sure the new permissions for the content type get added to the
    // permission cache.
    $this->checkPermissions(array('create petition content'), TRUE);

    foreach ($permissions as $user_key => $role_permissions) {
      $this->users[$user_key] = $this->drupalCreateUser($role_permissions);
    }

    // Set the mail system to test.
    variable_set('mail_system', array('default-system' => 'TestingMailSystem'));
  }

  /**
   * Create an instance of a webform user enabled node to use for testing.
   */
  protected function webformUserCreateNode() {
    // Create the node.
    $node = new stdClass();
    $node->is_new = 1;
    $node->type = 'petition';
    $node->language = LANGUAGE_NONE;
    $node->uid = 1;
    $node->title = 'Save the Humans';
    $node->field_fundraiser_internal_name = array($node->language => array(0 => array('value' => 'Save the Humans')));
    $node->status = 1;
    $node->promote = 1;
    $node->body['LANGUAGE_NONE'][0]['value'] = 'Sign the petition to save the humans.';
    $node->body['LANGUAGE_NONE'][0]['summary'] = 'Sign the petition to save the humans.';
    $node->body['LANGUAGE_NONE'][0]['format'] = 'filtered_html';
    $node->webform = array(
      'confirmation' => 'Thank you for saving the humans, [current-user:sbp-first-name].',
      'confirmation_format' => 'filtered_html',
      'redirect_url' => '<confirmation>',
      'teaser' => 0,
      'block' => 0,
      'allow_draft' => 0,
      'auto_save' => 0,
      'submit_notice' => 1,
      'submit_limit' => -1,
      'submit_interval' => -1,
      'total_submit_limit' => -1,
      'total_submit_interval' => -1,
      'status' => 1,
      'record_exists' => '',
      'roles' => array(
        '0' => 1,
        '1' => 2,
      ),
      'emails' => array(),
      'components' => array(),
    );

    $node->is_webform_user = 1;
    $node->send_new_user_email = 0;
    node_save($node);
  }

  /**
   * Create a petition content type and webform user enable it.
   */
  protected function webformUserCreateType() {
    $type = node_type_set_defaults();
    $type->name = t('Petition');
    $type->type = 'petition';
    $type->description = t('Webform user petition type.');
    $type->title_label = t('Title');
    $type->has_title = ($type->title_label != '');
    $type->base = 'node_content';
    $type->custom = TRUE;
    $type->modified = TRUE;

    // Save or reset persistent variable values.
    $variables = array(
      'node_submitted' => 0,
      'comment' => COMMENT_NODE_HIDDEN,
      'webform_user' => 1,
      'webform_user_default_fields' => array(
        'webform_user_all_profile_fields' => 'webform_user_all_profile_fields',
      ),
    );
    foreach ($variables as $key => $value) {
      $variable_new = $key . '_' . $type->type;
      if (is_array($value)) {
        $value = array_keys(array_filter($value));
      }
      variable_set($variable_new, $value);
    }
    $status = node_type_save($type);
    node_types_rebuild();
    node_add_body_field($type);

    // Add as a webform.
    $webform_node_types = variable_get('webform_node_types', array('webform'));
    $webform_node_types_primary = variable_get('webform_node_types_primary', array('webform'));
    $webform_node_types = array_merge($webform_node_types, array('petition'));
    $webform_node_types_primary = array_merge($webform_node_types_primary, array('petition'));
    variable_set('webform_node_types', array_unique($webform_node_types));
    variable_set('webform_node_types_primary', array_unique($webform_node_types_primary));
  }

  /**
   * Creates standard set of user profile fields that are used in webform_user.
   */
  protected function webformUserSetupUserProfile() {
    // Get default profile field definitions.
    $profile_fields = $this->webformUserDefaultProfileFields();

    // Create the field on the user for each profile.
    foreach ($profile_fields as $profile_field) {
      $field = array(
        'field_name' => $profile_field['field_name'],
        'cardinality' => 1,
        'type' => $profile_field['type'],
        'settings' => isset($profile_field['settings']) ? $profile_field['settings'] : array(),
      );
      field_create_field($field);
      $instance = array(
        'entity_type' => 'user',
        'bundle' => 'user',
      );
      $instance = array_merge($profile_field, $instance);
      field_create_instance($instance);
    }

  }

  /**
   * Create a user account and fills in some profile fields.
   *
   * @return false|object
   *   The user object.
   */
  protected function webformUserCreateUser() {
    // Create a user to test with.
    $user = $this->drupalCreateUser(array('access content'));

    $edit = array();
    $edit['sbp_first_name'][LANGUAGE_NONE][0]['value'] = 'Ralph';
    $edit['sbp_last_name'][LANGUAGE_NONE][0]['value'] = 'Mouth';
    $edit['sbp_address'][LANGUAGE_NONE][0]['value'] = '129 3rd Street';
    $edit['sbp_address_line_2'][LANGUAGE_NONE][0]['value'] = '';
    $edit['sbp_city'][LANGUAGE_NONE][0]['value'] = 'Milwaukee';
    $edit['sbp_state'][LANGUAGE_NONE][0]['value'] = 'WI';
    $edit['sbp_country'][LANGUAGE_NONE][0]['value'] = 'US';
    $edit['sbp_zip'][LANGUAGE_NONE][0]['value'] = '55555';

    // Save the user with new profile field values.
    user_save($user, $edit);

    return $user;
  }

  /**
   * Utility function, checks to see if a component exists for a given webform.
   */
  protected function webformUserComponentExists($nid, $form_key) {
    return (bool) db_query('SELECT cid FROM {webform_component} WHERE form_key = :form_key AND nid=:nid',
      array(':form_key' => $form_key, ':nid' => $nid))->fetchField();
  }

  /**
   * Utility function to get the details of a webform component.
   */
  protected function webformUserComponentDetails($nid, $form_key) {
    return db_query('SELECT cid, form_key, type, mandatory FROM {webform_component} WHERE form_key = :form_key AND nid = :nid', array(':form_key' => $form_key, ':nid' => $nid))->fetchObject();
  }

  /**
   * Utility function to create new user entity fields.
   */
  protected function webformUserAddField($name, $label, $type) {

    $field = array(
      'field_name' => $name,
      'type' => $type,
      'cardinality' => 1,
    );

    field_create_field($field);

    $instance = array(
      'field_name' => $name,
      'label' => $label,
      'entity_type' => 'user',
      'bundle' => 'user',
    );

    field_create_instance($instance);
  }

  /**
   * Utility function to return all standard profile field definitions.
   */
  protected function webformUserDefaultProfileFields() {
    $profile_fields = array();

    $profile_fields[] = array(
      'label' => t('First name'),
      'field_name' => 'sbp_first_name',
      'type' => 'text',
      'widget' => array(
        'type' => 'text_textfield',
      ),
    );
    $profile_fields[] = array(
      'label' => t('Last name'),
      'field_name' => 'sbp_last_name',
      'type' => 'text',
      'widget' => array(
        'type' => 'text_textfield',
      ),
    );
    $profile_fields[] = array(
      'label' => t('Address'),
      'field_name' => 'sbp_address',
      'type' => 'text',
      'widget' => array(
        'type' => 'text_textfield',
      ),
    );
    $profile_fields[] = array(
      'label' => t('Address Line 2'),
      'field_name' => 'sbp_address_line_2',
      'type' => 'text',
      'widget' => array(
        'type' => 'text_textfield',
      ),
    );
    $profile_fields[] = array(
      'label' => t('City'),
      'field_name' => 'sbp_city',
      'type' => 'text',
      'widget' => array(
        'type' => 'text_textfield',
      ),
    );
    $profile_fields[] = array(
      'label' => t('State/Province'),
      'field_name' => 'sbp_state',
      'type' => 'text',
      'widget' => array(
        'type' => 'text_textfield',
      ),
    );
    $profile_fields[] = array(
      'label' => t('Postal Code'),
      'field_name' => 'sbp_zip',
      'type' => 'text',
      'widget' => array(
        'type' => 'text_textfield',
      ),
    );
    $profile_fields[] = array(
      'label' => t('Country'),
      'field_name' => 'sbp_country',
      'type' => 'text',
      'widget' => array(
        'type' => 'text_textfield',
      ),
    );
    $profile_fields[] = array(
      'label' => t('Campaign ID'),
      'field_name' => 'sbp_cid',
      'type' => 'text',
      'widget' => array(
        'type' => 'text_textfield',
      ),
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'type' => 'hidden',
        ),
      ),
    );
    $profile_fields[] = array(
      'label' => t('Market Source'),
      'field_name' => 'sbp_ms',
      'type' => 'text',
      'widget' => array(
        'type' => 'text_textfield',
      ),
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'type' => 'hidden',
        ),
      ),
    );
    $profile_fields[] = array(
      'label' => t('Referrer'),
      'field_name' => 'sbp_referrer',
      'type' => 'text',
      'widget' => array(
        'type' => 'text_textfield',
      ),
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'type' => 'hidden',
        ),
      ),
    );
    $profile_fields[] = array(
      'label' => t('Initial Referrer'),
      'field_name' => 'sbp_initial_referrer',
      'type' => 'text',
      'widget' => array(
        'type' => 'text_textfield',
      ),
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'type' => 'hidden',
        ),
      ),
    );
    $profile_fields[] = array(
      'label' => t('Search Engine'),
      'field_name' => 'sbp_search_engine',
      'type' => 'text',
      'widget' => array(
        'type' => 'text_textfield',
      ),
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'type' => 'hidden',
        ),
      ),
    );
    $profile_fields[] = array(
      'label' => t('Search String'),
      'field_name' => 'sbp_search_string',
      'type' => 'text',
      'widget' => array(
        'type' => 'text_textfield',
      ),
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'type' => 'hidden',
        ),
      ),
    );
    $profile_fields[] = array(
      'label' => t('User Agent'),
      'field_name' => 'sbp_user_agent',
      'type' => 'text',
      'widget' => array(
        'type' => 'text_textfield',
      ),
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'type' => 'hidden',
        ),
      ),
    );
    $profile_fields[] = array(
      'label' => t('Salesforce Account Id'),
      'field_name' => 'sbp_salesforce_account_id',
      'type' => 'text',
      'widget' => array(
        'type' => 'text_textfield',
      ),
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'type' => 'hidden',
        ),
      ),
    );
    $profile_fields[] = array(
      'label' => t('Salesforce Contact Id'),
      'field_name' => 'sbp_salesforce_contact_id',
      'type' => 'text',
      'widget' => array(
        'type' => 'text_textfield',
      ),
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'type' => 'hidden',
        ),
      ),
    );

    return $profile_fields;
  }

}
