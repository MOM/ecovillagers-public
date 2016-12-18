<?php
/**
 * @file
 * springboard_p2p_category.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function springboard_p2p_category_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function springboard_p2p_category_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function springboard_p2p_category_node_info() {
  $items = array(
    'p2p_category' => array(
      'name' => t('Peer to Peer Category'),
      'base' => 'node_content',
      'description' => t('A peer to peer category.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => t('Peer to peer category submission guidelines.'),
    ),
  );
  return $items;
}
