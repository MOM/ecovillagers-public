<?php

/**
 * @file
 * Configures the mapping of Salesforce objects to Drupal objects.
 */

/**
 * Menu redirect per node requirement.
 */
function _salesforce_map_redirect($node) {
  // Gather modules that provide mapping support for generic objects.
  // Given that our spec is such we want to minimize tree depth in form display,
  // And the menu system is unable to determine the type of the node before
  // displaying the links, a redirect at runtime is the only viable solution.
  // Given a node, determine what, if any types of mapping are available for it.
  $modules = salesforce_genmap_info();
  $supported_modules = array();
  foreach ($modules as $module => $info) {
    if (in_array($node->type, $info['supported content types'])) {
      $access_callback = isset($info['access callback']) ? $info['access callback'] : '';
      if (isset($info['file'])) {
        module_load_include('', $module, $info['file']);
      }
      if (function_exists($access_callback) && $access_callback($node, $module)) {
        $supported_modules[$module] = $info;
      }
    }
  }
  // Now we have a list of the supported mapping forms filters by access.
  // Only serve up the first of the available mappings.
  // TODO: Find support in the future for more than one mapping at this
  // location, WITHOUT having to rely on pre-set menus. Since menus are overall
  // ignorant of node-type.
  foreach ($supported_modules as $supported_module => $info) {
    return salesforce_genmap_map_page($node, $supported_module);
  }
  return t('No Salesforce mapping is available for this content type.');
}

/**
 * Page callback to render the mapping page.
 */
function salesforce_genmap_map_page($node, $module) {
  $build = array();
  $build['content'] = array(
    'page_description' => array(
      '#id' => 'salesforce-map-helptext-page',
      '#type' => 'markup',
      '#markup' => '<p>' . t('Map which values should be sent to your Salesforce organization.') . '</p>',
      '#prefix' => '<div class="salesforce-map-helptext">',
      '#suffix' => '</div>',
    ),
    'salesforce_genmap_map_form' => drupal_get_form('salesforce_genmap_map_form', $node, $module),
  );
  return $build;
}

/**
 * Form to do the actual mapping configuration processes.
 */
