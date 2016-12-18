<?php
/**
 * @file
 * Admin settings forms.
 */

/**
 * Admin settings form.
 */
function email_wrappers_admin() {
  $form = array();
  $form['email_wrappers_og_filter'] = array(
    '#type' => 'checkbox',
    '#title' => t('Limit templates by group.'),
    '#description' => t('Use OG group membership to resitrict available confirmation templates. When this is enabled content editors will only see email templates assigned to groups they are members of when creating or editing donation forms.'),
    '#default_value' => variable_get('email_wrappers_og_filter', 0),
  );

  if (!module_exists('og')) {
    $form['email_wrappers_og_filter']['#disabled'] = TRUE;
    $form['email_wrappers_og_filter']['#description'] .= t('%message', array('%message' => 'This feature is disabled because Organic Groups is not installed.'));
  }

  return system_settings_form($form);
}
