<?php
/**
 * @file
 * Administration page callbacks for the webform_dupe_cop module.
 */

/**
 * Admin settings form.
 */
function webform_ui_settings_form($form, &$form_state) {

  $form['webform_ui_submit_on_edit'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add a field to set the submit button text to the node add/edit form'),
    '#default_value' => variable_get('webform_ui_submit_on_edit', 'FALSE'),
    '#description' => t('The submit button text field is normally hidden deep in the form components settings page. This option allows it to appear on the node edit form.'),
    '#weight' => 1,
  );

  $form['webform_ui_collapse_filter'] = array(
    '#type' => 'checkbox',
    '#title' => t('Wrap the body field on node add/edit forms in a fieldset and collapse the filter format fieldset'),
    '#default_value' => variable_get('webform_ui_collapse_filter', 'FALSE'),
    '#description' => t('Collapse filter format fieldsets on the node add/edit page in order to save space.'),
    '#weight' => 2,
  );

  $form['webform_ui_hide_hidden'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide fields of the type "hidden" on the webform components administration page'),
    '#default_value' => variable_get('webform_ui_hide_hidden', 'FALSE'),
    '#description' => t('Hide rarely edited hidden fields by default. A "show" link will allow you to toggle field visibility.'),
    '#weight' => 3,
  );

  $form['webform_ui_confirmation_page'] = array(
    '#type' => 'checkbox',
    '#title' => t('Clean up "Confirmation page & settings" UI'),
    '#default_value' => variable_get('webform_ui_confirmation_page', 'FALSE'),
    '#description' => 'Wrap "Confirmation page & settings" page options in fieldsets, and collapse them by default.',
    '#weight' => 4,
  );

  $form['webform_ui_use_alternate_submission'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use an alternate submission results page with pager and search functionality'),
    '#default_value' => variable_get('webform_ui_use_alternate_submission', 'FALSE'),
    '#description' => '',
    '#weight' => 5,
  );

  $form['webform_ui_use_bulk_delete'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show the bulk delete option on the results page'),
    '#default_value' => variable_get('webform_ui_use_bulk_delete', 'FALSE'),
    '#description' => '',
    '#states' => array(
      'visible' => array(
        ':input[name="webform_ui_use_alternate_submission"]' => array('checked' => TRUE),
      ),
    ),
    '#attributes' => array('style' => 'margin-left: 15px'),
    '#weight' => 6,
  );


  $form['webform_ui_hide_table'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide the "Table" tab on the submissions results page'),
    '#default_value' => variable_get('webform_ui_hide_table', 'FALSE'),
    '#description' => t("If you have many submissions, the table page will require extensive resources to load. If you don't need this feature, hide the tab."),
    '#weight' => 7,
  );

  $form['webform_ui_hide_clear_all'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide the "Clear" tab'),
    '#default_value' => variable_get('webform_ui_hide_clear_all', 'FALSE'),
    '#description' => t("Prevent access to the mass delete feature on the submission results page."),
    '#weight' => 8,
  );

  $form['webform_ui_make_hidden_editable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Make hidden fields editable on the submission result edit page.'),
    '#default_value' => variable_get('webform_ui_make_hidden_editable', 'FALSE'),
    '#description' => t("Make market source and other hidden fields editable in order to correct salesforce sync errors."),
    '#weight' => 8,
  );

  $form['#submit'][] = 'webform_ui_settings_form_submit';
  return system_settings_form($form);
}

function webform_ui_settings_form_submit($form, $form_state) {
  variable_set('menu_rebuild_needed', TRUE);
}

