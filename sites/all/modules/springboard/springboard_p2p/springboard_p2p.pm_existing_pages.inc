<?php
/**
 * @file
 * springboard_p2p.pm_existing_pages.inc
 */

/**
 * Implements hook_pm_existing_pages_info().
 */
function springboard_p2p_pm_existing_pages_info() {
  $export = array();

  $pm_existing_page = new stdClass();
  $pm_existing_page->api_version = 1;
  $pm_existing_page->name = 'p2p_node';
  $pm_existing_page->label = 'P2P Node';
  $pm_existing_page->context = 'entity|node|nid';
  $pm_existing_page->paths = 'node';
  $export['p2p_node'] = $pm_existing_page;

  return $export;
}
