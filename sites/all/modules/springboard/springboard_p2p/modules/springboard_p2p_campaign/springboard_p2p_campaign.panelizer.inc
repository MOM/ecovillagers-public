<?php
/**
 * @file
 * springboard_p2p_campaign.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function springboard_p2p_campaign_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->name = 'node:p2p_campaign:default';
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'p2p_campaign';
  $panelizer->no_blocks = FALSE;
  $panelizer->css_id = '';
  $panelizer->css = '';
  $panelizer->pipeline = 'standard';
  $panelizer->contexts = array();
  $panelizer->relationships = array();
  $panelizer->access = array();
  $panelizer->view_mode = 'page_manager';
  $panelizer->css_class = 'p2p-page-type p2p-campaign-page';
  $panelizer->title_element = 'H2';
  $panelizer->link_to_entity = TRUE;
  $panelizer->extra = array();
  $display = new panels_display();
  $display->layout = 'p2p_landing_twocol_bricks';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'top' => NULL,
      'middle_left' => NULL,
      'middle_right' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = '542f3390-cfa6-4710-96c6-8d1649f14a4b';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-3514bef7-441f-4f7c-8098-057048f1a136';
    $pane->panel = 'bottom';
    $pane->type = 'views_panes';
    $pane->subtype = 'p2p_referenced_campaigns-panel_pane_2';
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
    $pane->uuid = '3514bef7-441f-4f7c-8098-057048f1a136';
    $display->content['new-3514bef7-441f-4f7c-8098-057048f1a136'] = $pane;
    $display->panels['bottom'][0] = 'new-3514bef7-441f-4f7c-8098-057048f1a136';
    $pane = new stdClass();
    $pane->pid = 'new-5c0b9c01-b1ae-4bdb-8808-77979ea83c35';
    $pane->panel = 'middle_left';
    $pane->type = 'views_panes';
    $pane->subtype = 'p2p_campaign-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'pane-p2p-content panel-pane-wrapper',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '5c0b9c01-b1ae-4bdb-8808-77979ea83c35';
    $display->content['new-5c0b9c01-b1ae-4bdb-8808-77979ea83c35'] = $pane;
    $display->panels['middle_left'][0] = 'new-5c0b9c01-b1ae-4bdb-8808-77979ea83c35';
    $pane = new stdClass();
    $pane->pid = 'new-19ad46df-6219-453a-b6bc-2426c9092b4e';
    $pane->panel = 'middle_right';
    $pane->type = 'views_panes';
    $pane->subtype = 'p2p_top_personal_campaigns_by_category-panel_pane_1';
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
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '19ad46df-6219-453a-b6bc-2426c9092b4e';
    $display->content['new-19ad46df-6219-453a-b6bc-2426c9092b4e'] = $pane;
    $display->panels['middle_right'][0] = 'new-19ad46df-6219-453a-b6bc-2426c9092b4e';
    $pane = new stdClass();
    $pane->pid = 'new-481d1177-ebe1-491a-8e47-de25d4e13d31';
    $pane->panel = 'middle_right';
    $pane->type = 'custom';
    $pane->subtype = 'fundraising_title_pane';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => '',
      'title' => '',
      'body' => '',
      'format' => 'filtered_html',
      'substitute' => TRUE,
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '481d1177-ebe1-491a-8e47-de25d4e13d31';
    $display->content['new-481d1177-ebe1-491a-8e47-de25d4e13d31'] = $pane;
    $display->panels['middle_right'][1] = 'new-481d1177-ebe1-491a-8e47-de25d4e13d31';
    $pane = new stdClass();
    $pane->pid = 'new-782983cb-bd9e-49cb-b57c-d2aa136cde09';
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
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '782983cb-bd9e-49cb-b57c-d2aa136cde09';
    $display->content['new-782983cb-bd9e-49cb-b57c-d2aa136cde09'] = $pane;
    $display->panels['middle_right'][2] = 'new-782983cb-bd9e-49cb-b57c-d2aa136cde09';
    $pane = new stdClass();
    $pane->pid = 'new-4311f202-d667-435e-a6d8-35741a4d95ba';
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
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '4311f202-d667-435e-a6d8-35741a4d95ba';
    $display->content['new-4311f202-d667-435e-a6d8-35741a4d95ba'] = $pane;
    $display->panels['middle_right'][3] = 'new-4311f202-d667-435e-a6d8-35741a4d95ba';
    $pane = new stdClass();
    $pane->pid = 'new-728990ea-0369-4f19-ba3c-be7af0dc1543';
    $pane->panel = 'middle_right';
    $pane->type = 'custom';
    $pane->subtype = 'pane_search_link';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => '',
      'title' => '',
      'body' => '',
      'format' => 'filtered_html',
      'substitute' => TRUE,
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
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = '728990ea-0369-4f19-ba3c-be7af0dc1543';
    $display->content['new-728990ea-0369-4f19-ba3c-be7af0dc1543'] = $pane;
    $display->panels['middle_right'][4] = 'new-728990ea-0369-4f19-ba3c-be7af0dc1543';
    $pane = new stdClass();
    $pane->pid = 'new-fb351353-71d7-4a33-85d9-b9c30d616b33';
    $pane->panel = 'top';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_p2p_campaign_banner';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'title',
      'formatter' => 'image',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'image_style' => 'p2p_top_banner',
        'image_link' => '',
      ),
      'context' => 'panelizer',
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'pane-top-banner',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'fb351353-71d7-4a33-85d9-b9c30d616b33';
    $display->content['new-fb351353-71d7-4a33-85d9-b9c30d616b33'] = $pane;
    $display->panels['top'][0] = 'new-fb351353-71d7-4a33-85d9-b9c30d616b33';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $panelizer->display = $display;
  $export['node:p2p_campaign:default'] = $panelizer;

  return $export;
}
