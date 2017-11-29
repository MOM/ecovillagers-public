<?php

/**
 * @file
 * Defines the inline entity form controller for Commerce Line Items.
 */

class PageWrappersFileInlineEntityFormController extends EntityInlineEntityFormController {

  public function tableFields($bundles) {
    $fields['field_pw_asset_title'] = array(
      'type' => 'field',
      'label' => t('Title'),
      'formatter' => 'text_default',
      'weight' => 0,
    );
    $fields['owner'] = array(
      'type' => 'property',
      'label' => t('Owner'),
      'formatter' => 'text_default',
      'weight' => 1,
    );
    $fields['url'] = array(
      'type' => 'property',
      'label' => t('File Location'),
      'formatter' => 'text_default'
    );
    $fields['updated_time'] = array(
      'type' => 'callback',
      'label' => t('Last Updated'),
      'render_callback' => 'page_wrappers_ief_date_callback',
      'weight' => 2,
    );
    return $fields;
  }

  /**
   * Overrides EntityInlineEntityFormController::tableFields().
   */
  public function entityForm($entity_form, &$form_state) {
    $bundle = file_type_load($entity_form['#entity']->type);

    $file = $entity_form['#entity'];
    $file_extensions = file_type_get_valid_extensions($bundle);
    $options = array(
      'file_extensions' => implode(' ', $file_extensions),
    );

    module_load_include('inc', 'file_entity', 'file_entity.pages');
    if(isset($file->is_new)) {
      $entity_form['upload'] = array(
        '#type' => 'managed_file',
        '#title' => t('Upload a new file'),
        '#upload_location' => file_entity_upload_destination_uri($options),
        '#upload_validators' => file_entity_get_upload_validators($options),
        '#progress_indicator' => 'bar',
        '#required' => TRUE,
        '#pre_render' => array('file_managed_file_pre_render', 'file_entity_upload_validators_pre_render'),
        '#default_value' => NULL,
        '#weight' => -1,
      );
    }
    else {
      $file_form = file_entity_metadata_form_file($file);
      $entity_form['replace_upload'] = array(
        '#type' => 'file',
        '#title' => t('Replace file'),
        '#upload_location' => file_directory_temp(),
        '#upload_validators' => file_entity_get_upload_validators($options),
        '#progress_indicator' => 'bar',
        '#required' => FALSE,
        '#pre_render' => array('file_managed_file_pre_render', 'file_entity_upload_validators_pre_render'),
        '#default_value' => NULL,
        '#description' => t('This will replace the exiting file. This cannot be undone and may affect other page wrappers.'),
        '#weight' => -1,
      );
    }

    field_attach_form('file', $file, $entity_form, $form_state);

    return $entity_form;
  }

  /**
   * Overrides EntityInlineEntityFormController::settingsForm().
   */
  public function settingsForm($field, $instance) {
    $form = parent::settingsForm($field, $instance);

    // Adding existing entities is not supported for line items.
    $form['allow_existing']['#access'] = TRUE;

    return $form;
  }

  public function entityFormValidate($entity_form, &$form_state) {
    // Handle the replacement file if uploaded.
    if (isset($entity_form['replace_upload']['#value'])) {
      // Save the file as a temporary file.
      $file = file_save_upload($entity_form['#array_parents'][0], $entity_form['replace_upload']['#upload_validators']);
      if (!empty($file)) {
        // Put the temporary file in form_values so we can save it on submit.
        $form_state['replace_upload']['#file'] = $file;
      }
      elseif ($file === FALSE) {
        // File uploaded failed.
        form_set_error('replace_upload', t('The replacement file could not be uploaded.'));
      }
    }
    parent::entityFormValidate($entity_form, $form_state);
  }

  public function entityFormSubmit(&$entity_form, &$form_state) {
    // The Drupal core 'managed file' is already created when the file
    // is originally uploaded. The file entity associated with that managed
    // file will use the same file ID (fid) as its entity ID. Creating a "new"
    // file entity, then, is really just updating the fields
    // related to the entity ID already created in the file_managed table.
    $entity = false;
    if (isset($entity_form['upload']['#file'])) {
      // Replace the generic "new" entity object with the actual file entity.
      $entity = $entity_form['upload']['#file'];
      // Load the existing entity's field values
      $entity_values = (array) $entity_form['#entity'];
      // Reset the entity type to match the field settings.
      $entity->type = $entity_values['type'];
      foreach ($entity_values as $key => $values) {
        if (preg_match('/^field_?/', $key)) {
          $entity->$key = $values;
        }
      }
    }
    // If the file entity is being edited, we have to work around the core
    // File management a little to update the existing file entity rather than
    // creating a new one. Mostly copied from file_entity_edit_submit().
    elseif (isset($form_state['replace_upload']['#file'])) {
      $entity = $entity_form['#entity'];
      $replacement = $form_state['replace_upload']['#file'];
      // If the replacement file as the same name as the existing file,
      // set $replace to TRUE. Otherwise we will rename the
      // file in the case that any other files exist with the same name.
      $replace = FALSE;
      $real_filename = preg_replace("/^public:\/\/.*\//", "", $entity->uri);
      $replacement_filename = page_wrappers_filename_without_txt($replacement->filename);
      if ($replacement_filename == $real_filename) {
        $replace = TRUE;
      }
      // Move file from temp to permanent home.
      $replacement = page_wrappers_relocate_file($replacement, $replace);
      // $replacement = file_move($replacement, $destination_uri, ($destination_uri == $entity->uri ? FILE_EXISTS_REPLACE : FILE_EXISTS_RENAME));
      if (is_object($replacement)) {

        // If the uri target has changed, we have to jump through some
        // hoops to keep the same FID. We need the same FID so that
        // this update applies to all page wrappers referencing this file.
        if ($replacement->uri != $entity->uri) {
          // Switch the referenced entity to point to the new file,
          // then change the FID to match the existing reference.
          $fid = $entity->fid;
          $replacement_fid = $replacement->fid;
          $old_uri = $entity->uri;
          $entity = $replacement;
          $entity->fid = $fid;
          // Delete the old file.
          // @TODO when we add revisioning, we will need to keep the old file and make a record of when it was used.
          file_unmanaged_delete($old_uri);
          // Delete the database entry for the "new" file entity.
          db_delete('file_managed')
            ->condition('fid', $replacement_fid)
            ->execute();
        }
      }
    }
    if ($entity) {
      // Publish the file.
      $entity->status = 1;
      $entity_form['#entity'] = $entity;
    }
    parent::entityFormSubmit($entity_form, $form_state);
  }
}
