<?php
/**
 * @file
 * springboard_p2p.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function springboard_p2p_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_edit_panel_context';
  $handler->task = 'node_edit';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Personal campaign node edit / add',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => 'p2p-node-edit-add',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'p2p_personal_campaign' => 'p2p_personal_campaign',
            ),
          ),
          'context' => 'argument_node_edit_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'or',
    ),
  );
  $display = new panels_display();
  $display->layout = 'p2p_landing_twocol_bricks';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'top' => NULL,
      'middle_top_left' => NULL,
      'middle_top_right' => NULL,
      'middle_left' => NULL,
      'middle_right' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'dbcca079-3645-42ad-9628-b95dbeec6f04';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-295889f7-20c5-4c23-bd8e-0fa0054b4a62';
    $pane->panel = 'middle_left';
    $pane->type = 'page_messages';
    $pane->subtype = 'page_messages';
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
    $pane->uuid = '295889f7-20c5-4c23-bd8e-0fa0054b4a62';
    $display->content['new-295889f7-20c5-4c23-bd8e-0fa0054b4a62'] = $pane;
    $display->panels['middle_left'][0] = 'new-295889f7-20c5-4c23-bd8e-0fa0054b4a62';
    $pane = new stdClass();
    $pane->pid = 'new-60c81bc6-94d6-4d30-848d-1a7b98028ede';
    $pane->panel = 'middle_left';
    $pane->type = 'custom_title';
    $pane->subtype = 'custom_title';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'text' => 'Your campaign information',
      'markup_tag' => 'h2',
      'override_title' => FALSE,
      'override_title_text' => '<no title>',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'default',
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'custom-pane-title',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '60c81bc6-94d6-4d30-848d-1a7b98028ede';
    $display->content['new-60c81bc6-94d6-4d30-848d-1a7b98028ede'] = $pane;
    $display->panels['middle_left'][1] = 'new-60c81bc6-94d6-4d30-848d-1a7b98028ede';
    $pane = new stdClass();
    $pane->pid = 'new-42ddcb49-5a06-4bbb-9cba-a2b5ad3bba73';
    $pane->panel = 'middle_left';
    $pane->type = 'node_form_title';
    $pane->subtype = 'node_form_title';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_node_edit_1',
      'override_title' => 0,
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
    $pane->uuid = '42ddcb49-5a06-4bbb-9cba-a2b5ad3bba73';
    $display->content['new-42ddcb49-5a06-4bbb-9cba-a2b5ad3bba73'] = $pane;
    $display->panels['middle_left'][2] = 'new-42ddcb49-5a06-4bbb-9cba-a2b5ad3bba73';
    $pane = new stdClass();
    $pane->pid = 'new-9aede3e7-265a-4017-91cc-6080dcc82355';
    $pane->panel = 'middle_left';
    $pane->type = 'entity_form_field';
    $pane->subtype = 'node:field_p2p_campaign';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => '',
      'formatter' => '',
      'context' => 'argument_node_edit_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '9aede3e7-265a-4017-91cc-6080dcc82355';
    $display->content['new-9aede3e7-265a-4017-91cc-6080dcc82355'] = $pane;
    $display->panels['middle_left'][3] = 'new-9aede3e7-265a-4017-91cc-6080dcc82355';
    $pane = new stdClass();
    $pane->pid = 'new-83a38941-2305-4626-ae87-60916e5c3a9c';
    $pane->panel = 'middle_left';
    $pane->type = 'entity_form_field';
    $pane->subtype = 'node:field_p2p_personal_campaign_url';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => '',
      'formatter' => '',
      'context' => 'argument_node_edit_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = '83a38941-2305-4626-ae87-60916e5c3a9c';
    $display->content['new-83a38941-2305-4626-ae87-60916e5c3a9c'] = $pane;
    $display->panels['middle_left'][4] = 'new-83a38941-2305-4626-ae87-60916e5c3a9c';
    $pane = new stdClass();
    $pane->pid = 'new-0b89f721-62cf-45cd-aac0-30134c94fb8f';
    $pane->panel = 'middle_left';
    $pane->type = 'entity_form_field';
    $pane->subtype = 'node:field_p2p_personal_campaign_goal';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => '',
      'formatter' => '',
      'context' => 'argument_node_edit_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 5;
    $pane->locks = array();
    $pane->uuid = '0b89f721-62cf-45cd-aac0-30134c94fb8f';
    $display->content['new-0b89f721-62cf-45cd-aac0-30134c94fb8f'] = $pane;
    $display->panels['middle_left'][5] = 'new-0b89f721-62cf-45cd-aac0-30134c94fb8f';
    $pane = new stdClass();
    $pane->pid = 'new-52627fa7-fd45-4b3a-b20d-9d351ff42fb1';
    $pane->panel = 'middle_left';
    $pane->type = 'entity_form_field';
    $pane->subtype = 'node:field_p2p_personal_submit_goal';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => '',
      'formatter' => '',
      'context' => 'argument_node_edit_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 6;
    $pane->locks = array();
    $pane->uuid = '52627fa7-fd45-4b3a-b20d-9d351ff42fb1';
    $display->content['new-52627fa7-fd45-4b3a-b20d-9d351ff42fb1'] = $pane;
    $display->panels['middle_left'][6] = 'new-52627fa7-fd45-4b3a-b20d-9d351ff42fb1';
    $pane = new stdClass();
    $pane->pid = 'new-73e1b270-94c6-4788-b791-5df8b14e77a8';
    $pane->panel = 'middle_left';
    $pane->type = 'entity_form_field';
    $pane->subtype = 'node:field_p2p_suggested_donation_amt';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => '',
      'formatter' => '',
      'context' => 'argument_node_edit_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 7;
    $pane->locks = array();
    $pane->uuid = '73e1b270-94c6-4788-b791-5df8b14e77a8';
    $display->content['new-73e1b270-94c6-4788-b791-5df8b14e77a8'] = $pane;
    $display->panels['middle_left'][7] = 'new-73e1b270-94c6-4788-b791-5df8b14e77a8';
    $pane = new stdClass();
    $pane->pid = 'new-77b65726-5fdc-40ce-91d8-219aa4a0f175';
    $pane->panel = 'middle_left';
    $pane->type = 'entity_form_field';
    $pane->subtype = 'node:body';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => '',
      'formatter' => '',
      'context' => 'argument_node_edit_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 8;
    $pane->locks = array();
    $pane->uuid = '77b65726-5fdc-40ce-91d8-219aa4a0f175';
    $display->content['new-77b65726-5fdc-40ce-91d8-219aa4a0f175'] = $pane;
    $display->panels['middle_left'][8] = 'new-77b65726-5fdc-40ce-91d8-219aa4a0f175';
    $pane = new stdClass();
    $pane->pid = 'new-a00b7083-cc27-4a9a-9ac4-d333e51f77d7';
    $pane->panel = 'middle_left';
    $pane->type = 'entity_form_field';
    $pane->subtype = 'node:field_p2p_fundraising_deadline';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => '',
      'formatter' => '',
      'context' => 'argument_node_edit_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 9;
    $pane->locks = array();
    $pane->uuid = 'a00b7083-cc27-4a9a-9ac4-d333e51f77d7';
    $display->content['new-a00b7083-cc27-4a9a-9ac4-d333e51f77d7'] = $pane;
    $display->panels['middle_left'][9] = 'new-a00b7083-cc27-4a9a-9ac4-d333e51f77d7';
    $pane = new stdClass();
    $pane->pid = 'new-484bfb5f-f9be-457c-b8cb-bc88334bec9d';
    $pane->panel = 'middle_left';
    $pane->type = 'entity_form_field';
    $pane->subtype = 'node:field_p2p_campaign_images';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => '',
      'formatter' => '',
      'context' => 'argument_node_edit_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 10;
    $pane->locks = array();
    $pane->uuid = '484bfb5f-f9be-457c-b8cb-bc88334bec9d';
    $display->content['new-484bfb5f-f9be-457c-b8cb-bc88334bec9d'] = $pane;
    $display->panels['middle_left'][10] = 'new-484bfb5f-f9be-457c-b8cb-bc88334bec9d';
    $pane = new stdClass();
    $pane->pid = 'new-cac1c486-05f3-495e-8194-5ffda678e1f8';
    $pane->panel = 'middle_left';
    $pane->type = 'entity_form_field';
    $pane->subtype = 'node:field_p2p_video_embed';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => '',
      'formatter' => '',
      'context' => 'argument_node_edit_1',
      'override_title' => 0,
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
    $pane->position = 11;
    $pane->locks = array();
    $pane->uuid = 'cac1c486-05f3-495e-8194-5ffda678e1f8';
    $display->content['new-cac1c486-05f3-495e-8194-5ffda678e1f8'] = $pane;
    $display->panels['middle_left'][11] = 'new-cac1c486-05f3-495e-8194-5ffda678e1f8';
    $pane = new stdClass();
    $pane->pid = 'new-15ce72b0-b6fc-446b-8ab7-fb0e09c153a5';
    $pane->panel = 'middle_left';
    $pane->type = 'node_form_publishing';
    $pane->subtype = 'node_form_publishing';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'role',
          'settings' => array(
            'rids' => array(
              0 => 3,
              1 => 4,
              2 => 5,
            ),
          ),
          'context' => 'logged-in-user',
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
      'context' => 'argument_node_edit_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 12;
    $pane->locks = array();
    $pane->uuid = '15ce72b0-b6fc-446b-8ab7-fb0e09c153a5';
    $display->content['new-15ce72b0-b6fc-446b-8ab7-fb0e09c153a5'] = $pane;
    $display->panels['middle_left'][12] = 'new-15ce72b0-b6fc-446b-8ab7-fb0e09c153a5';
    $pane = new stdClass();
    $pane->pid = 'new-6cbe3107-a4af-4f44-bcf5-49b274267b9b';
    $pane->panel = 'middle_left';
    $pane->type = 'node_form_author';
    $pane->subtype = 'node_form_author';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'role',
          'settings' => array(
            'rids' => array(
              0 => 3,
              1 => 4,
              2 => 5,
            ),
          ),
          'context' => 'logged-in-user',
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
      'context' => 'argument_node_edit_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 13;
    $pane->locks = array();
    $pane->uuid = '6cbe3107-a4af-4f44-bcf5-49b274267b9b';
    $display->content['new-6cbe3107-a4af-4f44-bcf5-49b274267b9b'] = $pane;
    $display->panels['middle_left'][13] = 'new-6cbe3107-a4af-4f44-bcf5-49b274267b9b';
    $pane = new stdClass();
    $pane->pid = 'new-30201ffa-c673-48a8-88e2-17aca3561eec';
    $pane->panel = 'middle_left';
    $pane->type = 'node_form_path';
    $pane->subtype = 'node_form_path';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'role',
          'settings' => array(
            'rids' => array(
              0 => 3,
              1 => 4,
              2 => 5,
            ),
          ),
          'context' => 'logged-in-user',
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
      'context' => 'argument_node_edit_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 14;
    $pane->locks = array();
    $pane->uuid = '30201ffa-c673-48a8-88e2-17aca3561eec';
    $display->content['new-30201ffa-c673-48a8-88e2-17aca3561eec'] = $pane;
    $display->panels['middle_left'][14] = 'new-30201ffa-c673-48a8-88e2-17aca3561eec';
    $pane = new stdClass();
    $pane->pid = 'new-b5cd684f-3174-423c-aacf-8b87921007e6';
    $pane->panel = 'middle_left';
    $pane->type = 'entity_form_field';
    $pane->subtype = 'node:field_ms_ms';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => '',
      'formatter' => '',
      'context' => 'argument_node_edit_1',
      'override_title' => 0,
      'override_title_text' => 'Market Source',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 15;
    $pane->locks = array();
    $pane->uuid = 'b5cd684f-3174-423c-aacf-8b87921007e6';
    $display->content['new-b5cd684f-3174-423c-aacf-8b87921007e6'] = $pane;
    $display->panels['middle_left'][15] = 'new-b5cd684f-3174-423c-aacf-8b87921007e6';
    $pane = new stdClass();
    $pane->pid = 'new-cc1c125a-8abb-41be-ae7a-5a16e26377e7';
    $pane->panel = 'middle_left';
    $pane->type = 'entity_form_field';
    $pane->subtype = 'node:field_ms_cid';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => '',
      'formatter' => '',
      'context' => 'argument_node_edit_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 16;
    $pane->locks = array();
    $pane->uuid = 'cc1c125a-8abb-41be-ae7a-5a16e26377e7';
    $display->content['new-cc1c125a-8abb-41be-ae7a-5a16e26377e7'] = $pane;
    $display->panels['middle_left'][16] = 'new-cc1c125a-8abb-41be-ae7a-5a16e26377e7';
    $pane = new stdClass();
    $pane->pid = 'new-50d768b9-390b-4fc1-81f5-ebd68b31c331';
    $pane->panel = 'middle_left';
    $pane->type = 'entity_form_field';
    $pane->subtype = 'node:field_ms_referrer';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => '',
      'formatter' => '',
      'context' => 'argument_node_edit_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 17;
    $pane->locks = array();
    $pane->uuid = '50d768b9-390b-4fc1-81f5-ebd68b31c331';
    $display->content['new-50d768b9-390b-4fc1-81f5-ebd68b31c331'] = $pane;
    $display->panels['middle_left'][17] = 'new-50d768b9-390b-4fc1-81f5-ebd68b31c331';
    $pane = new stdClass();
    $pane->pid = 'new-2c1fca51-08d8-4ee0-93f8-a12eb278b92a';
    $pane->panel = 'middle_left';
    $pane->type = 'entity_form_field';
    $pane->subtype = 'node:field_ms_initial_referrer';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => '',
      'formatter' => '',
      'context' => 'argument_node_edit_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 18;
    $pane->locks = array();
    $pane->uuid = '2c1fca51-08d8-4ee0-93f8-a12eb278b92a';
    $display->content['new-2c1fca51-08d8-4ee0-93f8-a12eb278b92a'] = $pane;
    $display->panels['middle_left'][18] = 'new-2c1fca51-08d8-4ee0-93f8-a12eb278b92a';
    $pane = new stdClass();
    $pane->pid = 'new-5ddde951-a3c1-4dfd-bda0-6fbf24cb8aa8';
    $pane->panel = 'middle_left';
    $pane->type = 'entity_form_field';
    $pane->subtype = 'node:field_ms_search_engine';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => '',
      'formatter' => '',
      'context' => 'argument_node_edit_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 19;
    $pane->locks = array();
    $pane->uuid = '5ddde951-a3c1-4dfd-bda0-6fbf24cb8aa8';
    $display->content['new-5ddde951-a3c1-4dfd-bda0-6fbf24cb8aa8'] = $pane;
    $display->panels['middle_left'][19] = 'new-5ddde951-a3c1-4dfd-bda0-6fbf24cb8aa8';
    $pane = new stdClass();
    $pane->pid = 'new-551a886e-a806-4505-b015-448cda72677c';
    $pane->panel = 'middle_left';
    $pane->type = 'entity_form_field';
    $pane->subtype = 'node:field_ms_user_agent';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => '',
      'formatter' => '',
      'context' => 'argument_node_edit_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 20;
    $pane->locks = array();
    $pane->uuid = '551a886e-a806-4505-b015-448cda72677c';
    $display->content['new-551a886e-a806-4505-b015-448cda72677c'] = $pane;
    $display->panels['middle_left'][20] = 'new-551a886e-a806-4505-b015-448cda72677c';
    $pane = new stdClass();
    $pane->pid = 'new-3b1545d4-c84e-40b0-8803-62459c67a020';
    $pane->panel = 'middle_left';
    $pane->type = 'node_form_buttons';
    $pane->subtype = 'node_form_buttons';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_node_edit_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 21;
    $pane->locks = array();
    $pane->uuid = '3b1545d4-c84e-40b0-8803-62459c67a020';
    $display->content['new-3b1545d4-c84e-40b0-8803-62459c67a020'] = $pane;
    $display->panels['middle_left'][21] = 'new-3b1545d4-c84e-40b0-8803-62459c67a020';
    $pane = new stdClass();
    $pane->pid = 'new-23e31be4-587c-4714-b87c-2846e075affb';
    $pane->panel = 'middle_right';
    $pane->type = 'help_message';
    $pane->subtype = 'help_message';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'text' => '',
      'override_title' => 0,
      'override_title_text' => 'hello',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'panel-pane-wrapper',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '23e31be4-587c-4714-b87c-2846e075affb';
    $display->content['new-23e31be4-587c-4714-b87c-2846e075affb'] = $pane;
    $display->panels['middle_right'][0] = 'new-23e31be4-587c-4714-b87c-2846e075affb';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['node_edit_panel_context'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view_panel_context_p2p';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -99;
  $handler->conf = array(
    'title' => 'P2P Donation Form',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => 'p2p-donation-form p2p-page-type',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'logic' => 'or',
      'plugins' => array(
        0 => array(
          'name' => 'donation_form',
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
  $display->uuid = '9e04c4cd-58c0-46b0-abeb-edeb642c28de';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-19aeb1b9-6d0f-4c57-9eb0-6944673aa137';
    $pane->panel = 'middle_left';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:body';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'title',
      'formatter' => 'text_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'pane-body',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '19aeb1b9-6d0f-4c57-9eb0-6944673aa137';
    $display->content['new-19aeb1b9-6d0f-4c57-9eb0-6944673aa137'] = $pane;
    $display->panels['middle_left'][0] = 'new-19aeb1b9-6d0f-4c57-9eb0-6944673aa137';
    $pane = new stdClass();
    $pane->pid = 'new-8a8ff94b-c489-4458-8e3c-a097a7f8d45d';
    $pane->panel = 'middle_left';
    $pane->type = 'entity_field_extra';
    $pane->subtype = 'node:webform';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'view_mode' => 'full',
      'context' => 'argument_entity_id:node_1',
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
    $pane->uuid = '8a8ff94b-c489-4458-8e3c-a097a7f8d45d';
    $display->content['new-8a8ff94b-c489-4458-8e3c-a097a7f8d45d'] = $pane;
    $display->panels['middle_left'][1] = 'new-8a8ff94b-c489-4458-8e3c-a097a7f8d45d';
    $pane = new stdClass();
    $pane->pid = 'new-f12b3637-071a-420b-a82e-aad634b71afd';
    $pane->panel = 'middle_right';
    $pane->type = 'personal_campaign_progress';
    $pane->subtype = 'personal_campaign_progress';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => 'test1',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => array(
        'title' => array(
          'prefix' => '',
          'suffix' => '',
        ),
        'content' => array(
          'prefix' => '<div class="panel-pane-wrapper">',
          'suffix' => '',
        ),
        'theme' => 0,
      ),
      'style' => 'wrapper_raw',
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'pane-sidebar ',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'f12b3637-071a-420b-a82e-aad634b71afd';
    $display->content['new-f12b3637-071a-420b-a82e-aad634b71afd'] = $pane;
    $display->panels['middle_right'][0] = 'new-f12b3637-071a-420b-a82e-aad634b71afd';
    $pane = new stdClass();
    $pane->pid = 'new-1dbcc50f-6bbe-4808-a871-7f850969cca9';
    $pane->panel = 'middle_right';
    $pane->type = 'personal_campaign_goal';
    $pane->subtype = 'personal_campaign_goal';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_entity_id:node_1',
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
          'suffix' => '</div>',
        ),
        'theme' => 0,
      ),
      'style' => 'wrapper_raw',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '1dbcc50f-6bbe-4808-a871-7f850969cca9';
    $display->content['new-1dbcc50f-6bbe-4808-a871-7f850969cca9'] = $pane;
    $display->panels['middle_right'][1] = 'new-1dbcc50f-6bbe-4808-a871-7f850969cca9';
    $pane = new stdClass();
    $pane->pid = 'new-96263c63-c874-4a00-8dfb-0eafb7f64c75';
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'pane-top-banner',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '96263c63-c874-4a00-8dfb-0eafb7f64c75';
    $display->content['new-96263c63-c874-4a00-8dfb-0eafb7f64c75'] = $pane;
    $display->panels['top'][0] = 'new-96263c63-c874-4a00-8dfb-0eafb7f64c75';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['node_view_panel_context_p2p'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'pm_existing_pages_p2p_node_panel_context';
  $handler->task = 'pm_existing_pages';
  $handler->subtask = 'p2p_node';
  $handler->handler = 'panel_context';
  $handler->weight = -29;
  $handler->conf = array(
    'title' => 'P2P Donation Form',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => 'p2p-donation-form p2p-page-type',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'logic' => 'and',
      'plugins' => array(
        0 => array(
          'name' => 'donation_form',
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
  $display->uuid = '9e04c4cd-58c0-46b0-abeb-edeb642c28de';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-19aeb1b9-6d0f-4c57-9eb0-6944673aa137';
    $pane->panel = 'middle_left';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:body';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'title',
      'formatter' => 'text_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'pane-body',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '19aeb1b9-6d0f-4c57-9eb0-6944673aa137';
    $display->content['new-19aeb1b9-6d0f-4c57-9eb0-6944673aa137'] = $pane;
    $display->panels['middle_left'][0] = 'new-19aeb1b9-6d0f-4c57-9eb0-6944673aa137';
    $pane = new stdClass();
    $pane->pid = 'new-8a8ff94b-c489-4458-8e3c-a097a7f8d45d';
    $pane->panel = 'middle_left';
    $pane->type = 'entity_field_extra';
    $pane->subtype = 'node:webform';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'view_mode' => 'full',
      'context' => 'argument_entity_id:node_1',
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
    $pane->uuid = '8a8ff94b-c489-4458-8e3c-a097a7f8d45d';
    $display->content['new-8a8ff94b-c489-4458-8e3c-a097a7f8d45d'] = $pane;
    $display->panels['middle_left'][1] = 'new-8a8ff94b-c489-4458-8e3c-a097a7f8d45d';
    $pane = new stdClass();
    $pane->pid = 'new-f12b3637-071a-420b-a82e-aad634b71afd';
    $pane->panel = 'middle_right';
    $pane->type = 'personal_campaign_progress';
    $pane->subtype = 'personal_campaign_progress';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => 'test1',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => array(
        'title' => array(
          'prefix' => '',
          'suffix' => '',
        ),
        'content' => array(
          'prefix' => '<div class="panel-pane-wrapper">',
          'suffix' => '',
        ),
        'theme' => 0,
      ),
      'style' => 'wrapper_raw',
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'pane-sidebar ',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'f12b3637-071a-420b-a82e-aad634b71afd';
    $display->content['new-f12b3637-071a-420b-a82e-aad634b71afd'] = $pane;
    $display->panels['middle_right'][0] = 'new-f12b3637-071a-420b-a82e-aad634b71afd';
    $pane = new stdClass();
    $pane->pid = 'new-1dbcc50f-6bbe-4808-a871-7f850969cca9';
    $pane->panel = 'middle_right';
    $pane->type = 'personal_campaign_goal';
    $pane->subtype = 'personal_campaign_goal';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_entity_id:node_1',
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
          'suffix' => '</div>',
        ),
        'theme' => 0,
      ),
      'style' => 'wrapper_raw',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '1dbcc50f-6bbe-4808-a871-7f850969cca9';
    $display->content['new-1dbcc50f-6bbe-4808-a871-7f850969cca9'] = $pane;
    $display->panels['middle_right'][1] = 'new-1dbcc50f-6bbe-4808-a871-7f850969cca9';
    $pane = new stdClass();
    $pane->pid = 'new-96263c63-c874-4a00-8dfb-0eafb7f64c75';
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'pane-top-banner top-banner',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '96263c63-c874-4a00-8dfb-0eafb7f64c75';
    $display->content['new-96263c63-c874-4a00-8dfb-0eafb7f64c75'] = $pane;
    $display->panels['top'][0] = 'new-96263c63-c874-4a00-8dfb-0eafb7f64c75';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['pm_existing_pages_p2p_node_panel_context'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'pm_existing_pages_p2p_node_panelizer_node';
  $handler->task = 'pm_existing_pages';
  $handler->subtask = 'p2p_node';
  $handler->handler = 'panelizer_node';
  $handler->weight = -28;
  $handler->conf = array(
    'title' => 'P2P Panelizer',
    'contexts' => array(),
    'relationships' => array(),
    'context' => 'argument_entity_id:node_1',
  );
  $export['pm_existing_pages_p2p_node_panelizer_node'] = $handler;

  return $export;
}

/**
 * Implements hook_default_page_manager_pages().
 */
