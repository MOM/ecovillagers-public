<?php
/**
 * @file
 * springboard_p2p_landing.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function springboard_p2p_landing_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->name = 'node:p2p_campaign_landing:default';
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'p2p_campaign_landing';
  $panelizer->no_blocks = FALSE;
  $panelizer->css_id = '';
  $panelizer->css = '';
  $panelizer->pipeline = 'standard';
  $panelizer->contexts = array();
  $panelizer->relationships = array();
  $panelizer->access = array();
  $panelizer->view_mode = 'page_manager';
  $panelizer->css_class = 'p2p-panelizer-campaign-landing';
  $panelizer->title_element = 'H2';
  $panelizer->link_to_entity = TRUE;
  $panelizer->extra = array();
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
      'middle_top_left' => NULL,
      'middle_top_right' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = 'f63f1a99-39ec-4e1e-a3de-887fd61e4808';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-0d094ea0-7fa7-4402-9e68-8752e0860753';
    $pane->panel = 'bottom';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => '',
      'title' => '',
      'body' => '<h2>%node:field_p2p_featured_title</h2>',
      'format' => 'full_html',
      'substitute' => 1,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '0d094ea0-7fa7-4402-9e68-8752e0860753';
    $display->content['new-0d094ea0-7fa7-4402-9e68-8752e0860753'] = $pane;
    $display->panels['bottom'][0] = 'new-0d094ea0-7fa7-4402-9e68-8752e0860753';
    $pane = new stdClass();
    $pane->pid = 'new-ea8fe52b-8cca-41bc-8b77-0952f6299084';
    $pane->panel = 'bottom';
    $pane->type = 'views_panes';
    $pane->subtype = 'p2p_referenced_campaigns-panel_pane_2';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'entity_field_value:node:p2p_campaign_landing:field_p2p_choose_featured_type',
          'settings' => array(
            'field_p2p_choose_featured_type' => array(
              'und' => array(
                0 => array(
                  'value' => 'automated',
                ),
              ),
            ),
            'field_p2p_choose_featured_type_value' => 'automated',
          ),
          'context' => 'panelizer',
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'ea8fe52b-8cca-41bc-8b77-0952f6299084';
    $display->content['new-ea8fe52b-8cca-41bc-8b77-0952f6299084'] = $pane;
    $display->panels['bottom'][1] = 'new-ea8fe52b-8cca-41bc-8b77-0952f6299084';
    $pane = new stdClass();
    $pane->pid = 'new-be82ca65-44c8-4215-b1ae-0556f5e9c346';
    $pane->panel = 'bottom';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_p2p_featured_choose_blocks';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'entity_field_value:node:p2p_campaign_landing:field_p2p_choose_featured_type',
          'settings' => array(
            'field_p2p_choose_featured_type' => array(
              'und' => array(
                0 => array(
                  'value' => 'custom_blocks',
                ),
              ),
            ),
            'field_p2p_choose_featured_type_value' => 'custom_blocks',
          ),
          'context' => 'panelizer',
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
      'label' => 'title',
      'formatter' => 'blockreference_without_title',
      'delta_limit' => '0',
      'delta_offset' => '0',
      'delta_reversed' => 0,
      'formatter_settings' => array(),
      'context' => 'panelizer',
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'be82ca65-44c8-4215-b1ae-0556f5e9c346';
    $display->content['new-be82ca65-44c8-4215-b1ae-0556f5e9c346'] = $pane;
    $display->panels['bottom'][2] = 'new-be82ca65-44c8-4215-b1ae-0556f5e9c346';
    $pane = new stdClass();
    $pane->pid = 'new-0c63d3b8-5e94-4147-96e5-226e34539acf';
    $pane->panel = 'middle_left';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'Grid Title',
      'title' => '',
      'body' => '<h2>%node:field-p2p-grid-title</h2>',
      'format' => 'full_html',
      'substitute' => 1,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '0c63d3b8-5e94-4147-96e5-226e34539acf';
    $display->content['new-0c63d3b8-5e94-4147-96e5-226e34539acf'] = $pane;
    $display->panels['middle_left'][0] = 'new-0c63d3b8-5e94-4147-96e5-226e34539acf';
    $pane = new stdClass();
    $pane->pid = 'new-75fdd4db-bb0b-4436-b8ea-5454fc55fbf9';
    $pane->panel = 'middle_left';
    $pane->type = 'views_panes';
    $pane->subtype = 'p2p_referenced_campaigns-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '75fdd4db-bb0b-4436-b8ea-5454fc55fbf9';
    $display->content['new-75fdd4db-bb0b-4436-b8ea-5454fc55fbf9'] = $pane;
    $display->panels['middle_left'][1] = 'new-75fdd4db-bb0b-4436-b8ea-5454fc55fbf9';
    $pane = new stdClass();
    $pane->pid = 'new-9fa69cd5-022d-4ad4-848b-653e3a22da7e';
    $pane->panel = 'middle_right';
    $pane->type = 'block';
    $pane->subtype = 'sb_social-social_sharing';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Share',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'pane-social-links',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '9fa69cd5-022d-4ad4-848b-653e3a22da7e';
    $display->content['new-9fa69cd5-022d-4ad4-848b-653e3a22da7e'] = $pane;
    $display->panels['middle_right'][0] = 'new-9fa69cd5-022d-4ad4-848b-653e3a22da7e';
    $pane = new stdClass();
    $pane->pid = 'new-945aa5a7-9224-4e69-9758-4bded5096b1a';
    $pane->panel = 'middle_right';
    $pane->type = 'views_panes';
    $pane->subtype = 'p2p_top_personal_campaigns_by_category-panel_pane_2';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'pane-top-campaigns',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '945aa5a7-9224-4e69-9758-4bded5096b1a';
    $display->content['new-945aa5a7-9224-4e69-9758-4bded5096b1a'] = $pane;
    $display->panels['middle_right'][1] = 'new-945aa5a7-9224-4e69-9758-4bded5096b1a';
    $pane = new stdClass();
    $pane->pid = 'new-6a83cfd5-6a3e-4a37-8fb9-02f36e51479d';
    $pane->panel = 'middle_right';
    $pane->type = 'views_panes';
    $pane->subtype = 'p2p_top_personal_campaigns_by_category-panel_pane_1';
    $pane->shown = FALSE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'pane-top-campaigns',
    );
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '6a83cfd5-6a3e-4a37-8fb9-02f36e51479d';
    $display->content['new-6a83cfd5-6a3e-4a37-8fb9-02f36e51479d'] = $pane;
    $display->panels['middle_right'][2] = 'new-6a83cfd5-6a3e-4a37-8fb9-02f36e51479d';
    $pane = new stdClass();
    $pane->pid = 'new-809ad633-6e77-417c-b8a6-67e55c1b0c0e';
    $pane->panel = 'middle_right';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => '',
      'title' => '',
      'body' => '<h3>Search for a personal campaign</h3>',
      'format' => 'full_html',
      'substitute' => 1,
      'name' => 'fundraising_title_pane',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => array(
        'title' => array(
          'prefix' => '',
          'suffix' => '',
        ),
        'content' => array(
          'prefix' => '<div class="panel-pane-wrapper search-wrapper">',
          'suffix' => '',
        ),
        'theme' => 0,
      ),
      'style' => 'wrapper_raw',
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'pane-search-title',
    );
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '809ad633-6e77-417c-b8a6-67e55c1b0c0e';
    $display->content['new-809ad633-6e77-417c-b8a6-67e55c1b0c0e'] = $pane;
    $display->panels['middle_right'][3] = 'new-809ad633-6e77-417c-b8a6-67e55c1b0c0e';
    $pane = new stdClass();
    $pane->pid = 'new-b0afc09f-b0b8-4039-825b-25257ccfa6c9';
    $pane->panel = 'middle_right';
    $pane->type = 'block';
    $pane->subtype = 'views-34b46eb746b893fab34588cc0e4e3d47';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'inherit_path' => 1,
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'landing-search-form',
    );
    $pane->extras = array();
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = 'b0afc09f-b0b8-4039-825b-25257ccfa6c9';
    $display->content['new-b0afc09f-b0b8-4039-825b-25257ccfa6c9'] = $pane;
    $display->panels['middle_right'][4] = 'new-b0afc09f-b0b8-4039-825b-25257ccfa6c9';
    $pane = new stdClass();
    $pane->pid = 'new-74da5479-bb91-49fd-9079-c3e4638bffdb';
    $pane->panel = 'middle_right';
    $pane->type = 'views_panes';
    $pane->subtype = 'p2p_search_for_a_campaign-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 5;
    $pane->locks = array();
    $pane->uuid = '74da5479-bb91-49fd-9079-c3e4638bffdb';
    $display->content['new-74da5479-bb91-49fd-9079-c3e4638bffdb'] = $pane;
    $display->panels['middle_right'][5] = 'new-74da5479-bb91-49fd-9079-c3e4638bffdb';
    $pane = new stdClass();
    $pane->pid = 'new-dccb99b4-ecb2-4d12-af32-de2d9dfbb5db';
    $pane->panel = 'middle_right';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => '',
      'title' => '',
      'body' => '<a href="/peer-to-peer-campaign-search">View all campaigns</a>',
      'format' => 'filtered_html',
      'substitute' => 1,
      'name' => 'pane_search_link',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => array(
        'title' => array(
          'prefix' => '',
          'suffix' => '',
        ),
        'content' => array(
          'prefix' => '',
          'suffix' => '</div>',
        ),
        'theme' => 0,
      ),
      'style' => 'wrapper_raw',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 6;
    $pane->locks = array();
    $pane->uuid = 'dccb99b4-ecb2-4d12-af32-de2d9dfbb5db';
    $display->content['new-dccb99b4-ecb2-4d12-af32-de2d9dfbb5db'] = $pane;
    $display->panels['middle_right'][6] = 'new-dccb99b4-ecb2-4d12-af32-de2d9dfbb5db';
    $pane = new stdClass();
    $pane->pid = 'new-2b715f39-4aca-4454-b3ba-ee14443b1274';
    $pane->panel = 'middle_right';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_p2p_side_block';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'blockreference_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'panelizer',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'landing-side-block side-gray-shaded',
    );
    $pane->extras = array();
    $pane->position = 7;
    $pane->locks = array();
    $pane->uuid = '2b715f39-4aca-4454-b3ba-ee14443b1274';
    $display->content['new-2b715f39-4aca-4454-b3ba-ee14443b1274'] = $pane;
    $display->panels['middle_right'][7] = 'new-2b715f39-4aca-4454-b3ba-ee14443b1274';
    $pane = new stdClass();
    $pane->pid = 'new-27f93a8e-f0c3-4e06-b3b7-d8302b6d8522';
    $pane->panel = 'top';
    $pane->type = 'top_links';
    $pane->subtype = 'top_links';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'text' => '',
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => '',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '27f93a8e-f0c3-4e06-b3b7-d8302b6d8522';
    $display->content['new-27f93a8e-f0c3-4e06-b3b7-d8302b6d8522'] = $pane;
    $display->panels['top'][0] = 'new-27f93a8e-f0c3-4e06-b3b7-d8302b6d8522';
    $pane = new stdClass();
    $pane->pid = 'new-9bb0248f-6996-43d9-bfae-970ef5cf9e44';
    $pane->panel = 'top';
    $pane->type = 'views_panes';
    $pane->subtype = 'p2p_campaign_landing_slideshow-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => 'slideshow-panel',
      'css_class' => '',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '9bb0248f-6996-43d9-bfae-970ef5cf9e44';
    $display->content['new-9bb0248f-6996-43d9-bfae-970ef5cf9e44'] = $pane;
    $display->panels['top'][1] = 'new-9bb0248f-6996-43d9-bfae-970ef5cf9e44';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-75fdd4db-bb0b-4436-b8ea-5454fc55fbf9';
  $panelizer->display = $display;
  $export['node:p2p_campaign_landing:default'] = $panelizer;

  return $export;
}