function salesforce_genmap_map_form($form, &$form_state, $node, $module) {
  // Fail if we can't connect to Salesforce.
  $sfapi = salesforce_get_api();
  if (!$sfapi->isAuthorized()) {
    return array(
      'no_sfapi' => array(
        '#markup' => '<p>' . t('Cannot connect to Salesforce, preventing the ability to map Salesforce objects.  !ConfigureSalesforce',
                array('!ConfigureSalesforce' => l(t('Configure Salesforce'), 'admin/config/salesforce/authorize'))) . '</p>',
        '#prefix' => '<div class="salesforce-map-error salesforce-map-error-salesforce">',
        '#suffix' => '</div>',
      ),
    );
  }

  // Time to build up the form.
  $form = array(
    '#tree' => TRUE,
    '#node' => $node,
    '#module' => $module,
    '#prefix' => '<div id="salesforce-generic-map-ajax-sf-object">',
    '#suffix' => '</div>',
  );

  $form['salesforce_object_info'] = array(
    '#type' => 'fieldset',
    '#title' => 'Salesforce Object Mapping',
  );

  // The type of Salesforce Object.
  $sf_objects = _sfw_salesforce_object_list($sfapi);
  $sf_object = _sfw_default_value($form, $form_state, 'salesforce_object_type', 'salesforce_object_info');
  $form['salesforce_object_info']['salesforce_object_type'] = array(
    '#id' => 'salesforce-object-type',
    '#title' => t('Salesforce object'),
    '#type' => 'select',
    '#description' => t('Select a Salesforce object to map to this Drupal object.'),
    '#default_value' => $sf_object,
    '#options' => $sf_objects,
    '#required' => TRUE,
    '#ajax' => array(
      'callback' => 'salesforce_genmap_map_form_ajax_sf_object',
      'wrapper' => 'salesforce-generic-map-ajax-sf-object',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  if (empty($sf_object)) {
    // Since the user has not selected a Salesforce object yet, we should not
    // display the remainder of the form.  Stop here.
    return $form;
  }

  // The type of record of the chosen Salesforce Object.
  $sf_records = _sfw_salesforce_record_type_list($sfapi, $sf_object, FALSE);
  if (count($sf_records) > 1) {
    $form['salesforce_object_info']['salesforce_record_type'] = array(
      '#id' => 'salesforce-record-type',
      '#title' => t('Object Record Type'),
      '#type' => 'select',
      '#description' => t('Select a record type.'),
      '#default_value' => _sfw_default_value($form, $form_state, 'salesforce_record_type', 'salesforce_object_info'),
      '#options' => $sf_records,
      '#required' => TRUE,
    );
  }

  // Add the mapping functionality to the form.
  $sf_fields = _sfw_salesforce_field_list($sfapi, $sf_object);
  $form['field_map'] = array(
    '#type' => 'fieldset',
    '#title' => 'Field Mapping',
  );

  // Get the fields to map for this module.
  $fields = module_invoke($module, 'salesforce_genmap_map_field_info', $node);
  // Allow for altering the field set.
  drupal_alter('salesforce_genmap_map_field_info', $fields, $node, $module);
  // Make the form for each field.
  foreach ($fields as $category => $category_info) {
    $map_row_class_name = 'salesforce-' . $category_info['#type'] . '-map-field';
    // Add the map from Drupal object fields to Salesforce fields.
    $form['field_map'][$category] = array(
      '#id' => 'salesforce-' . $category_info['#type'] . '-map',
      '#tree' => TRUE,
      '#theme' => 'table',
      '#header' => array($category_info['#label'], t('Salesforce Field')),
      '#row_storage' => array(),
    );

    // Process each listed field for our fieldset.
    foreach ($category_info['#fields'] as $field_key => $field_label) {
      $sf_field = _sfw_default_value($form, $form_state, 'sf_field', $category, $field_key);
      $row = array(
        'label' => array(
          '#id' => $category_info['#type'] . '-label-' . $field_key,
          '#markup' => $field_label,
          '#prefix' => '<label class="' . $map_row_class_name . '">',
          '#suffix' => '</label>',
        ),
        'sf_field' => array(
          '#id' => 'salesforce-map-' . $field_key,
          '#type' => 'select',
          '#default_value' => $sf_field,
          '#options' => $sf_fields,
        ),
      );
      if ($category_info['#dedupe'] == TRUE) {
        $row['sf_field']['#ajax'] = array(
          'callback' => 'salesforce_genmap_map_form_ajax_sf_dedupe',
          'wrapper' => 'salesforce-ajax-dedupe-' . $field_key,
          'method' => 'replace',
          'effect' => 'fade',
          '#form_key' => $field_key,
          '#category' => $category,
        );
        $row['dedupe'] = array(
          '#id' => 'salesforce-dedupe-' . $field_key,
          '#type' => 'hidden',
          '#value' => NULL,
          '#prefix' => '<div id="salesforce-ajax-dedupe-' . $field_key . '">',
          '#suffix' => '</div>',
        );
        $sf_field_dedupe = _sfw_salesforce_field_can_dedupe($sfapi, $sf_object, $sf_field);
        if (!empty($sf_field) && $sf_field_dedupe) {
          $dedupe_field = &$row['dedupe'];
          $dedupe_field['#type'] = 'radio';
          $dedupe_field['#return_value'] = $sf_field;
          $dedupe_field['#attributes'] = array('name' => 'salesforce_dedupe_field');
          $dedupe_field['#value'] = _sfw_default_value($form, $form_state, 'dedupe', $category, $field_key);
        }
      }
      $form['field_map'][$category]['#row_storage'][$field_key] = $row;
    }

    // Add additional dedupe features if dedupe is true.
    if ($category_info['#dedupe'] == TRUE) {
      $form['field_map'][$category]['#header'] = array(
        $category_info['#label'],
        t('Salesforce Field'),
        t('Dedupe Field'),
      );
      $form['field_map'][$category]['#sticky'] = FALSE;
      $form['field_map'][$category]['#prefix'] = '<div id="salesforce-' . $category_info['#type'] . '-map-ajax-sf-dedupe">';
      $form['field_map'][$category]['#suffix'] = '</div>';
      // Add some help text.
      $form['field_map'][$category]['#row_storage'][0] = array(
        'empty' => array(
          '#markup' => '',
        ),
        'helptext' => array(
          '#id' => 'salesforce-' . $category_info['#type'] . '-map-helptext-field-map',
          '#markup' => '<p>' . t('<strong>Dedupe Field:</strong> Minimizes duplicate
            records and allows updating existing records. Selecting a dedupe field
            chooses which field is the unique identifier for this form.  A dedupe
            option only appears if the selected field can be used as a unique
            identifier. Select \'None\' to not use this feature.') . '</p>',
          '#prefix' => '<div class="salesforce-' . $category_info['#type'] . '-map-helptext">',
          '#suffix' => '</div>',
        ),
        'no_dedupe' => array(
          '#id' => 'salesforce-no-dedupe',
          '#title' => t('None'),
          '#type' => 'radio',
          '#return_value' => 'none',
          '#attributes' => array('name' => 'salesforce_dedupe_field'),
          '#default_value' => _sfw_default_value($form, $form_state, 'no_dedupe', $category, 0),
        ),
      );
    }

    // Create the table.
    _sfw_generate_form_table($form['field_map'][$category]);
  }

  // Mapping configuration options.
  $form['map_config'] = array(
    '#type' => 'fieldset',
    '#title' => 'Map Configuration',
  );

  // Options for Syncing with Salesforce.
  $form['map_config']['sync_options'] = array(
    '#id' => 'salesforce-map-config-sync',
    '#type' => 'checkboxes',
    '#required' => TRUE,
    '#title' => t('Salesforce Sync Options'),
    '#description' => t('When should submissions of this object type be synced with Salesforce?'),
    '#default_value' => _sfw_default_value($form, $form_state, 'sync_options', 'map_config'),
    '#options' => array(
      'insert' => t('New submissions'),
      'update' => t('Modified submissions'),
    ),
  );

  // Add the option to configure a map to delete on sync only if this site is
  // configured to allow this configuration setting and the user has access.
  if (variable_get('salesforce_genmap_allow_delete_sync', FALSE) && user_access('configure ' . $module . ' delete sync')) {
    $form['map_config']['sync_options']['#options']['delete'] = t('Deleted submissions');
  }

  // Buttons buttons buttons.
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
    '#weight' => 1,

  );
  $map = salesforce_genmap_load_map($node->nid, $module);
  if (!empty($map)) {
    $form['cancel'] = array(
      '#type' => 'submit',
      '#value' => 'Cancel',
      '#weight' => 2,

    );
    $form['unmap'] = array(
      '#type' => 'submit',
      '#value' => 'Unmap',
      '#weight' => 3,
    );
  }

  // Add CSS after build to avoid validation errs.
  $form['#after_build'][] = 'salesforce_genmap_map_form_after_build';
  return $form;
}

/**
 * After build callback to add CSS.
 */
function salesforce_genmap_map_form_after_build($form, &$form_state) {
  drupal_add_css(drupal_get_path('module', 'salesforce_genmap') . '/css/salesforce_genmap.css');
  return $form;
}

/**
 * AJAX callback to populate the form for the chosen Salesforce object.
 */
function salesforce_genmap_map_form_ajax_sf_object($form) {
  return $form;
}

/**
 * AJAX callback to set a field row's dedupe cell.
 */
function salesforce_genmap_map_form_ajax_sf_dedupe($form, &$form_state) {
  $form_key = $form_state['triggering_element']['#ajax']['#form_key'];
  $category = $form_state['triggering_element']['#ajax']['#category'];
  return $form['field_map'][$category][$form_key]['dedupe'];
}

/**
 * Validate the mapping form.
 */
function salesforce_genmap_map_form_validate($form, &$form_state) {
  if (!isset($form_state['input']['field_map'])) {
    // There is nothing to check.
    return;
  }

  // Prevent the user from mistakenly bypassing the restriction for configuring
  // delete on sync.
  if (in_array('delete', $form_state['input']['map_config']['sync_options']) && !user_access('configure ' . $form['#module'] . ' delete sync')) {
    unset($form_state['input']['map_config']['sync_options']['delete']);
    $error_text = t('You do not have permission to configure a !module map to sync on delete.', array('!module' => $form['#module']));
    form_set_error('map_config][sync_options][delete', $error_text);
  }

  // No Salesforce field can be used twice.
  $error_text = t('Multiple fields cannot be mapped to the same Salesforce fields.');
  $sf_fields = array();
  foreach ($form_state['input']['field_map'] as $group => $drupal_fields) {
    foreach ($drupal_fields as $drupal_field => $columns) {
      $sf_field = isset($columns['sf_field']) ? $columns['sf_field'] : NULL;
      if (!empty($sf_field)) {
        $field_path = 'field_map][' . $group . '][' . $drupal_field . '][sf_field';
        $count = isset($sf_fields[$sf_field]) ? count($sf_fields[$sf_field]) : 0;
        if ($count == 1) {
          // Set error on current field.
          form_set_error($field_path, $error_text);

          // Set error on prior field.
          $prior_drupal_field = key($sf_fields[$sf_field]);
          $prior_field_path = 'field_map][' . $sf_fields[$sf_field][$prior_drupal_field] . '][' . $prior_drupal_field . '][sf_field';
          form_set_error($prior_field_path, $error_text);
        }
        elseif ($count > 1) {
          // Add another error for this field being used again.
          form_set_error($field_path, $error_text);
        }
        $sf_fields[$sf_field][$drupal_field] = $group;
      }
    }
  }
}

/**
 * Submit callback for the mapping form.
 */
function salesforce_genmap_map_form_submit($form, &$form_state) {
  $node = $form_state['build_info']['args'][0];

  // Delete the map.
  if ($form_state['clicked_button']['#value'] == 'Unmap') {
    $result = salesforce_genmap_delete_map($node->nid, $form['#module']);
    if ($result === FALSE) {
      drupal_set_message(t('There was an error deleting the map.'), 'error');
    }
    else {
      drupal_set_message(t('The Salesforce to Drupal object map has been removed.'));
    }
    return;
  }

  // Cancel and do nothing.
  elseif ($form_state['clicked_button']['#value'] == 'Cancel') {
    drupal_set_message(t('The Salesforce map has been reset to the original values.'));
    return;
  }

  // Save the contributed values.
  elseif ($form_state['clicked_button']['#value'] == 'Save') {
    $map = _sfw_convert_input($form_state['input']);
    $map['nid'] = $node->nid;
    $result = salesforce_genmap_save_map($map, $form['#module']);
    if ($result === FALSE) {
      drupal_set_message(t('There was an error saving the map.'), 'error');
    }
    else {
      drupal_set_message(t('The map was saved successfully.'));
    }
    return;
  }

  // No action was specified.
  drupal_set_message(t('Form was submitted unexpectedly. It has been reset to the original values.'), 'error');
}

/**
 * @} salesforce_genmap_map_form
 */


/**
 * @defgroup form_helper Misc tools to help streamline form building
 * @{
 */

/**
 * Helper function for the tedious case of finding the default value of a field.
 *
 * @param array $form
 *   Raw form array
 * @param array $form_state
 *   Current $form_state as given to you by the system
 * @param string $field
 *   Name of the field to find the default value of
 * @param string $group
 *   Fieldgroup the field is a child of
 * @param string $drupal_field
 *   Value of the field in Drupal, this is also known as the row key
 *
 * @return string
 *   The value of the field you requested
 */
function _sfw_default_value($form, $form_state, $field, $group = NULL, $drupal_field = NULL) {
  $node = $form_state['build_info']['args'][0];
  $node_map = salesforce_genmap_load_map($node->nid, $form['#module']);
  if (empty($form_state['input']) && empty($node_map)) {
    return '';
  }

  // Refer against inputted values if the form has been submitted, else the
  // node.
  if (empty($form_state['input']['salesforce_object_info']) && !empty($node_map)) {
    $map = (array) $node_map;
  }
  else {
    $map = _sfw_convert_input($form_state['input']);
  }

  // Salesforce object, record and dedupe field value.
  if (empty($group) || $group == 'salesforce_object_info' || $group == 'map_config') {
    if ($field == 'sync_options' && empty($map['sync_options'])) {
      // Make only insert and update default.  Delete should not be default
      // because it is too dangerous to be deleting records in Salesforce.
      return array(
        'insert',
        'update',
      );
    }
    elseif (isset($map[$field])) {
      return $map[$field];
    }
    elseif ($field == 'salesforce_record_type') {
      // If there is not a set record type yet, use the default record type for
      // the object.
      if (empty($map[$group]['salesforce_record_type'])) {
        $sf_object = _sfw_default_value($form, $form_state, 'salesforce_object_type', $group);
        return _sfw_salesforce_default_record_type($sf_object);
      }
    }
  }

  // Handling for the case of no dedupe field value.
  elseif ($field == 'no_dedupe') {
    $salesforce_dedupe_field = _sfw_default_value($form, $form_state, 'salesforce_dedupe_field');
    if (empty($salesforce_dedupe_field) || $salesforce_dedupe_field == 'none') {
      return TRUE;
    }
    return FALSE;
  }

  // Dedupe field values.
  // These are found by seeing which salesforce field is mapped to the related
  // dedupe field and then checking if salesforce_dedupe_field has that field
  // selected.
  elseif ($field == 'dedupe') {
    $salesforce_dedupe_field = _sfw_default_value($form, $form_state, 'salesforce_dedupe_field');
    if (!empty($salesforce_dedupe_field) && $salesforce_dedupe_field != 'none') {
      $sf_field = _sfw_default_value($form, $form_state, 'sf_field', $group, $drupal_field);
      if ($salesforce_dedupe_field == $sf_field) {
        return TRUE;
      }
    }
    return FALSE;
  }

  // The rest are all the salesforce mapping fields.
  else {
    if (isset($map['field_map'][$group][$drupal_field])) {
      return $map['field_map'][$group][$drupal_field];
    }
  }
  return '';
}

/**
 * Helper function to convert input from form submission into a savable format.
 */
function _sfw_convert_input($input) {
  $map = array();

  $map['salesforce_dedupe_field'] = NULL;
  if (isset($input['salesforce_dedupe_field']) && $input['salesforce_dedupe_field'] != 'none') {
    $map['salesforce_dedupe_field'] = $input['salesforce_dedupe_field'];
  }

  if (isset($input['salesforce_object_info'])) {
    $map['salesforce_object_type'] = '';
    if (isset($input['salesforce_object_info']['salesforce_object_type'])) {
      $map['salesforce_object_type'] = $input['salesforce_object_info']['salesforce_object_type'];
    }
    $map['salesforce_record_type'] = '';
    if (isset($input['salesforce_object_info']['salesforce_record_type'])) {
      $map['salesforce_record_type'] = $input['salesforce_object_info']['salesforce_record_type'];
    }
  }

  $map['field_map'] = array();
  if (isset($input['field_map'])) {
    foreach ($input['field_map'] as $group => $drupal_fields) {
      foreach ($drupal_fields as $drupal_field => $columns) {
        if (isset($columns['sf_field']) && !empty($columns['sf_field'])) {
          $map['field_map'][$group][$drupal_field] = $columns['sf_field'];
        }
      }
    }
  }

  $map['sync_options'] = isset($input['map_config']['sync_options']) ? $input['map_config']['sync_options'] : array();

  return $map;
}

/**
 * Helper function for the annoying case of setting a table in a form.
 */
function _sfw_generate_form_table(&$form) {
  foreach ($form['#row_storage'] as $row_num => $row) {
    // In order for the fields to render, they need to be in the root.
    $form[$row_num] = $row;
    foreach ($form[$row_num] as $column => $cell) {
      // The magic is right here.  You need to pass the field data by reference
      // to the table rendering in order for the fields to function properly.
      $form['#rows'][$row_num][$column]['data'] = &$form[$row_num][$column];
      $form['#rows'][$row_num][$column]['class'] = array('salesforce-table-field', 'salesforce-table-field-' . $column);
    }
  }
  unset($form['#row_storage']);
}

/**
 * Gather a simple list of Salesforce objects.
 *
 * @param Salesforce $sfapi
 *   A Salesforce API object
 *
 * @return Array
 *   Array of Salesforce objects keyed by the object's name and the label as the
 *   value
 */
function _sfw_salesforce_object_list(Salesforce $sfapi, $include_select = TRUE) {
  // Salesforce module v4 filters down to updatable and triggerable so it is
  // easier to visually consume the list.
  $objects_info = $sfapi->objects(array('updateable' => TRUE, 'triggerable' => TRUE));

  $dupes = array();
  $objects_list = array();
  if ($include_select) {
    $objects_list[NULL] = '- ' . t('Select object type') . ' -';
  }
  foreach ($objects_info as $object) {
    // Some objects have the same label, which just makes things confusing
    // I could make only subsequent duplicates unique, but I figure that users
    // may wonder what the first instance is referencing.
    if (in_array($object['label'], $objects_list)) {
      $dupes[] = $object['label'];
    }

    $objects_list[$object['name']] = $object['label'];
  }

  // Now make duplicate labels be unique.
  if (!empty($dupes)) {
    foreach ($objects_list as $object_name => $object_label) {
      if (in_array($object_label, $dupes)) {
        $objects_list[$object_name] = $object_label . ' (' . $object_name . ')';
      }
    }
  }

  asort($objects_list);
  return $objects_list;
}

/**
 * Gather a simple list of record types for a given Salesforce object.
 *
 * @param Salesforce $sfapi
 *   A Salesforce API object
 * @param String $sf_object
 *   The type of Salesforce object you are querying
 *
 * @return Array
 *   Array of record types of the given Salesforce object
 */
function _sfw_salesforce_record_type_list(Salesforce $sfapi, $sf_object, $include_select = TRUE) {
  $object_info = $sfapi->objectDescribe($sf_object);
  $record_type_list = array();
  if ($include_select) {
    $record_type_list[NULL] = '- ' . t('Select record type') . ' -';
  }
  foreach ($object_info['recordTypeInfos'] as $record_type) {
    if ($record_type['name'] != 'Master' && $record_type['available'] == TRUE) {
      $record_type_list[$record_type['recordTypeId']] = $record_type['name'];
    }
  }
  asort($record_type_list);
  return $record_type_list;
}

/**
 * Find the default record type for the given Salesforce object.
 *
 * @param String $sf_object
 *   The type of Salesforce object you are querying
 *
 * @return String
 *   The default record type of the given Salesforce object, or NULL if there is
 *   not a default type
 */
function _sfw_salesforce_default_record_type($sf_object) {
  $sfapi = salesforce_get_api();
  $object_info = $sfapi->objectDescribe($sf_object);
  foreach ($object_info['recordTypeInfos'] as $record_type) {
    if ($record_type['defaultRecordTypeMapping'] == TRUE) {
      return $record_type['name'];
    }
  }
  return NULL;
}

/**
 * Gather a simple list of fields for the given Salesforce object.
 *
 * @param Salesforce $sfapi
 *   A Salesforce API object
 * @param String $sf_object
 *   The type of Salesforce object you are querying
 *
 * @return Array
 *   Array of fields on the given Salesforce object
 */
function _sfw_salesforce_field_list(Salesforce $sfapi, $sf_object, $include_select = TRUE) {
  $object_info = $sfapi->objectDescribe($sf_object);
  $field_list = array();
  if ($include_select) {
    $field_list[NULL] = '- ' . t('Select field') . ' -';
  }
  foreach ($object_info['fields'] as $field) {
    // Filter out fields that can't be altered.
    if ($field['updateable'] || $field['createable']) {
      $field_list[$field['name']] = $field['label'];
    }
  }
  asort($field_list);
  return $field_list;
}

/**
 * Find out the idLookup value for a given Salesforce field.
 *
 * @param Salesforce $sfapi
 *   A Salesforce API object
 * @param String $sf_object
 *   The type of Salesforce object that has the field
 * @param String $sf_field
 *   The field you're looking for information about
 *
 * @return Bool
 *   The value of idLookup as provided by Salesforce
 */
function _sfw_salesforce_field_can_dedupe(Salesforce $sfapi, $sf_object, $sf_field) {
  if (empty($sf_object) || empty($sf_field)) {
    return FALSE;
  }
  $object_info = $sfapi->objectDescribe($sf_object);
  // Find the field.
  foreach ($object_info['fields'] as $field) {
    if ($field['name'] == $sf_field) {
      return $field['idLookup'];
    }
  }
}

/**
 * Find out if the field's value must be unique in the Salesforce database.
 *
 * @param Salesforce $sfapi
 *   A Salesforce API object
 * @param String $sf_object
 *   The type of Salesforce object that has the field
 * @param String $sf_field
 *   The field you're looking for information about
 *
 * @return Bool
 *   The value of as provided by Salesforce
 */
function _sfw_salesforce_field_is_unique(Salesforce $sfapi, $sf_object, $sf_field) {
  if (empty($sf_object) || empty($sf_field)) {
    return FALSE;
  }
  $object_info = $sfapi->objectDescribe($sf_object);
  // Find the field.
  foreach ($object_info['fields'] as $field) {
    if ($field['name'] == $sf_field) {
      return $field['unique'];
    }
  }
}

/**
 * @} form_helper
 */
