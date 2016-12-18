<?php
/**
 * @file
 * springboard_p2p_landing.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function springboard_p2p_landing_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__p2p_campaign_landing';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '0',
        ),
        'path' => array(
          'weight' => '6',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__p2p_campaign_landing'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_p2p_campaign_landing';
  $strongarm->value = array();
  $export['menu_options_p2p_campaign_landing'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_p2p_campaign_landing';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_p2p_campaign_landing'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_p2p_campaign_landing';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_p2p_campaign_landing'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_p2p_campaign_landing';
  $strongarm->value = '0';
  $export['node_preview_p2p_campaign_landing'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_p2p_campaign_landing';
  $strongarm->value = 0;
  $export['node_submitted_p2p_campaign_landing'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_node_p2p_campaign_landing';
  $strongarm->value = array(
    'status' => 1,
    'view modes' => array(
      'page_manager' => array(
        'status' => 1,
        'default' => 1,
        'default display' => 'node:p2p_campaign_landing:default',
        'choice' => 0,
      ),
      'default' => array(
        'status' => 0,
        'default' => 0,
        'default display' => 0,
        'choice' => 0,
      ),
      'teaser' => array(
        'status' => 0,
        'default' => 0,
        'default display' => 0,
        'choice' => 0,
      ),
    ),
  );
  $export['panelizer_defaults_node_p2p_campaign_landing'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:p2p_campaign_landing:default_selection';
  $strongarm->value = 'node:p2p_campaign_landing:default:default';
  $export['panelizer_node:p2p_campaign_landing:default_selection'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:p2p_campaign_landing:page_manager_selection';
  $strongarm->value = 'node:p2p_campaign_landing:default';
  $export['panelizer_node:p2p_campaign_landing:page_manager_selection'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:p2p_campaign_landing_allowed_layouts';
  $strongarm->value = 'O:22:"panels_allowed_layouts":4:{s:9:"allow_new";b:1;s:11:"module_name";s:35:"panelizer_node:p2p_campaign_landing";s:23:"allowed_layout_settings";a:9:{s:8:"flexible";b:1;s:14:"twocol_stacked";b:1;s:13:"twocol_bricks";b:1;s:6:"twocol";b:1;s:25:"threecol_33_34_33_stacked";b:1;s:17:"threecol_33_34_33";b:1;s:25:"threecol_25_50_25_stacked";b:1;s:17:"threecol_25_50_25";b:1;s:6:"onecol";b:1;}s:10:"form_state";N;}';
  $export['panelizer_node:p2p_campaign_landing_allowed_layouts'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:p2p_campaign_landing_allowed_layouts_default';
  $strongarm->value = 1;
  $export['panelizer_node:p2p_campaign_landing_allowed_layouts_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:p2p_campaign_landing_allowed_types_default';
  $strongarm->value = 1;
  $export['panelizer_node:p2p_campaign_landing_allowed_types_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:p2p_campaign_landing_default';
  $strongarm->value = array(
    'token' => 'token',
    'entity_form_field' => 'entity_form_field',
    'entity_field' => 'entity_field',
    'entity_field_extra' => 'entity_field_extra',
    'custom' => 'custom',
    'block' => 'block',
    'entity_view' => 'entity_view',
    'panels_mini' => 'panels_mini',
    'other' => 'other',
  );
  $export['panelizer_node:p2p_campaign_landing_default'] = $strongarm;

  return $export;
}
