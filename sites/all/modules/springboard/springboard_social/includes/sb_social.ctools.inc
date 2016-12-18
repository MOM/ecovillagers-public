<?php

/**
 * @file
 * Chaos tools hooks.
 */

/**
 * Implements hook_ctools_plugin_directory().
 */
function sb_social_ctools_plugin_directory($owner, $plugin_type) {
  if ($owner = 'sb_social') {
    return "plugins/$plugin_type";
  }
}

/**
 * Implements hook_ctools_plugin_type().
 */
function sb_social_ctools_plugin_type() {
  $plugins['social_networks'] = array(
    'load themes' => TRUE,
  );
  return $plugins;
}
