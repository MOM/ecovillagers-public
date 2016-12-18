<?php
/**
 * @file
 * Functions to define default user roles and permissions for Springboard.
 */

/**
 * Initial user roles.
 */
function springboard_user_roles() {
  $roles = array();

  $role = new stdClass();
  $role->name = 'Administrator';
  $role->weight = 1;
  $roles[] = $role;

  $role = new stdClass();
  $role->name = 'Springboard administrator';
  $role->weight = 2;
  $roles[] = $role;

  $role = new stdClass();
  $role->name = 'Springboard editor';
  $role->weight = 3;
  $roles[] = $role;

  return $roles;
}

/**
 * Initial user permissions.
 */
function springboard_user_permissions() {

  $permissions = array();

  // Exported permission: 'access administration pages'.
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access all webform results'.
  $permissions['access all webform results'] = array(
    'name' => 'access all webform results',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'access content'.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access contextual links'.
  $permissions['access contextual links'] = array(
    'name' => 'access contextual links',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'contextual',
  );

  // Exported permission: 'access own webform results'.
  $permissions['access own webform results'] = array(
    'name' => 'access own webform results',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'access own webform submissions'.
  $permissions['access own webform submissions'] = array(
    'name' => 'access own webform submissions',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'access site in maintenance mode'.
  $permissions['access site in maintenance mode'] = array(
    'name' => 'access site in maintenance mode',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access site reports'.
  $permissions['access site reports'] = array(
    'name' => 'access site reports',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access springboard dashboard'.
  $permissions['access springboard dashboard'] = array(
    'name' => 'access springboard dashboard',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'springboard',
  );

  // Exported permission: 'access springboard version'.
  $permissions['access springboard version'] = array(
    'name' => 'access springboard version',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'springboard_version',
  );

  // Exported permission: 'access user profiles'.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer fundraiser'.
  $permissions['administer fundraiser'] = array(
    'name' => 'administer fundraiser',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'fundraiser',
  );

  // Exported permission: 'administer google analytics'.
  $permissions['administer google analytics'] = array(
    'name' => 'administer google analytics',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'googleanalytics',
  );

  // Exported permission: 'administer page wrappers'.
  $permissions['administer page wrappers'] = array(
    'name' => 'administer page wrappers',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'page_wrappers',
  );

  // Exported permission: 'administer salesforce mapping'.
  $permissions['administer salesforce mapping'] = array(
    'name' => 'administer salesforce mapping',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'salesforce_mapping',
  );

  // Exported permission: 'administer salesforce npsp'.
  $permissions['administer salesforce npsp'] = array(
    'name' => 'administer salesforce npsp',
    'roles' => array('Springboard administrator' => 'Springboard administrator'),
    'module' => 'salesforce_npsp',
  );

  // Exported permission: 'administer secure pre-populate'.
  $permissions['administer secure pre-populate'] = array(
    'name' => 'administer secure pre-populate',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'secure_prepopulate',
  );

  // Exported permission: 'administer springboard'.
  $permissions['administer springboard'] = array(
    'name' => 'administer springboard',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'springboard',
  );

  // Exported permission: 'administer springboard dashboard'.
  $permissions['administer springboard dashboard'] = array(
    'name' => 'administer springboard dashboard',
    'roles' => array('Springboard administrator' => 'Springboard administrator'),
    'module' => 'springboard',
  );

  // Exported permission: 'administer springboard theme'.
  $permissions['administer springboard theme'] = array(
    'name' => 'administer springboard theme',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'springboard_admin',
  );

  // Exported permission: 'assign user roles'.
  $permissions['assign user roles'] = array(
    'name' => 'assign user roles',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'springboard_admin',
  );

  // Exported permission: 'administer user map'.
  $permissions['administer user map'] = array(
    'name' => 'administer user map',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'webform_user',
  );

  // Exported permission: 'administer webform_ab'.
  $permissions['administer webform_ab'] = array(
    'name' => 'administer webform_ab',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'webform_ab',
  );

  // Exported permission: 'administer webform goals'.
  $permissions['administer webform goals'] = array(
    'name' => 'administer webform goals',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'webform_goals',
  );

  // Exported permission: 'administrate recurring donations'.
  $permissions['administrate recurring donations'] = array(
    'name' => 'administrate recurring donations',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'fundraiser_sustainers',
  );

  // Exported permission: 'alter webform components'.
  $permissions['alter webform components'] = array(
    'name' => 'alter webform components',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'webform_user',
  );

  // Exported permission: 'bypass node access'.
  $permissions['bypass node access'] = array(
    'name' => 'bypass node access',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'cancel future donations'.
  $permissions['cancel future donations'] = array(
    'name' => 'cancel future donations',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'fundraiser_sustainers',
  );

  // Exported permission: 'clone donation form'.
  $permissions['clone donation form'] = array(
    'name' => 'clone donation form',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'fundraiser',
  );

  // Exported permission: 'clone node'.
  $permissions['clone node'] = array(
    'name' => 'clone node',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'clone',
  );

  // Exported permission: 'clone own nodes'.
  $permissions['clone own nodes'] = array(
    'name' => 'clone own nodes',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'clone',
  );

  // Exported permission: 'configure webform emails'.
  $permissions['configure webform emails'] = array(
    'name' => 'configure webform emails',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'webform_user',
  );

  // Exported permission: 'configure webform settings'.
  $permissions['configure webform settings'] = array(
    'name' => 'configure webform settings',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'webform_user',
  );

  // Exported permission: 'create donation form'.
  $permissions['create donation form'] = array(
    'name' => 'create donation form',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'fundraiser',
  );

  // Exported permission: 'create donation_form content'.
  $permissions['create donation_form content'] = array(
    'name' => 'create donation_form content',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create email_wrapper content'.
  $permissions['create email_wrapper content'] = array(
    'name' => 'create email_wrapper content',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create page_wrapper content'.
  $permissions['create page_wrapper content'] = array(
    'name' => 'create page_wrapper content',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create url aliases'.
  $permissions['create url aliases'] = array(
    'name' => 'create url aliases',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'path',
  );

  // Exported permission: 'create webform content'.
  $permissions['create webform content'] = array(
    'name' => 'create webform content',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create webform_ab'.
  $permissions['create webform_ab'] = array(
    'name' => 'create webform_ab',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'webform_ab',
  );

  // Exported permission: 'create webform_ab content'.
  $permissions['create webform_ab content'] = array(
    'name' => 'create webform_ab content',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete all webform submissions'.
  $permissions['delete all webform submissions'] = array(
    'name' => 'delete all webform submissions',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'delete any donation form'.
  $permissions['delete any donation form'] = array(
    'name' => 'delete any donation form',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'fundraiser',
  );

  // Exported permission: 'delete any donation_form content'.
  $permissions['delete any donation_form content'] = array(
    'name' => 'delete any donation_form content',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any email_wrapper content'.
  $permissions['delete any email_wrapper content'] = array(
    'name' => 'delete any email_wrapper content',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any page_wrapper content'.
  $permissions['delete any page_wrapper content'] = array(
    'name' => 'delete any page_wrapper content',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any webform content'.
  $permissions['delete any webform content'] = array(
    'name' => 'delete any webform content',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any webform_ab'.
  $permissions['delete any webform_ab'] = array(
    'name' => 'delete any webform_ab',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'webform_ab',
  );

  // Exported permission: 'delete any webform_ab content'.
  $permissions['delete any webform_ab content'] = array(
    'name' => 'delete any webform_ab content',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own donation form'.
  $permissions['delete own donation form'] = array(
    'name' => 'delete own donation form',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'fundraiser',
  );

  // Exported permission: 'delete own donation_form content'.
  $permissions['delete own donation_form content'] = array(
    'name' => 'delete own donation_form content',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own email_wrapper content'.
  $permissions['delete own email_wrapper content'] = array(
    'name' => 'delete own email_wrapper content',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own page_wrapper content'.
  $permissions['delete own page_wrapper content'] = array(
    'name' => 'delete own page_wrapper content',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own webform content'.
  $permissions['delete own webform content'] = array(
    'name' => 'delete own webform content',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own webform submissions'.
  $permissions['delete own webform submissions'] = array(
    'name' => 'delete own webform submissions',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'delete own webform_ab'.
  $permissions['delete own webform_ab'] = array(
    'name' => 'delete own webform_ab',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'webform_ab',
  );

  // Exported permission: 'delete own webform_ab content'.
  $permissions['delete own webform_ab content'] = array(
    'name' => 'delete own webform_ab content',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit all webform submissions'.
  $permissions['edit all webform submissions'] = array(
    'name' => 'edit all webform submissions',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'edit any donation form'.
  $permissions['edit any donation form'] = array(
    'name' => 'edit any donation form',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'fundraiser',
  );

  // Exported permission: 'edit any donation_form content'.
  $permissions['edit any donation_form content'] = array(
    'name' => 'edit any donation_form content',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any email_wrapper content'.
  $permissions['edit any email_wrapper content'] = array(
    'name' => 'edit any email_wrapper content',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any page_wrapper content'.
  $permissions['edit any page_wrapper content'] = array(
    'name' => 'edit any page_wrapper content',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any webform content'.
  $permissions['edit any webform content'] = array(
    'name' => 'edit any webform content',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any webform_ab'.
  $permissions['edit any webform_ab'] = array(
    'name' => 'edit any webform_ab',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'webform_ab',
  );

  // Exported permission: 'edit any webform_ab content'.
  $permissions['edit any webform_ab content'] = array(
    'name' => 'edit any webform_ab content',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own donation form'.
  $permissions['edit own donation form'] = array(
    'name' => 'edit own donation form',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'fundraiser',
  );

  // Exported permission: 'edit own donation_form content'.
  $permissions['edit own donation_form content'] = array(
    'name' => 'edit own donation_form content',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own email_wrapper content'.
  $permissions['edit own email_wrapper content'] = array(
    'name' => 'edit own email_wrapper content',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own page_wrapper content'.
  $permissions['edit own page_wrapper content'] = array(
    'name' => 'edit own page_wrapper content',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own webform content'.
  $permissions['edit own webform content'] = array(
    'name' => 'edit own webform content',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own webform submissions'.
  $permissions['edit own webform submissions'] = array(
    'name' => 'edit own webform submissions',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'edit own webform_ab'.
  $permissions['edit own webform_ab'] = array(
    'name' => 'edit own webform_ab',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'webform_ab',
  );

  // Exported permission: 'edit own webform_ab content'.
  $permissions['edit own webform_ab content'] = array(
    'name' => 'edit own webform_ab content',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'manage currencies'.
  $permissions['manage currencies'] = array(
    'name' => 'manage currencies',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'fundraiser_multi_currency',
  );

  // Exported permission: 'manage webform goals'.
  $permissions['manage webform goals'] = array(
    'name' => 'manage webform goals',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'webform_goals',
  );

  // Exported permission: 'map salesforce objects'.
  $permissions['map salesforce objects'] = array(
    'name' => 'map salesforce objects',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'salesforce_genmap',
  );

  // Exported permission: 'map salesforce to donation'.
  $permissions['map salesforce to donation'] = array(
    'name' => 'map salesforce to donation',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'salesforce_donation',
  );

  // Exported permission: 'map salesforce to webform'.
  $permissions['map salesforce to webform'] = array(
    'name' => 'map salesforce to webform',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'salesforce_genmap',
  );

  // Exported permission: 'opt-in or out of tracking'.
  $permissions['opt-in or out of tracking'] = array(
    'name' => 'opt-in or out of tracking',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'googleanalytics',
  );

  // Exported permission: 'refund donations'.
  $permissions['refund donations'] = array(
    'name' => 'refund donations',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'fundraiser',
  );

  // Exported permission: 'reset webform_ab test data'.
  $permissions['reset webform_ab test data'] = array(
    'name' => 'reset webform_ab test data',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'webform_ab',
  );

  // Exported permission: 'use PHP for tracking visibility'.
  $permissions['use PHP for tracking visibility'] = array(
    'name' => 'use PHP for tracking visibility',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'googleanalytics',
  );

  // Exported permission: 'use gateway switcher'.
  $permissions['use gateway switcher'] = array(
    'name' => 'use gateway switcher',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'fundraiser',
  );

  // Exported permission: 'use text format filtered_html'.
  $permissions['use text format filtered_html'] = array(
    'name' => 'use text format filtered_html',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format full_html'.
  $permissions['use text format full_html'] = array(
    'name' => 'use text format full_html',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'view any commerce_order entity'.
  $permissions['view any commerce_order entity'] = array(
    'name' => 'view any commerce_order entity',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'commerce_order',
  );

  // Exported permission: 'view any webform_ab reports'.
  $permissions['view any webform_ab reports'] = array(
    'name' => 'view any webform_ab reports',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'webform_ab',
  );

  // Exported permission: 'view own webform_ab reports'.
  $permissions['view own webform_ab reports'] = array(
    'name' => 'view own webform_ab reports',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'webform_ab',
  );

  // Exported permission: 'view payments'.
  $permissions['view payments'] = array(
    'name' => 'view payments',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'commerce_payment',
  );

  // Exported permission: 'view salesforce batch logs'.
  $permissions['view salesforce batch logs'] = array(
    'name' => 'view salesforce batch logs',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'salesforce_log',
  );

  // Exported permission: 'view salesforce mapping'.
  $permissions['view salesforce mapping'] = array(
    'name' => 'view salesforce mapping',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'salesforce_mapping',
  );

  // Exported permission: 'view the administration theme'.
  $permissions['view the administration theme'] = array(
    'name' => 'view the administration theme',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
      'Springboard editor' => 'Springboard editor',
    ),
    'module' => 'system',
  );

  $permissions['allow node-specific ticket deletion'] = array(
    'name' => 'allow node-specific ticket deletion',
    'roles' => array(
      'Springboard administrator' => 'Springboard administrator',
    ),
    'module' => 'fundraiser_tickets',
  );

  return $permissions;
}
