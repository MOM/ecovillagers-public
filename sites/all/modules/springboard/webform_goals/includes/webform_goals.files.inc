<?php

/**
 * @file file handling functions.
 */
/**
 * Returns the path to where all page wrapper files are stored.
 */
function _webform_goals_base_path() {
  return drupal_realpath(file_default_scheme() . '://') . '/webform_goals';
}

function _webform_goals_file_insert($goal, $data) {
  $path = _webform_goals_base_path();
  $uri = $path . '/template-' . $goal['gid'] . '.txt';
  if (file_prepare_directory($path, FILE_CREATE_DIRECTORY)) {
    if (!file_unmanaged_save_data($data, $uri, FILE_EXISTS_REPLACE)) {
      drupal_set_message(t('Unable to save the template file, please check folder permissions.'), 'error');
      watchdog('webform_goals', t('There was a problem writing a goal template file. Check directory permissions.'), array(), WATCHDOG_ERROR);
    }
    else {
      drupal_set_message('Widget file saved.');
    }
  }
  else {
    drupal_set_message(t('The webform_goals folder either does not exist or cannot be written to.'), 'error');
    watchdog('webform_goals', t('The webform_goals folder either does not exist or cannot be written to.'), array(), WATCHDOG_ERROR);
  }

}
