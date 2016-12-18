<?php
/**
 * @file
 * springboard_p2p_category.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function springboard_p2p_category_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_basic_info|node|p2p_category|form';
  $field_group->group_name = 'group_basic_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'p2p_category';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_tabs';
  $field_group->data = array(
    'label' => 'Basic info',
    'weight' => '2',
    'children' => array(
      0 => 'body',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Basic info',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_basic_info|node|p2p_category|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_media|node|p2p_category|form';
  $field_group->group_name = 'group_media';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'p2p_category';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_tabs';
  $field_group->data = array(
    'label' => 'Media',
    'weight' => '6',
    'children' => array(
      0 => 'field_p2p_category_image',
      1 => 'group_p2p_images',
      2 => 'group_p2p_video_embed',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Media',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-media field-group-htab',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_media|node|p2p_category|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_p2p_campaign_defaults|node|p2p_category|form';
  $field_group->group_name = 'group_p2p_campaign_defaults';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'p2p_category';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_tabs';
  $field_group->data = array(
    'label' => 'Advanced',
    'weight' => '5',
    'children' => array(
      0 => 'field_p2p_org_intro',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Advanced',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_p2p_campaign_defaults|node|p2p_category|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_p2p_donation_form|node|p2p_category|form';
  $field_group->group_name = 'group_p2p_donation_form';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'p2p_category';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_tabs';
  $field_group->data = array(
    'label' => 'Form banner',
    'weight' => '3',
    'children' => array(
      0 => 'field_p2p_campaign_banner',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Form banner',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_p2p_donation_form|node|p2p_category|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_p2p_images|node|p2p_category|form';
  $field_group->group_name = 'group_p2p_images';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'p2p_category';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_media';
  $field_group->data = array(
    'label' => 'Personal campaign images',
    'weight' => '8',
    'children' => array(
      0 => 'field_p2p_images',
      1 => 'field_p2p_images_edit',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_p2p_images|node|p2p_category|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_p2p_personal_intro|node|p2p_category|form';
  $field_group->group_name = 'group_p2p_personal_intro';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'p2p_category';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_tabs';
  $field_group->data = array(
    'label' => 'Personal campaign introduction',
    'weight' => '4',
    'children' => array(
      0 => 'field_p2p_personal_intro',
      1 => 'field_p2p_personal_intro_edit',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Personal campaign introduction',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_p2p_personal_intro|node|p2p_category|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_p2p_video_embed|node|p2p_category|form';
  $field_group->group_name = 'group_p2p_video_embed';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'p2p_category';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_media';
  $field_group->data = array(
    'label' => 'Video embed',
    'weight' => '9',
    'children' => array(
      0 => 'field_p2p_video_embed',
      1 => 'field_p2p_video_embed_edit',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_p2p_video_embed|node|p2p_category|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_tabs|node|p2p_category|form';
  $field_group->group_name = 'group_tabs';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'p2p_category';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Tabs',
    'weight' => '3',
    'children' => array(
      0 => 'group_p2p_campaign_defaults',
      1 => 'group_p2p_donation_form',
      2 => 'group_p2p_personal_intro',
      3 => 'group_media',
      4 => 'group_basic_info',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => 'group-tabs field-group-htabs',
      ),
    ),
  );
  $export['group_tabs|node|p2p_category|form'] = $field_group;

  return $export;
}