function springboard_p2p_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'p2p_registration_page';
  $page->task = 'page';
  $page->admin_title = 'Springboard P2P registration page';
  $page->admin_description = '';
  $page->path = 'p2p/register';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'perm',
        'settings' => array(
          'perm' => 'register for springboard p2p',
        ),
        'context' => 'logged-in-user',
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_p2p_registration_page_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'p2p_registration_page';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Registration',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => 'p2p-page-type p2p-register-page',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'p2p_threecol_stacked';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'top' => NULL,
      'left' => NULL,
      'middle' => NULL,
      'right' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'Sign up for an Account';
  $display->uuid = '67bb0998-9a48-4122-99a9-08f2b979df70';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-98c8de5f-7ec0-4e9a-a90a-133af5b6c99c';
    $pane->panel = 'left';
    $pane->type = 'fboauth_login';
    $pane->subtype = 'fboauth_login';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'pane-social-login',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '98c8de5f-7ec0-4e9a-a90a-133af5b6c99c';
    $display->content['new-98c8de5f-7ec0-4e9a-a90a-133af5b6c99c'] = $pane;
    $display->panels['left'][0] = 'new-98c8de5f-7ec0-4e9a-a90a-133af5b6c99c';
    $pane = new stdClass();
    $pane->pid = 'new-4258aeae-338f-463f-862a-64f2b307951a';
    $pane->panel = 'middle';
    $pane->type = 'register';
    $pane->subtype = 'register';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'reg-pane',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '4258aeae-338f-463f-862a-64f2b307951a';
    $display->content['new-4258aeae-338f-463f-862a-64f2b307951a'] = $pane;
    $display->panels['middle'][0] = 'new-4258aeae-338f-463f-862a-64f2b307951a';
    $pane = new stdClass();
    $pane->pid = 'new-3f8ff8a6-0965-475e-aeee-484ec16ba512';
    $pane->panel = 'right';
    $pane->type = 'login_intro';
    $pane->subtype = 'login_intro';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'text' => '',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'pane-login',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '3f8ff8a6-0965-475e-aeee-484ec16ba512';
    $display->content['new-3f8ff8a6-0965-475e-aeee-484ec16ba512'] = $pane;
    $display->panels['right'][0] = 'new-3f8ff8a6-0965-475e-aeee-484ec16ba512';
    $pane = new stdClass();
    $pane->pid = 'new-770ce805-317b-4423-8075-448f5441d6b9';
    $pane->panel = 'top';
    $pane->type = 'campaign_header_no_context';
    $pane->subtype = 'campaign_header_no_context';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(),
    );
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'pane-campaign-header',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '770ce805-317b-4423-8075-448f5441d6b9';
    $display->content['new-770ce805-317b-4423-8075-448f5441d6b9'] = $pane;
    $display->panels['top'][0] = 'new-770ce805-317b-4423-8075-448f5441d6b9';
    $pane = new stdClass();
    $pane->pid = 'new-667571e6-db71-468f-a95b-ccba6761872a';
    $pane->panel = 'top';
    $pane->type = 'page_messages';
    $pane->subtype = 'page_messages';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'pane-messages',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '667571e6-db71-468f-a95b-ccba6761872a';
    $display->content['new-667571e6-db71-468f-a95b-ccba6761872a'] = $pane;
    $display->panels['top'][1] = 'new-667571e6-db71-468f-a95b-ccba6761872a';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['p2p_registration_page'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'springboard_p2p_login_page';
  $page->task = 'page';
  $page->admin_title = 'Springboard P2P Login page';
  $page->admin_description = '';
  $page->path = 'p2p/login';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_springboard_p2p_login_page_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'springboard_p2p_login_page';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => 'p2p-page-type p2p-login-page',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'panels_page_title_state' => 0,
    'panels_page_title' => '',
  );
  $display = new panels_display();
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'Login';
  $display->uuid = '8c9c3eb7-fd3b-4739-b087-ccb9e2fa6e82';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-8c4878a3-7ad3-43eb-99ea-be1ab11e3358';
    $pane->panel = 'middle';
    $pane->type = 'campaign_header_no_context';
    $pane->subtype = 'campaign_header_no_context';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'pane-campaign-header',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '8c4878a3-7ad3-43eb-99ea-be1ab11e3358';
    $display->content['new-8c4878a3-7ad3-43eb-99ea-be1ab11e3358'] = $pane;
    $display->panels['middle'][0] = 'new-8c4878a3-7ad3-43eb-99ea-be1ab11e3358';
    $pane = new stdClass();
    $pane->pid = 'new-02324aa6-20f2-4e6d-b2df-09b5f9b6225c';
    $pane->panel = 'middle';
    $pane->type = 'page_messages';
    $pane->subtype = 'page_messages';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'pane-messages',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '02324aa6-20f2-4e6d-b2df-09b5f9b6225c';
    $display->content['new-02324aa6-20f2-4e6d-b2df-09b5f9b6225c'] = $pane;
    $display->panels['middle'][1] = 'new-02324aa6-20f2-4e6d-b2df-09b5f9b6225c';
    $pane = new stdClass();
    $pane->pid = 'new-ec87ad4b-670e-4f49-bac0-a7130a8ce60c';
    $pane->panel = 'middle';
    $pane->type = 'custom_title';
    $pane->subtype = 'custom_title';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'text' => 'Already Registered?',
      'override_title' => 1,
      'override_title_text' => '<No Title>',
      'markup_tag' => 'h1',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'pane-title-wrapper',
    );
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'ec87ad4b-670e-4f49-bac0-a7130a8ce60c';
    $display->content['new-ec87ad4b-670e-4f49-bac0-a7130a8ce60c'] = $pane;
    $display->panels['middle'][2] = 'new-ec87ad4b-670e-4f49-bac0-a7130a8ce60c';
    $pane = new stdClass();
    $pane->pid = 'new-b59ab21a-1e06-4fd3-8250-ced0257e94d7';
    $pane->panel = 'middle';
    $pane->type = 'fboauth_login';
    $pane->subtype = 'fboauth_login';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
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
          'prefix' => '<div class="panel-pane-wrapper pane-login">',
          'suffix' => '',
        ),
        'theme' => 0,
      ),
      'style' => 'wrapper_raw',
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'pane-fb-login',
    );
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = 'b59ab21a-1e06-4fd3-8250-ced0257e94d7';
    $display->content['new-b59ab21a-1e06-4fd3-8250-ced0257e94d7'] = $pane;
    $display->panels['middle'][3] = 'new-b59ab21a-1e06-4fd3-8250-ced0257e94d7';
    $pane = new stdClass();
    $pane->pid = 'new-706eea80-ee1a-4f5f-8450-42c0358c5cd1';
    $pane->panel = 'middle';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => '',
      'title' => '',
      'body' => '<p>OR</p>',
      'format' => 'full_html',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'pane-or',
    );
    $pane->extras = array();
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = '706eea80-ee1a-4f5f-8450-42c0358c5cd1';
    $display->content['new-706eea80-ee1a-4f5f-8450-42c0358c5cd1'] = $pane;
    $display->panels['middle'][4] = 'new-706eea80-ee1a-4f5f-8450-42c0358c5cd1';
    $pane = new stdClass();
    $pane->pid = 'new-bc08a237-4d8b-4f09-9b18-9922f550802b';
    $pane->panel = 'middle';
    $pane->type = 'login';
    $pane->subtype = 'login';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
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
          'suffix' => '</div>',
        ),
        'theme' => 0,
      ),
      'style' => 'wrapper_raw',
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => '',
    );
    $pane->extras = array();
    $pane->position = 5;
    $pane->locks = array();
    $pane->uuid = 'bc08a237-4d8b-4f09-9b18-9922f550802b';
    $display->content['new-bc08a237-4d8b-4f09-9b18-9922f550802b'] = $pane;
    $display->panels['middle'][5] = 'new-bc08a237-4d8b-4f09-9b18-9922f550802b';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-ec87ad4b-670e-4f49-bac0-a7130a8ce60c';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['springboard_p2p_login_page'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'springboard_p2p_password_page';
  $page->task = 'page';
  $page->admin_title = 'Springboard P2P password page';
  $page->admin_description = '';
  $page->path = 'p2p/password';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_springboard_p2p_password_page_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'springboard_p2p_password_page';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => 'p2p-page-type p2p-password-page',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '307e6d0b-84e4-4b4d-8ef9-e9170f78b1cd';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-1860f5f2-8a8a-4f03-838c-6ecbfc2e6a1d';
    $pane->panel = 'middle';
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
    $pane->uuid = '1860f5f2-8a8a-4f03-838c-6ecbfc2e6a1d';
    $display->content['new-1860f5f2-8a8a-4f03-838c-6ecbfc2e6a1d'] = $pane;
    $display->panels['middle'][0] = 'new-1860f5f2-8a8a-4f03-838c-6ecbfc2e6a1d';
    $pane = new stdClass();
    $pane->pid = 'new-73b09de7-23be-4a7d-91c2-d943c856b0f0';
    $pane->panel = 'middle';
    $pane->type = 'custom_title';
    $pane->subtype = 'custom_title';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'text' => 'Password Reset',
      'override_title' => 1,
      'override_title_text' => '<no title>',
      'markup_tag' => 'h1',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'pane-title-wrapper',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '73b09de7-23be-4a7d-91c2-d943c856b0f0';
    $display->content['new-73b09de7-23be-4a7d-91c2-d943c856b0f0'] = $pane;
    $display->panels['middle'][1] = 'new-73b09de7-23be-4a7d-91c2-d943c856b0f0';
    $pane = new stdClass();
    $pane->pid = 'new-f36d6008-3741-4361-813c-67df2c9c883b';
    $pane->panel = 'middle';
    $pane->type = 'page_messages';
    $pane->subtype = 'page_messages';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'f36d6008-3741-4361-813c-67df2c9c883b';
    $display->content['new-f36d6008-3741-4361-813c-67df2c9c883b'] = $pane;
    $display->panels['middle'][2] = 'new-f36d6008-3741-4361-813c-67df2c9c883b';
    $pane = new stdClass();
    $pane->pid = 'new-5313fd09-1801-49f3-9129-8c8e27ebbe67';
    $pane->panel = 'middle';
    $pane->type = 'request_password_reset';
    $pane->subtype = 'request_password_reset';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => 'dfd',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'pane-password',
    );
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '5313fd09-1801-49f3-9129-8c8e27ebbe67';
    $display->content['new-5313fd09-1801-49f3-9129-8c8e27ebbe67'] = $pane;
    $display->panels['middle'][3] = 'new-5313fd09-1801-49f3-9129-8c8e27ebbe67';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-1860f5f2-8a8a-4f03-838c-6ecbfc2e6a1d';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['springboard_p2p_password_page'] = $page;

  return $pages;

}
