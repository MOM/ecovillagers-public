<?php

/**
 * Create the page wrapper node type.
 */
function _page_wrappers_create_node_type() {
  // Implement node type.
  $t = get_t();

  if (!in_array('page_wrapper', node_type_get_names())) {
    $type = array(
      'type' => 'page_wrapper',
      'name' => 'Page Wrapper',
      'description' => $t('Allows a user to define custom page templates that can then be assigned to specific nodes.'),
      'base' => 'node_content',
      'custom' => 1,
      'modified' => 1,
      'locked' => 0,
      'title_label' => $t('Internal Title'),
      'node_submitted' => 0,
    );
    $type = node_type_set_defaults($type);
    node_type_save($type);
  }
}


/**
 * Delete the page wrapper nodes.
 */
function _page_wrappers_delete_nodes() {
  require_once 'page_wrappers.module';
  $nids = page_wrappers_get_nodes();
  node_delete_multiple($nids);
  drupal_set_message(t('Page Wrappers have been deleted.'));
}
