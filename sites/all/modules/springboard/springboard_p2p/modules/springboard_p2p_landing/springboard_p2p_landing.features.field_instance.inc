<?php
/**
 * @file
 * springboard_p2p_landing.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function springboard_p2p_landing_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-p2p_campaign_landing-field_p2p_choose_featured_type'
  $field_instances['node-p2p_campaign_landing-field_p2p_choose_featured_type'] = array(
    'bundle' => 'p2p_campaign_landing',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 7,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_p2p_choose_featured_type',
    'label' => 'Choose a Featured Type',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-p2p_campaign_landing-field_p2p_feature_pers_campaigns'
  $field_instances['node-p2p_campaign_landing-field_p2p_feature_pers_campaigns'] = array(
    'bundle' => 'p2p_campaign_landing',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_p2p_feature_pers_campaigns',
    'label' => 'Featured Personal Campaigns',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'node-p2p_campaign_landing-field_p2p_featured_choose_blocks'
  $field_instances['node-p2p_campaign_landing-field_p2p_featured_choose_blocks'] = array(
    'bundle' => 'p2p_campaign_landing',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'blockreference',
        'settings' => array(),
        'type' => 'blockreference_default',
        'weight' => 6,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_p2p_featured_choose_blocks',
    'label' => 'Featured Choose Blocks',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'blockreference',
      'settings' => array(
        'autocomplete_path' => 'blockreference/autocomplete',
        'size' => 60,
      ),
      'type' => 'blockreference_autocomplete',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-p2p_campaign_landing-field_p2p_featured_title'
  $field_instances['node-p2p_campaign_landing-field_p2p_featured_title'] = array(
    'bundle' => 'p2p_campaign_landing',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 5,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_p2p_featured_title',
    'label' => 'Featured Title',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-p2p_campaign_landing-field_p2p_grid_title'
  $field_instances['node-p2p_campaign_landing-field_p2p_grid_title'] = array(
    'bundle' => 'p2p_campaign_landing',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 4,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_p2p_grid_title',
    'label' => 'Grid Title',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-p2p_campaign_landing-field_p2p_referenced_campaigns'
  $field_instances['node-p2p_campaign_landing-field_p2p_referenced_campaigns'] = array(
    'bundle' => 'p2p_campaign_landing',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Choose nodes to reference from Peer to peer campaigns. (Typing bring up suggestions.)',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_p2p_referenced_campaigns',
    'label' => 'Start your own campaign',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-p2p_campaign_landing-field_p2p_side_block'
  $field_instances['node-p2p_campaign_landing-field_p2p_side_block'] = array(
    'bundle' => 'p2p_campaign_landing',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Choose a block to reference. (Typing bring up suggestions.)',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'blockreference',
        'settings' => array(),
        'type' => 'blockreference_default',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_p2p_side_block',
    'label' => 'Side Block',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'blockreference',
      'settings' => array(
        'autocomplete_path' => 'blockreference/autocomplete',
        'size' => 60,
      ),
      'type' => 'blockreference_autocomplete',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-p2p_campaign_landing-field_p2p_slide_show'
  $field_instances['node-p2p_campaign_landing-field_p2p_slide_show'] = array(
    'bundle' => 'p2p_campaign_landing',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Choose nodes to reference from Peer to peer campaigns for the slideshow. (Typing bring up suggestions.)',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_p2p_slide_show',
    'label' => 'Slide Show',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 12,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Choose a Featured Type');
  t('Choose a block to reference. (Typing bring up suggestions.)');
  t('Choose nodes to reference from Peer to peer campaigns for the slideshow. (Typing bring up suggestions.)');
  t('Choose nodes to reference from Peer to peer campaigns. (Typing bring up suggestions.)');
  t('Featured Choose Blocks');
  t('Featured Personal Campaigns');
  t('Featured Title');
  t('Grid Title');
  t('Side Block');
  t('Slide Show');
  t('Start your own campaign');

  return $field_instances;
}
