<?php
/**
 * @file
 * springboard_p2p.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function springboard_p2p_user_default_roles() {
  $roles = array();

  // Exported role: Springboard P2P campaigner.
  $roles['Springboard P2P campaigner'] = array(
    'name' => 'Springboard P2P campaigner',
    'weight' => 4,
  );

  return $roles;
}
