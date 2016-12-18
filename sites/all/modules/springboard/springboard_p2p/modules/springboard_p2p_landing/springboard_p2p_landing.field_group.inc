<?php
/**
 * @file
 * springboard_p2p_landing.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function springboard_p2p_landing_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_featured|node|p2p_campaign_landing|form';
  $field_group->group_name = 'group_featured';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'p2p_campaign_landing';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_tabs';
  $field_group->data = array(
    'label' => 'Featured',
    'weight' => '13',
    'children' => array(
      0 => 'field_p2p_feature_pers_campaigns',
      1 => 'field_p2p_featured_title',
      2 => 'field_p2p_featured_choose_blocks',
      3 => 'field_p2p_choose_featured_type',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Featured',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-featured field-group-htab',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_featured|node|p2p_campaign_landing|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_grid|node|p2p_campaign_landing|form';
  $field_group->group_name = 'group_grid';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'p2p_campaign_landing';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_tabs';
  $field_group->data = array(
    'label' => 'Grid',
    'weight' => '12',
    'children' => array(
      0 => 'field_p2p_referenced_campaigns',
      1 => 'field_p2p_grid_title',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Grid',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-grid field-group-htab',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_grid|node|p2p_campaign_landing|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sidebar|node|p2p_campaign_landing|form';
  $field_group->group_name = 'group_sidebar';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'p2p_campaign_landing';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_tabs';
  $field_group->data = array(
    'label' => 'Sidebar',
    'weight' => '14',
    'children' => array(
      0 => 'field_p2p_side_block',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Sidebar',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-sidebar field-group-htab',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_sidebar|node|p2p_campaign_landing|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_slideshow|node|p2p_campaign_landing|form';
  $field_group->group_name = 'group_slideshow';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'p2p_campaign_landing';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_tabs';
  $field_group->data = array(
    'label' => 'Slideshow',
    'weight' => '11',
    'children' => array(
      0 => 'field_p2p_slide_show',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Slideshow',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-slideshow field-group-htab',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_slideshow|node|p2p_campaign_landing|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_tabs|node|p2p_campaign_landing|form';
  $field_group->group_name = 'group_tabs';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'p2p_campaign_landing';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Tabs',
    'weight' => '1',
    'children' => array(
      0 => 'group_slideshow',
      1 => 'group_grid',
      2 => 'group_featured',
      3 => 'group_sidebar',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => '',
      ),
    ),
  );
  $export['group_tabs|node|p2p_campaign_landing|form'] = $field_group;

  return $export;
}
