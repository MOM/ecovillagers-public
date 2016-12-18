<?php
/**
 * @file
 * springboard_p2p_personal_campaign.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function springboard_p2p_personal_campaign_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->name = 'node:p2p_personal_campaign:default';
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'p2p_personal_campaign';
  $panelizer->no_blocks = FALSE;
  $panelizer->css_id = '';
  $panelizer->css = '';
  $panelizer->pipeline = 'standard';
  $panelizer->contexts = array(
    0 => array(
      'identifier' => 'User',
      'keyword' => 'user',
      'name' => 'user',
      'type' => 'current',
      'uid' => '',
      'id' => 1,
    ),
  );
  $panelizer->relationships = array(
    0 => array(
      'identifier' => 'User from Node (on node.node_author)',
      'keyword' => 'user_2',
      'name' => 'entity_from_schema:uid-node-user',
      'context' => 'panelizer',
      'id' => 1,
    ),
  );
  $panelizer->access = array();
  $panelizer->view_mode = 'page_manager';
  $panelizer->css_class = 'p2p-panelizer-personal-campaign';
  $panelizer->title_element = 'H2';
  $panelizer->link_to_entity = TRUE;
  $panelizer->extra = array();
  $display = new panels_display();
  $display->layout = 'p2p_twocol_bricks';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'top' => NULL,
      'middle_left' => NULL,
      'middle_right' => NULL,
      'bottom' => NULL,
      'middle_top_left' => NULL,
      'middle_top_right' => NULL,
    ),
    'middle_top_right' => array(
      'style' => '-1',
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = '3a5a357b-35c3-404d-95c7-710fe59c4a26';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-9e7adff4-77d7-4c34-b2fb-417c130de880';
    $pane->panel = 'bottom';
    $pane->type = 'personal_campaign_comments';
    $pane->subtype = 'personal_campaign_comments';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'donation_date_deadline',
          'settings' => NULL,
          'context' => 'panelizer',
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
      'context' => 'panelizer',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => 'p2p-comment-pane',
      'css_class' => '',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '9e7adff4-77d7-4c34-b2fb-417c130de880';
    $display->content['new-9e7adff4-77d7-4c34-b2fb-417c130de880'] = $pane;
    $display->panels['bottom'][0] = 'new-9e7adff4-77d7-4c34-b2fb-417c130de880';
    $pane = new stdClass();
    $pane->pid = 'new-8321c063-28f8-4398-9b2c-9b56bf78395f';
    $pane->panel = 'middle_left';
    $pane->type = 'personal_campaign_call_to_action';
    $pane->subtype = 'personal_campaign_call_to_action';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'donation_date_deadline',
          'settings' => NULL,
          'context' => 'panelizer',
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
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
      'css_class' => 'donate-button',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '8321c063-28f8-4398-9b2c-9b56bf78395f';
    $display->content['new-8321c063-28f8-4398-9b2c-9b56bf78395f'] = $pane;
    $display->panels['middle_left'][0] = 'new-8321c063-28f8-4398-9b2c-9b56bf78395f';
    $pane = new stdClass();
    $pane->pid = 'new-1dfeee97-1a59-4f64-9da7-601b11a32735';
    $pane->panel = 'middle_left';
    $pane->type = 'org_intro';
    $pane->subtype = 'org_intro';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'donation_date_deadline',
          'settings' => NULL,
          'context' => 'panelizer',
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
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
      'css_class' => '',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '1dfeee97-1a59-4f64-9da7-601b11a32735';
    $display->content['new-1dfeee97-1a59-4f64-9da7-601b11a32735'] = $pane;
    $display->panels['middle_left'][1] = 'new-1dfeee97-1a59-4f64-9da7-601b11a32735';
    $pane = new stdClass();
    $pane->pid = 'new-a6baa2cb-e251-4a0e-9f6b-83446a4dcdf3';
    $pane->panel = 'middle_left';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_p2p_video_embed';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'donation_date_deadline',
          'settings' => NULL,
          'context' => 'panelizer',
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'video_embed_field',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'description' => 1,
        'description_position' => 'bottom',
        'video_style' => 'p2p_video',
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
      'css_class' => 'pane-video',
    );
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'a6baa2cb-e251-4a0e-9f6b-83446a4dcdf3';
    $display->content['new-a6baa2cb-e251-4a0e-9f6b-83446a4dcdf3'] = $pane;
    $display->panels['middle_left'][2] = 'new-a6baa2cb-e251-4a0e-9f6b-83446a4dcdf3';
    $pane = new stdClass();
    $pane->pid = 'new-fa2ee32b-a7bc-417e-9e5c-2ba674f867ff';
    $pane->panel = 'middle_left';
    $pane->type = 'personal_campaign_call_to_action';
    $pane->subtype = 'personal_campaign_call_to_action';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'node_field_populated',
          'settings' => array(
            'node_field' => 'p2p_personal_campaign:field_p2p_video_embed',
            'label' => 'Peer to peer personal campaign - Upload a Campaign Video',
          ),
          'context' => 'panelizer',
          'not' => FALSE,
        ),
        1 => array(
          'name' => 'donation_date_deadline',
          'settings' => NULL,
          'context' => 'panelizer',
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
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
      'css_class' => 'donate-button video-pane-button',
    );
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = 'fa2ee32b-a7bc-417e-9e5c-2ba674f867ff';
    $display->content['new-fa2ee32b-a7bc-417e-9e5c-2ba674f867ff'] = $pane;
    $display->panels['middle_left'][3] = 'new-fa2ee32b-a7bc-417e-9e5c-2ba674f867ff';
    $pane = new stdClass();
    $pane->pid = 'new-6a286485-ca59-4bae-a049-ed3af09e6767';
    $pane->panel = 'middle_right';
    $pane->type = 'personal_campaign_share';
    $pane->subtype = 'personal_campaign_share';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'donation_date_deadline',
          'settings' => NULL,
          'context' => 'panelizer',
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
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
      'css_class' => 'pane-social-links',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '6a286485-ca59-4bae-a049-ed3af09e6767';
    $display->content['new-6a286485-ca59-4bae-a049-ed3af09e6767'] = $pane;
    $display->panels['middle_right'][0] = 'new-6a286485-ca59-4bae-a049-ed3af09e6767';
    $pane = new stdClass();
    $pane->pid = 'new-a713082a-f1f9-4e4b-9fa9-eaedeef71bf1';
    $pane->panel = 'middle_right';
    $pane->type = 'personal_campaign_progress';
    $pane->subtype = 'personal_campaign_progress';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'donation_date_deadline',
          'settings' => NULL,
          'context' => 'panelizer',
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
      'context' => 'panelizer',
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => array(
        'title' => array(
          'prefix' => '',
          'suffix' => '',
        ),
        'content' => array(
          'prefix' => '<div class="panel-pane-wrapper pane-progress">',
          'suffix' => '',
        ),
        'theme' => 0,
      ),
      'style' => 'wrapper_raw',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'a713082a-f1f9-4e4b-9fa9-eaedeef71bf1';
    $display->content['new-a713082a-f1f9-4e4b-9fa9-eaedeef71bf1'] = $pane;
    $display->panels['middle_right'][1] = 'new-a713082a-f1f9-4e4b-9fa9-eaedeef71bf1';
    $pane = new stdClass();
    $pane->pid = 'new-c46d449f-8ba5-4326-aeb6-3306b172ef4d';
    $pane->panel = 'middle_right';
    $pane->type = 'personal_campaign_goal';
    $pane->subtype = 'personal_campaign_goal';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'donation_date_deadline',
          'settings' => NULL,
          'context' => 'panelizer',
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
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
    $pane->uuid = 'c46d449f-8ba5-4326-aeb6-3306b172ef4d';
    $display->content['new-c46d449f-8ba5-4326-aeb6-3306b172ef4d'] = $pane;
    $display->panels['middle_right'][2] = 'new-c46d449f-8ba5-4326-aeb6-3306b172ef4d';
    $pane = new stdClass();
    $pane->pid = 'new-d4ef12a9-ee7d-44ff-8747-3e42752e1988';
    $pane->panel = 'middle_right';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_p2p_fundraising_deadline';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'donation_date_deadline',
          'settings' => NULL,
          'context' => 'panelizer',
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
      'label' => 'above',
      'formatter' => 'date_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'format_type' => 'long',
        'fromto' => 'both',
        'multiple_from' => '',
        'multiple_number' => '',
        'multiple_to' => '',
      ),
      'context' => 'panelizer',
      'override_title' => 0,
      'override_title_text' => '',
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
          'suffix' => '',
        ),
        'theme' => 0,
      ),
      'style' => 'wrapper_raw',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = 'd4ef12a9-ee7d-44ff-8747-3e42752e1988';
    $display->content['new-d4ef12a9-ee7d-44ff-8747-3e42752e1988'] = $pane;
    $display->panels['middle_right'][3] = 'new-d4ef12a9-ee7d-44ff-8747-3e42752e1988';
    $pane = new stdClass();
    $pane->pid = 'new-01e77e74-02dc-4795-8812-a4b245e4decb';
    $pane->panel = 'middle_right';
    $pane->type = 'views_panes';
    $pane->subtype = 'p2p_suggested_donation-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'node_field_populated',
          'settings' => array(
            'node_field' => 'p2p_personal_campaign:field_p2p_suggested_donation_amt',
            'label' => 'Peer to Peer Personal Campaign - Suggested Donation Amount',
          ),
          'context' => 'panelizer',
          'not' => FALSE,
        ),
        1 => array(
          'name' => 'donation_date_deadline',
          'settings' => NULL,
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
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = '01e77e74-02dc-4795-8812-a4b245e4decb';
    $display->content['new-01e77e74-02dc-4795-8812-a4b245e4decb'] = $pane;
    $display->panels['middle_right'][4] = 'new-01e77e74-02dc-4795-8812-a4b245e4decb';
    $pane = new stdClass();
    $pane->pid = 'new-626dcfc6-654f-41ec-8721-35e6014cd926';
    $pane->panel = 'middle_right';
    $pane->type = 'views_panes';
    $pane->subtype = 'p2p_suggested_donation-panel_pane_2';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'node_field_populated',
          'settings' => array(
            'node_field' => 'p2p_campaign:field_p2p_suggested_donation',
            'label' => 'Peer to Peer Campaign - P2P Suggested Donation Amount',
          ),
          'context' => 'panelizer',
          'not' => TRUE,
        ),
        1 => array(
          'name' => 'node_field_populated',
          'settings' => array(
            'node_field' => 'p2p_personal_campaign:field_p2p_suggested_donation_amt',
            'label' => 'Peer to Peer Personal Campaign - Suggested Donation Amount',
          ),
          'context' => 'panelizer',
          'not' => TRUE,
        ),
        2 => array(
          'name' => 'donation_date_deadline',
          'settings' => NULL,
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
    $pane->position = 5;
    $pane->locks = array();
    $pane->uuid = '626dcfc6-654f-41ec-8721-35e6014cd926';
    $display->content['new-626dcfc6-654f-41ec-8721-35e6014cd926'] = $pane;
    $display->panels['middle_right'][5] = 'new-626dcfc6-654f-41ec-8721-35e6014cd926';
    $pane = new stdClass();
    $pane->pid = 'new-57cfe285-650a-4b86-9b80-a4bece44752c';
    $pane->panel = 'middle_right';
    $pane->type = 'personal_campaign_call_to_action';
    $pane->subtype = 'personal_campaign_call_to_action';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'donation_date_deadline',
          'settings' => NULL,
          'context' => 'panelizer',
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
      'context' => 'panelizer',
      'override_title' => 1,
      'override_title_text' => '',
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'donate-button',
    );
    $pane->extras = array();
    $pane->position = 6;
    $pane->locks = array();
    $pane->uuid = '57cfe285-650a-4b86-9b80-a4bece44752c';
    $display->content['new-57cfe285-650a-4b86-9b80-a4bece44752c'] = $pane;
    $display->panels['middle_right'][6] = 'new-57cfe285-650a-4b86-9b80-a4bece44752c';
    $pane = new stdClass();
    $pane->pid = 'new-6a1e2843-d844-482f-bfda-bc47c4921c4c';
    $pane->panel = 'middle_right';
    $pane->type = 'personal_campaign_roll';
    $pane->subtype = 'personal_campaign_roll';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(),
    );
    $pane->configuration = array(
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
      'css_class' => 'pane-recent-donors',
    );
    $pane->extras = array();
    $pane->position = 7;
    $pane->locks = array();
    $pane->uuid = '6a1e2843-d844-482f-bfda-bc47c4921c4c';
    $display->content['new-6a1e2843-d844-482f-bfda-bc47c4921c4c'] = $pane;
    $display->panels['middle_right'][7] = 'new-6a1e2843-d844-482f-bfda-bc47c4921c4c';
    $pane = new stdClass();
    $pane->pid = 'new-21eaa0fe-da1c-4af1-bd6e-48527364618d';
    $pane->panel = 'middle_right';
    $pane->type = 'custom';
    $pane->subtype = 'fundraising_title_pane';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(),
    );
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
    $pane->position = 8;
    $pane->locks = array();
    $pane->uuid = '21eaa0fe-da1c-4af1-bd6e-48527364618d';
    $display->content['new-21eaa0fe-da1c-4af1-bd6e-48527364618d'] = $pane;
    $display->panels['middle_right'][8] = 'new-21eaa0fe-da1c-4af1-bd6e-48527364618d';
    $pane = new stdClass();
    $pane->pid = 'new-31382ff6-f3f2-47f8-95e8-425972bf9f38';
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
    $pane->position = 9;
    $pane->locks = array();
    $pane->uuid = '31382ff6-f3f2-47f8-95e8-425972bf9f38';
    $display->content['new-31382ff6-f3f2-47f8-95e8-425972bf9f38'] = $pane;
    $display->panels['middle_right'][9] = 'new-31382ff6-f3f2-47f8-95e8-425972bf9f38';
    $pane = new stdClass();
    $pane->pid = 'new-4bef38ad-a8aa-46ab-a7f5-a8dca8b7f93a';
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
    $pane->position = 10;
    $pane->locks = array();
    $pane->uuid = '4bef38ad-a8aa-46ab-a7f5-a8dca8b7f93a';
    $display->content['new-4bef38ad-a8aa-46ab-a7f5-a8dca8b7f93a'] = $pane;
    $display->panels['middle_right'][10] = 'new-4bef38ad-a8aa-46ab-a7f5-a8dca8b7f93a';
    $pane = new stdClass();
    $pane->pid = 'new-af37ece0-1376-4a72-a3f6-31c0f0829987';
    $pane->panel = 'middle_right';
    $pane->type = 'custom';
    $pane->subtype = 'pane_search_link';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(),
    );
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
    $pane->position = 11;
    $pane->locks = array();
    $pane->uuid = 'af37ece0-1376-4a72-a3f6-31c0f0829987';
    $display->content['new-af37ece0-1376-4a72-a3f6-31c0f0829987'] = $pane;
    $display->panels['middle_right'][11] = 'new-af37ece0-1376-4a72-a3f6-31c0f0829987';
    $pane = new stdClass();
    $pane->pid = 'new-9042689c-b289-40fa-ab51-46c9f494f96f';
    $pane->panel = 'middle_right';
    $pane->type = 'views_panes';
    $pane->subtype = 'p2p_campaign-panel_pane_2';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'side-gray-shaded pane-get-started',
    );
    $pane->extras = array();
    $pane->position = 12;
    $pane->locks = array();
    $pane->uuid = '9042689c-b289-40fa-ab51-46c9f494f96f';
    $display->content['new-9042689c-b289-40fa-ab51-46c9f494f96f'] = $pane;
    $display->panels['middle_right'][12] = 'new-9042689c-b289-40fa-ab51-46c9f494f96f';
    $pane = new stdClass();
    $pane->pid = 'new-0cd4f51e-4ba7-474d-a3ad-e1a931ded90f';
    $pane->panel = 'middle_top_left';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:body';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'donation_date_deadline',
          'settings' => NULL,
          'context' => 'panelizer',
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'text_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
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
      'css_class' => 'pane-campaign-text',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '0cd4f51e-4ba7-474d-a3ad-e1a931ded90f';
    $display->content['new-0cd4f51e-4ba7-474d-a3ad-e1a931ded90f'] = $pane;
    $display->panels['middle_top_left'][0] = 'new-0cd4f51e-4ba7-474d-a3ad-e1a931ded90f';
    $pane = new stdClass();
    $pane->pid = 'new-8c5c3580-a2e6-475f-92ce-03ecdb6df16a';
    $pane->panel = 'middle_top_right';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_p2p_campaign_images';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'donation_date_deadline',
          'settings' => NULL,
          'context' => 'panelizer',
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'image',
      'delta_limit' => '0',
      'delta_offset' => '0',
      'delta_reversed' => 0,
      'formatter_settings' => array(
        'image_link' => '',
        'image_style' => 'p2p_pers_campaign_image_thumb',
      ),
      'context' => 'panelizer',
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'default',
    );
    $pane->css = array(
      'css_id' => 'pane-slide-show',
      'css_class' => 'pane-campaign-images',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '8c5c3580-a2e6-475f-92ce-03ecdb6df16a';
    $display->content['new-8c5c3580-a2e6-475f-92ce-03ecdb6df16a'] = $pane;
    $display->panels['middle_top_right'][0] = 'new-8c5c3580-a2e6-475f-92ce-03ecdb6df16a';
    $pane = new stdClass();
    $pane->pid = 'new-55cccd38-79cf-4dff-99c5-e7777784c29d';
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
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '55cccd38-79cf-4dff-99c5-e7777784c29d';
    $display->content['new-55cccd38-79cf-4dff-99c5-e7777784c29d'] = $pane;
    $display->panels['top'][0] = 'new-55cccd38-79cf-4dff-99c5-e7777784c29d';
    $pane = new stdClass();
    $pane->pid = 'new-2f539e1d-8d07-4b0b-82fc-cf3731624ec4';
    $pane->panel = 'top';
    $pane->type = 'personal_campaign_help';
    $pane->subtype = 'personal_campaign_help';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'compare_users',
          'settings' => array(
            'equality' => '1',
          ),
          'context' => array(
            0 => 'logged-in-user',
            1 => 'relationship_entity_from_schema:uid-node-user_1',
          ),
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
      'context' => 'panelizer',
      'override_title' => 0,
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
    $pane->uuid = '2f539e1d-8d07-4b0b-82fc-cf3731624ec4';
    $display->content['new-2f539e1d-8d07-4b0b-82fc-cf3731624ec4'] = $pane;
    $display->panels['top'][1] = 'new-2f539e1d-8d07-4b0b-82fc-cf3731624ec4';
    $pane = new stdClass();
    $pane->pid = 'new-c4839f2b-7028-4f6a-b12d-d21c3004d8f1';
    $pane->panel = 'top';
    $pane->type = 'campaign_header';
    $pane->subtype = 'campaign_header';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(),
    );
    $pane->configuration = array(
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
    $pane->uuid = 'c4839f2b-7028-4f6a-b12d-d21c3004d8f1';
    $display->content['new-c4839f2b-7028-4f6a-b12d-d21c3004d8f1'] = $pane;
    $display->panels['top'][2] = 'new-c4839f2b-7028-4f6a-b12d-d21c3004d8f1';
    $pane = new stdClass();
    $pane->pid = 'new-4a068a70-4475-49cf-8535-196ca8fd9f22';
    $pane->panel = 'top';
    $pane->type = 'node_title';
    $pane->subtype = 'node_title';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'link' => 0,
      'markup' => 'h1',
      'id' => '',
      'class' => '',
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
      'css_class' => 'pane-node-title',
    );
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '4a068a70-4475-49cf-8535-196ca8fd9f22';
    $display->content['new-4a068a70-4475-49cf-8535-196ca8fd9f22'] = $pane;
    $display->panels['top'][3] = 'new-4a068a70-4475-49cf-8535-196ca8fd9f22';
    $pane = new stdClass();
    $pane->pid = 'new-5a231b84-dea1-4c4a-a386-df18d09cc825';
    $pane->panel = 'top';
    $pane->type = 'campaign_expiration_message';
    $pane->subtype = 'campaign_expiration_message';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'donation_date_deadline',
          'settings' => NULL,
          'context' => 'panelizer',
          'not' => TRUE,
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
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = '5a231b84-dea1-4c4a-a386-df18d09cc825';
    $display->content['new-5a231b84-dea1-4c4a-a386-df18d09cc825'] = $pane;
    $display->panels['top'][4] = 'new-5a231b84-dea1-4c4a-a386-df18d09cc825';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-0cd4f51e-4ba7-474d-a3ad-e1a931ded90f';
  $panelizer->display = $display;
  $export['node:p2p_personal_campaign:default'] = $panelizer;

  return $export;
}
