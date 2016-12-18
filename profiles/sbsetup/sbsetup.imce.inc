<?php
/**
 * @file
 * Creates the default configuration profiles.
 */

include_once drupal_get_path('module', 'imce') . '/inc/imce.core.profiles.inc';

/**
 * Create core profiles.
 */
function sbsetup_imce_install_profiles() {
  $profiles = variable_get('imce_profiles', array());
  $profiles[] = sbsetup_imce_sbadmin_profile();
  variable_set('imce_profiles', $profiles);
  $roles = user_roles();
  $scheme = variable_get('file_default_scheme', 'public');
  $roles_profiles = variable_get('imce_roles_profiles', array());
  $count = count($profiles);
  foreach ($roles as $rid => $role) {
    if (in_array($role, array(
      'Administrator',
      'Springboard editor',
      'Springboard administrator',
    ))) {
      $roles_profiles[$rid][$scheme . '_pid'] = $count;
    }
  }
  variable_set('imce_roles_profiles', $roles_profiles);
  return TRUE;
}

/**
 * User1's profile.
 */
function sbsetup_imce_sbadmin_profile() {
  return imce_construct_profile('Springboard Administration', 1, 0, 0, 0, '*', '1200x1200', 0,
    array(
      array(
        '.',
        1,
        1,
        1,
        1,
        1,
        1,
      ),
    ),
    array(
      array(
        'Small',
        '90x90',
        'small_',
        '',
      ),
      array(
        'Medium',
        '120x120',
        'medium_',
        '',
      ),
      array(
        'Large',
        '180x180',
        'large_',
        '',
      ),
    )
  );
}
