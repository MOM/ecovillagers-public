<?php
/**
 * @file
 * springboard_p2p_webform_confirmation.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function springboard_p2p_webform_confirmation_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'pm_existing_pages_p2p_webform_confirmation_panel_context';
  $handler->task = 'pm_existing_pages';
  $handler->subtask = 'p2p_webform_confirmation';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'P2P Donation Confirmation Page',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => 'p2p-page-type',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'logic' => 'and',
      'plugins' => array(
        0 => array(
          'name' => 'donation_thank_you',
          'settings' => NULL,
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
    ),
  );
  $display = new panels_display();
  $display->layout = 'p2p_landing_twocol_bricks';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'top' => NULL,
      'middle_left' => NULL,
      'middle_right' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '78059b1d-cc5a-49a3-9d54-57685c7f82f5';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-bcec0694-5531-400c-8d05-d7521fb72c98';
    $pane->panel = 'top';
    $pane->type = 'campaign_header_no_context';
    $pane->subtype = 'campaign_header_no_context';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'bcec0694-5531-400c-8d05-d7521fb72c98';
    $display->content['new-bcec0694-5531-400c-8d05-d7521fb72c98'] = $pane;
    $display->panels['top'][0] = 'new-bcec0694-5531-400c-8d05-d7521fb72c98';
    $pane = new stdClass();
    $pane->pid = 'new-12ef7582-b921-4b36-a1d8-4092c1de8cb0';
    $pane->panel = 'top';
    $pane->type = 'pm_existing_pages';
    $pane->subtype = 'pm_existing_pages';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      0 => 'task_id',
      1 => 'pane_title_from_menu',
      'task_id' => 'node_overview',
      'pane_title_from_menu' => 1,
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '12ef7582-b921-4b36-a1d8-4092c1de8cb0';
    $display->content['new-12ef7582-b921-4b36-a1d8-4092c1de8cb0'] = $pane;
    $display->panels['top'][1] = 'new-12ef7582-b921-4b36-a1d8-4092c1de8cb0';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-12ef7582-b921-4b36-a1d8-4092c1de8cb0';
  $handler->conf['display'] = $display;
  $export['pm_existing_pages_p2p_webform_confirmation_panel_context'] = $handler;

  return $export;
}
