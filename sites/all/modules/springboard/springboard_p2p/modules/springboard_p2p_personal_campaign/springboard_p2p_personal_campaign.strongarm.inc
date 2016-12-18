<?php
/**
 * @file
 * springboard_p2p_personal_campaign.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function springboard_p2p_personal_campaign_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_p2p_personal_campaign';
  $strongarm->value = 'edit-panelizer';
  $export['additional_settings__active_tab_p2p_personal_campaign'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__p2p_personal_campaign';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
      'search_index' => array(
        'custom_settings' => FALSE,
      ),
      'search_result' => array(
        'custom_settings' => FALSE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '0',
        ),
        'path' => array(
          'weight' => '30',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__p2p_personal_campaign'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fundraiser_p2p_personal_campaign';
  $strongarm->value = 0;
  $export['fundraiser_p2p_personal_campaign'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_p2p_personal_campaign';
  $strongarm->value = array();
  $export['menu_options_p2p_personal_campaign'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_p2p_personal_campaign';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_p2p_personal_campaign'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_p2p_personal_campaign';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_p2p_personal_campaign'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_p2p_personal_campaign';
  $strongarm->value = '0';
  $export['node_preview_p2p_personal_campaign'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_p2p_personal_campaign';
  $strongarm->value = 0;
  $export['node_submitted_p2p_personal_campaign'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_node_p2p_personal_campaign';
  $strongarm->value = array(
    'status' => 1,
    'view modes' => array(
      'page_manager' => array(
        'status' => 1,
        'default' => 1,
        'choice' => 1,
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
  $export['panelizer_defaults_node_p2p_personal_campaign'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:p2p_personal_campaign:page_manager_selection';
  $strongarm->value = 'node:p2p_personal_campaign:default';
  $export['panelizer_node:p2p_personal_campaign:page_manager_selection'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:p2p_personal_campaign_allowed_layouts';
  $strongarm->value = 'O:22:"panels_allowed_layouts":4:{s:9:"allow_new";b:1;s:11:"module_name";s:36:"panelizer_node:p2p_personal_campaign";s:23:"allowed_layout_settings";a:16:{s:8:"flexible";b:1;s:14:"twocol_stacked";b:1;s:13:"twocol_bricks";b:1;s:6:"twocol";b:1;s:25:"threecol_33_34_33_stacked";b:1;s:17:"threecol_33_34_33";b:1;s:25:"threecol_25_50_25_stacked";b:1;s:17:"threecol_25_50_25";b:1;s:6:"onecol";b:1;s:25:"p2p_landing_twocol_bricks";b:1;s:23:"zen_two_sidebars_second";b:1;s:22:"zen_two_sidebars_first";b:1;s:16:"zen_two_sidebars";b:1;s:22:"zen_one_sidebar_second";b:1;s:21:"zen_one_sidebar_first";b:1;s:11:"bricks-cttr";b:1;}s:10:"form_state";N;}';
  $export['panelizer_node:p2p_personal_campaign_allowed_layouts'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:p2p_personal_campaign_allowed_layouts_default';
  $strongarm->value = 1;
  $export['panelizer_node:p2p_personal_campaign_allowed_layouts_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:p2p_personal_campaign_allowed_types_default';
  $strongarm->value = 1;
  $export['panelizer_node:p2p_personal_campaign_allowed_types_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:p2p_personal_campaign_default';
  $strongarm->value = array(
    'token' => 'token',
    'entity_form_field' => 'entity_form_field',
    'entity_field' => 'entity_field',
    'entity_field_extra' => 'entity_field_extra',
    'custom' => 'custom',
    'block' => 'block',
    'entity_view' => 'entity_view',
    'panels_mini' => 'panels_mini',
    'views' => 'views',
    'views_panes' => 'views_panes',
    'other' => 'other',
  );
  $export['panelizer_node:p2p_personal_campaign_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'springboard_social_enabled_content_types';
  $strongarm->value = array(
    'p2p_personal_campaign' => 'p2p_personal_campaign',
    'donation_form' => 'donation_form',
    'p2p_donation_form' => 'p2p_donation_form',
    'p2p_campaign' => 0,
    'p2p_category' => 0,
    'p2p_campaign_landing' => 0,
    'webform_ab' => 0,
    'advocacy' => 0,
    'article' => 0,
    'email_sign_up' => 0,
    'email_wrapper' => 0,
    'page' => 0,
    'page_wrapper' => 0,
    'petition' => 0,
    'ticketed_event' => 0,
    'webform' => 0,
  );
  $export['springboard_social_enabled_content_types'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'springboard_social_services';
  $strongarm->value = array(
    'twitter' => 'twitter',
    'facebook' => 'facebook',
    'email' => 'email',
  );
  $export['springboard_social_services'] = $strongarm;

  return $export;
}
