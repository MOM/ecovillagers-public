<?php
/**
 * @file
 * ecovillagers_ia.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ecovillagers_ia_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access comments'.
  $permissions['access comments'] = array(
    'name' => 'access comments',
    'roles' => array(),
    'module' => 'comment',
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

  // Exported permission: 'access content overview'.
  $permissions['access content overview'] = array(
    'name' => 'access content overview',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'access private fields'.
  $permissions['access private fields'] = array(
    'name' => 'access private fields',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'access service links'.
  $permissions['access service links'] = array(
    'name' => 'access service links',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'service_links',
  );

  // Exported permission: 'administer content types'.
  $permissions['administer content types'] = array(
    'name' => 'administer content types',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'administer field permissions'.
  $permissions['administer field permissions'] = array(
    'name' => 'administer field permissions',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'administer nodes'.
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'bypass node access'.
  $permissions['bypass node access'] = array(
    'name' => 'bypass node access',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'create inspiration content'.
  $permissions['create inspiration content'] = array(
    'name' => 'create inspiration content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'create overview content'.
  $permissions['create overview content'] = array(
    'name' => 'create overview content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any inspiration content'.
  $permissions['delete any inspiration content'] = array(
    'name' => 'delete any inspiration content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any overview content'.
  $permissions['delete any overview content'] = array(
    'name' => 'delete any overview content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own inspiration content'.
  $permissions['delete own inspiration content'] = array(
    'name' => 'delete own inspiration content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own overview content'.
  $permissions['delete own overview content'] = array(
    'name' => 'delete own overview content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete revisions'.
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any inspiration content'.
  $permissions['edit any inspiration content'] = array(
    'name' => 'edit any inspiration content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any overview content'.
  $permissions['edit any overview content'] = array(
    'name' => 'edit any overview content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own comments'.
  $permissions['edit own comments'] = array(
    'name' => 'edit own comments',
    'roles' => array(),
    'module' => 'comment',
  );

  // Exported permission: 'edit own inspiration content'.
  $permissions['edit own inspiration content'] = array(
    'name' => 'edit own inspiration content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own overview content'.
  $permissions['edit own overview content'] = array(
    'name' => 'edit own overview content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'manage Shorten URLs API keys'.
  $permissions['manage Shorten URLs API keys'] = array(
    'name' => 'manage Shorten URLs API keys',
    'roles' => array(),
    'module' => 'shorten',
  );

  // Exported permission: 'post comments'.
  $permissions['post comments'] = array(
    'name' => 'post comments',
    'roles' => array(),
    'module' => 'comment',
  );

  // Exported permission: 'revert revisions'.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'skip comment approval'.
  $permissions['skip comment approval'] = array(
    'name' => 'skip comment approval',
    'roles' => array(),
    'module' => 'comment',
  );

  // Exported permission: 'use PHP for service visibility'.
  $permissions['use PHP for service visibility'] = array(
    'name' => 'use PHP for service visibility',
    'roles' => array(),
    'module' => 'service_links',
  );

  // Exported permission: 'use Shorten URLs page'.
  $permissions['use Shorten URLs page'] = array(
    'name' => 'use Shorten URLs page',
    'roles' => array(),
    'module' => 'shorten',
  );

  // Exported permission: 'view own unpublished content'.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'view revisions'.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(),
    'module' => 'node',
  );

  return $permissions;
}
