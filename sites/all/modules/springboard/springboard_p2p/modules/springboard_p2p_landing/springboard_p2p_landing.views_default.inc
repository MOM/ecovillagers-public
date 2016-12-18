<?php
/**
 * @file
 * springboard_p2p_landing.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function springboard_p2p_landing_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'p2p_campaign_landing_slideshow';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'P2P Campaign Landing Slideshow';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['css_class'] = 'p2p-campaign-landing-slideshow';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['pure_distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '4';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['class'] = 'slides';
  $handler->display->display_options['style_options']['wrapper_class'] = 'flexslider';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_p2p_slide_show_node']['id'] = 'reverse_field_p2p_slide_show_node';
  $handler->display->display_options['relationships']['reverse_field_p2p_slide_show_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_p2p_slide_show_node']['field'] = 'reverse_field_p2p_slide_show_node';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_p2p_slide_show_target_id']['id'] = 'field_p2p_slide_show_target_id';
  $handler->display->display_options['relationships']['field_p2p_slide_show_target_id']['table'] = 'field_data_field_p2p_slide_show';
  $handler->display->display_options['relationships']['field_p2p_slide_show_target_id']['field'] = 'field_p2p_slide_show_target_id';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Landing page slider */
  $handler->display->display_options['fields']['field_p2p_campaign_slider']['id'] = 'field_p2p_campaign_slider';
  $handler->display->display_options['fields']['field_p2p_campaign_slider']['table'] = 'field_data_field_p2p_campaign_slider';
  $handler->display->display_options['fields']['field_p2p_campaign_slider']['field'] = 'field_p2p_campaign_slider';
  $handler->display->display_options['fields']['field_p2p_campaign_slider']['label'] = '';
  $handler->display->display_options['fields']['field_p2p_campaign_slider']['element_type'] = '0';
  $handler->display->display_options['fields']['field_p2p_campaign_slider']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_p2p_campaign_slider']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_p2p_campaign_slider']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_p2p_campaign_slider']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_p2p_campaign_slider']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_p2p_campaign_slider']['settings'] = array(
    'image_style' => 'campaign_image_slideshow',
    'image_link' => '',
  );
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['element_type'] = 'span';
  $handler->display->display_options['fields']['edit_node']['element_class'] = 'node-edit';
  $handler->display->display_options['fields']['edit_node']['element_label_type'] = '0';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_node']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['edit_node']['element_default_classes'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['text'] = '<a href="/p2p/register?p2p_cid=[nid]" >Get Started</a>';
  $handler->display->display_options['fields']['nid']['element_type'] = 'span';
  $handler->display->display_options['fields']['nid']['element_class'] = 'slide-link';
  $handler->display->display_options['fields']['nid']['element_label_type'] = '0';
  $handler->display->display_options['fields']['nid']['element_wrapper_type'] = '0';
  /* Sort criterion: Content: Slide Show (field_p2p_slide_show:delta) */
  $handler->display->display_options['sorts']['delta']['id'] = 'delta';
  $handler->display->display_options['sorts']['delta']['table'] = 'field_data_field_p2p_slide_show';
  $handler->display->display_options['sorts']['delta']['field'] = 'delta';
  $handler->display->display_options['sorts']['delta']['relationship'] = 'field_p2p_slide_show_target_id';
  $handler->display->display_options['sorts']['delta']['order'] = 'DESC';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'reverse_field_p2p_slide_show_node';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'p2p_campaign' => 'p2p_campaign',
  );
  /* Filter criterion: Content: Landing page slider (field_p2p_campaign_slider:fid) */
  $handler->display->display_options['filters']['field_p2p_campaign_slider_fid']['id'] = 'field_p2p_campaign_slider_fid';
  $handler->display->display_options['filters']['field_p2p_campaign_slider_fid']['table'] = 'field_data_field_p2p_campaign_slider';
  $handler->display->display_options['filters']['field_p2p_campaign_slider_fid']['field'] = 'field_p2p_campaign_slider_fid';
  $handler->display->display_options['filters']['field_p2p_campaign_slider_fid']['operator'] = 'not empty';

  /* Display: Slideshow */
  $handler = $view->new_display('panel_pane', 'Slideshow', 'panel_pane_1');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Landing page slider */
  $handler->display->display_options['fields']['field_p2p_campaign_slider']['id'] = 'field_p2p_campaign_slider';
  $handler->display->display_options['fields']['field_p2p_campaign_slider']['table'] = 'field_data_field_p2p_campaign_slider';
  $handler->display->display_options['fields']['field_p2p_campaign_slider']['field'] = 'field_p2p_campaign_slider';
  $handler->display->display_options['fields']['field_p2p_campaign_slider']['label'] = '';
  $handler->display->display_options['fields']['field_p2p_campaign_slider']['element_type'] = '0';
  $handler->display->display_options['fields']['field_p2p_campaign_slider']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_p2p_campaign_slider']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_p2p_campaign_slider']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_p2p_campaign_slider']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_p2p_campaign_slider']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_p2p_campaign_slider']['settings'] = array(
    'image_style' => 'p2p_campaign_image_slideshow',
    'image_link' => '',
  );
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['element_type'] = 'span';
  $handler->display->display_options['fields']['edit_node']['element_class'] = 'node-edit';
  $handler->display->display_options['fields']['edit_node']['element_label_type'] = '0';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_node']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['edit_node']['element_default_classes'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['text'] = '<a href="/p2p/register?p2p_cid=[nid]" >Get Started</a>';
  $handler->display->display_options['fields']['nid']['element_type'] = 'span';
  $handler->display->display_options['fields']['nid']['element_class'] = 'slide-link';
  $handler->display->display_options['fields']['nid']['element_label_type'] = '0';
  $handler->display->display_options['fields']['nid']['element_wrapper_type'] = '0';
  /* Field: Content: Landing page slider teaser */
  $handler->display->display_options['fields']['field_p2p_landing_slider_text']['id'] = 'field_p2p_landing_slider_text';
  $handler->display->display_options['fields']['field_p2p_landing_slider_text']['table'] = 'field_data_field_p2p_landing_slider_text';
  $handler->display->display_options['fields']['field_p2p_landing_slider_text']['field'] = 'field_p2p_landing_slider_text';
  $handler->display->display_options['fields']['field_p2p_landing_slider_text']['label'] = '';
  $handler->display->display_options['fields']['field_p2p_landing_slider_text']['element_type'] = 'span';
  $handler->display->display_options['fields']['field_p2p_landing_slider_text']['element_class'] = 'slider-teaser';
  $handler->display->display_options['fields']['field_p2p_landing_slider_text']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_p2p_landing_slider_text']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_p2p_landing_slider_text']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_p2p_landing_slider_text']['element_default_classes'] = FALSE;
  /* Field: Content: External Link? */
  $handler->display->display_options['fields']['field_p2p_external_link']['id'] = 'field_p2p_external_link';
  $handler->display->display_options['fields']['field_p2p_external_link']['table'] = 'field_data_field_p2p_external_link';
  $handler->display->display_options['fields']['field_p2p_external_link']['field'] = 'field_p2p_external_link';
  $handler->display->display_options['fields']['field_p2p_external_link']['label'] = '';
  $handler->display->display_options['fields']['field_p2p_external_link']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_p2p_external_link']['element_type'] = '0';
  $handler->display->display_options['fields']['field_p2p_external_link']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_p2p_external_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_p2p_external_link']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_p2p_external_link']['element_default_classes'] = FALSE;
  /* Field: Content: Landing page slider optional external link */
  $handler->display->display_options['fields']['field_p2p_landing_slider_link']['id'] = 'field_p2p_landing_slider_link';
  $handler->display->display_options['fields']['field_p2p_landing_slider_link']['table'] = 'field_data_field_p2p_landing_slider_link';
  $handler->display->display_options['fields']['field_p2p_landing_slider_link']['field'] = 'field_p2p_landing_slider_link';
  $handler->display->display_options['fields']['field_p2p_landing_slider_link']['label'] = '';
  $handler->display->display_options['fields']['field_p2p_landing_slider_link']['element_type'] = 'span';
  $handler->display->display_options['fields']['field_p2p_landing_slider_link']['element_class'] = 'external-link';
  $handler->display->display_options['fields']['field_p2p_landing_slider_link']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_p2p_landing_slider_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_p2p_landing_slider_link']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_p2p_landing_slider_link']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_p2p_landing_slider_link']['click_sort_column'] = 'url';
  /* Field: Views: Views Conditional */
  $handler->display->display_options['fields']['views_conditional']['id'] = 'views_conditional';
  $handler->display->display_options['fields']['views_conditional']['table'] = 'views_conditional';
  $handler->display->display_options['fields']['views_conditional']['field'] = 'views_conditional';
  $handler->display->display_options['fields']['views_conditional']['label'] = '';
  $handler->display->display_options['fields']['views_conditional']['element_type'] = 'span';
  $handler->display->display_options['fields']['views_conditional']['element_class'] = 'conditional-link slide-link';
  $handler->display->display_options['fields']['views_conditional']['element_label_type'] = '0';
  $handler->display->display_options['fields']['views_conditional']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_conditional']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['views_conditional']['if'] = 'field_p2p_external_link';
  $handler->display->display_options['fields']['views_conditional']['condition'] = '7';
  $handler->display->display_options['fields']['views_conditional']['equalto'] = 'yes';
  $handler->display->display_options['fields']['views_conditional']['then'] = '[field_p2p_landing_slider_link]';
  $handler->display->display_options['fields']['views_conditional']['or'] = '[nid]';
  $handler->display->display_options['pane_category']['name'] = 'Springboard P2P';
  $handler->display->display_options['pane_category']['weight'] = '0';
  $export['p2p_campaign_landing_slideshow'] = $view;

  $view = new view();
  $view->name = 'p2p_landing_pages';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'P2P landing pages';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'P2P landing pages';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer springboard p2p';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'edit_node' => 'edit_node',
    'view_node' => 'edit_node',
    'clone_node' => 'edit_node',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => ' | ',
      'empty_column' => 0,
    ),
    'view_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'clone_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Action';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  /* Field: Content: Clone link */
  $handler->display->display_options['fields']['clone_node']['id'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['table'] = 'node';
  $handler->display->display_options['fields']['clone_node']['field'] = 'clone_node';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'p2p_campaign_landing' => 'p2p_campaign_landing',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::node_assign_owner_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_sticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_unsticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::node_promote_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_publish_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpromote_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_save_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::panelizer_set_status_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::_fundraiser_gateway_switch_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_by_keyword_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::pathauto_node_update_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Edit';
  /* Field: Content: Clone link */
  $handler->display->display_options['fields']['clone_node']['id'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['table'] = 'node';
  $handler->display->display_options['fields']['clone_node']['field'] = 'clone_node';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'p2p_campaign_landing' => 'p2p_campaign_landing',
  );
  /* Filter criterion: Global: Combine fields filter */
  $handler->display->display_options['filters']['combine']['id'] = 'combine';
  $handler->display->display_options['filters']['combine']['table'] = 'views';
  $handler->display->display_options['filters']['combine']['field'] = 'combine';
  $handler->display->display_options['filters']['combine']['operator'] = 'contains';
  $handler->display->display_options['filters']['combine']['exposed'] = TRUE;
  $handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['identifier'] = 'combine';
  $handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['combine']['fields'] = array(
    'title' => 'title',
  );
  /* Filter criterion: Date: Date (node) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = 'between';
  $handler->display->display_options['filters']['date_filter']['exposed'] = TRUE;
  $handler->display->display_options['filters']['date_filter']['expose']['operator_id'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['operator'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['identifier'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['date_filter']['form_type'] = 'date_popup';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'node.created' => 'node.created',
  );
  $handler->display->display_options['path'] = 'admin/springboard/p2p/landing-pages';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Landing pages';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $export['p2p_landing_pages'] = $view;

  $view = new view();
  $view->name = 'p2p_referenced_campaigns';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'P2P Campaign Landing Your P2P';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['css_class'] = 'campaign-landing-view';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '4';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['class'] = 'campaign-landing-grid';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_p2p_referenced_campaigns_node']['id'] = 'reverse_field_p2p_referenced_campaigns_node';
  $handler->display->display_options['relationships']['reverse_field_p2p_referenced_campaigns_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_p2p_referenced_campaigns_node']['field'] = 'reverse_field_p2p_referenced_campaigns_node';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_p2p_referenced_campaigns_target_id']['id'] = 'field_p2p_referenced_campaigns_target_id';
  $handler->display->display_options['relationships']['field_p2p_referenced_campaigns_target_id']['table'] = 'field_data_field_p2p_referenced_campaigns';
  $handler->display->display_options['relationships']['field_p2p_referenced_campaigns_target_id']['field'] = 'field_p2p_referenced_campaigns_target_id';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'h2';
  $handler->display->display_options['fields']['title']['element_class'] = 'p2p-thumb-title';
  $handler->display->display_options['fields']['title']['element_label_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Campaign thumbnail */
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['id'] = 'field_p2p_campaign_thumbnail';
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['table'] = 'field_data_field_p2p_campaign_thumbnail';
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['field'] = 'field_p2p_campaign_thumbnail';
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['label'] = '';
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['element_type'] = '0';
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['settings'] = array(
    'image_style' => 'campaign_image_landing',
    'image_link' => '',
  );
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '120';
  $handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['body']['element_type'] = 'p';
  $handler->display->display_options['fields']['body']['element_label_type'] = '0';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_wrapper_type'] = '0';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['text'] = '<a href="/p2p/register?p2p_cid=[nid]" >Get Started</a>';
  $handler->display->display_options['fields']['nid']['element_type'] = 'span';
  $handler->display->display_options['fields']['nid']['element_class'] = 'campaign-node-link';
  $handler->display->display_options['fields']['nid']['element_label_type'] = '0';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_wrapper_type'] = '0';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['element_type'] = 'span';
  $handler->display->display_options['fields']['edit_node']['element_class'] = 'node-edit';
  $handler->display->display_options['fields']['edit_node']['element_label_type'] = '0';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_node']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['edit_node']['element_default_classes'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'reverse_field_p2p_referenced_campaigns_node';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'p2p_campaign' => 'p2p_campaign',
  );

  /* Display: Your P2P (Grid) */
  $handler = $view->new_display('panel_pane', 'Your P2P (Grid)', 'panel_pane_1');
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '6';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['defaults']['empty'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'h2';
  $handler->display->display_options['fields']['title']['element_class'] = 'p2p-thumb-title';
  $handler->display->display_options['fields']['title']['element_label_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Campaign thumbnail */
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['id'] = 'field_p2p_campaign_thumbnail';
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['table'] = 'field_data_field_p2p_campaign_thumbnail';
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['field'] = 'field_p2p_campaign_thumbnail';
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['label'] = '';
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['element_type'] = '0';
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['settings'] = array(
    'image_style' => 'p2p_campaign_image_landing',
    'image_link' => '',
  );
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '120';
  $handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['body']['element_type'] = 'p';
  $handler->display->display_options['fields']['body']['element_label_type'] = '0';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_wrapper_type'] = '0';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['text'] = '<a href="/p2p/register?p2p_cid=[nid]" >Get Started</a>';
  $handler->display->display_options['fields']['nid']['element_type'] = 'span';
  $handler->display->display_options['fields']['nid']['element_class'] = 'campaign-node-link';
  $handler->display->display_options['fields']['nid']['element_label_type'] = '0';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_wrapper_type'] = '0';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['element_type'] = 'span';
  $handler->display->display_options['fields']['view_node']['element_class'] = 'campaign-node-link learn-more';
  $handler->display->display_options['fields']['view_node']['element_label_type'] = '0';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['view_node']['text'] = 'Learn more';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['element_type'] = 'span';
  $handler->display->display_options['fields']['edit_node']['element_class'] = 'node-edit';
  $handler->display->display_options['fields']['edit_node']['element_label_type'] = '0';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_node']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['edit_node']['element_default_classes'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Start your own campaign (field_p2p_referenced_campaigns:delta) */
  $handler->display->display_options['sorts']['delta']['id'] = 'delta';
  $handler->display->display_options['sorts']['delta']['table'] = 'field_data_field_p2p_referenced_campaigns';
  $handler->display->display_options['sorts']['delta']['field'] = 'delta';
  $handler->display->display_options['pane_category']['name'] = 'Springboard P2P';
  $handler->display->display_options['pane_category']['weight'] = '0';

  /* Display: Featured Personal */
  $handler = $view->new_display('panel_pane', 'Featured Personal', 'panel_pane_2');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'campaign-landing-featured-view';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '3';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_p2p_feature_pers_campaigns_node']['id'] = 'reverse_field_p2p_feature_pers_campaigns_node';
  $handler->display->display_options['relationships']['reverse_field_p2p_feature_pers_campaigns_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_p2p_feature_pers_campaigns_node']['field'] = 'reverse_field_p2p_feature_pers_campaigns_node';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_p2p_feature_pers_campaigns_target_id']['id'] = 'field_p2p_feature_pers_campaigns_target_id';
  $handler->display->display_options['relationships']['field_p2p_feature_pers_campaigns_target_id']['table'] = 'field_data_field_p2p_feature_pers_campaigns';
  $handler->display->display_options['relationships']['field_p2p_feature_pers_campaigns_target_id']['field'] = 'field_p2p_feature_pers_campaigns_target_id';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_p2p_campaign_target_id']['id'] = 'field_p2p_campaign_target_id';
  $handler->display->display_options['relationships']['field_p2p_campaign_target_id']['table'] = 'field_data_field_p2p_campaign';
  $handler->display->display_options['relationships']['field_p2p_campaign_target_id']['field'] = 'field_p2p_campaign_target_id';
  $handler->display->display_options['relationships']['field_p2p_campaign_target_id']['label'] = 'Campaign Content entity referenced from field_p2p_campaign';
  $handler->display->display_options['relationships']['field_p2p_campaign_target_id']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Personal campaign action button label */
  $handler->display->display_options['fields']['field_p2p_campaign_action_button']['id'] = 'field_p2p_campaign_action_button';
  $handler->display->display_options['fields']['field_p2p_campaign_action_button']['table'] = 'field_data_field_p2p_campaign_action_button';
  $handler->display->display_options['fields']['field_p2p_campaign_action_button']['field'] = 'field_p2p_campaign_action_button';
  $handler->display->display_options['fields']['field_p2p_campaign_action_button']['relationship'] = 'field_p2p_campaign_target_id';
  $handler->display->display_options['fields']['field_p2p_campaign_action_button']['label'] = '';
  $handler->display->display_options['fields']['field_p2p_campaign_action_button']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_p2p_campaign_action_button']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'h2';
  $handler->display->display_options['fields']['title']['element_class'] = 'p2p-thumb-title';
  $handler->display->display_options['fields']['title']['element_label_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Upload a Campaign Image */
  $handler->display->display_options['fields']['field_p2p_campaign_images']['id'] = 'field_p2p_campaign_images';
  $handler->display->display_options['fields']['field_p2p_campaign_images']['table'] = 'field_data_field_p2p_campaign_images';
  $handler->display->display_options['fields']['field_p2p_campaign_images']['field'] = 'field_p2p_campaign_images';
  $handler->display->display_options['fields']['field_p2p_campaign_images']['element_type'] = '0';
  $handler->display->display_options['fields']['field_p2p_campaign_images']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_p2p_campaign_images']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_p2p_campaign_images']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_p2p_campaign_images']['settings'] = array(
    'image_style' => 'p2p_campaign_image_landing',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_p2p_campaign_images']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_p2p_campaign_images']['delta_offset'] = '0';
  /* Field: Content: Campaign thumbnail */
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['id'] = 'field_p2p_campaign_thumbnail';
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['table'] = 'field_data_field_p2p_campaign_thumbnail';
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['field'] = 'field_p2p_campaign_thumbnail';
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['label'] = '';
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['element_type'] = '0';
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_p2p_campaign_thumbnail']['settings'] = array(
    'image_style' => 'p2p_campaign_image_landing',
    'image_link' => '',
  );
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '120';
  $handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['body']['element_type'] = 'p';
  $handler->display->display_options['fields']['body']['element_label_type'] = '0';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_wrapper_type'] = '0';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['view_node']['alter']['text'] = '[field_p2p_campaign_action_button]';
  $handler->display->display_options['fields']['view_node']['element_type'] = 'span';
  $handler->display->display_options['fields']['view_node']['element_class'] = 'campaign-node-link';
  $handler->display->display_options['fields']['view_node']['element_label_type'] = '0';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['view_node']['element_default_classes'] = FALSE;
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node_1']['id'] = 'view_node_1';
  $handler->display->display_options['fields']['view_node_1']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node_1']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node_1']['label'] = '';
  $handler->display->display_options['fields']['view_node_1']['element_type'] = 'span';
  $handler->display->display_options['fields']['view_node_1']['element_class'] = 'campaign-node-link learn-more';
  $handler->display->display_options['fields']['view_node_1']['element_label_type'] = '0';
  $handler->display->display_options['fields']['view_node_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node_1']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['view_node_1']['text'] = 'Learn more';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['element_type'] = 'span';
  $handler->display->display_options['fields']['edit_node']['element_class'] = 'node-edit';
  $handler->display->display_options['fields']['edit_node']['element_label_type'] = '0';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_node']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['edit_node']['element_default_classes'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Featured Personal Campaigns (field_p2p_feature_pers_campaigns:delta) */
  $handler->display->display_options['sorts']['delta']['id'] = 'delta';
  $handler->display->display_options['sorts']['delta']['table'] = 'field_data_field_p2p_feature_pers_campaigns';
  $handler->display->display_options['sorts']['delta']['field'] = 'delta';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'reverse_field_p2p_feature_pers_campaigns_node';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'p2p_personal_campaign' => 'p2p_personal_campaign',
  );
  $handler->display->display_options['pane_category']['name'] = 'Springboard P2P';
  $handler->display->display_options['pane_category']['weight'] = '0';
  $export['p2p_referenced_campaigns'] = $view;

  $view = new view();
  $view->name = 'p2p_search_for_a_campaign';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'P2P Search for a Campaign';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['css_class'] = 'landing-search-view';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'input_required';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['exposed_form']['options']['text_input_required_format'] = 'filtered_html';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '4';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: P2P: User requesting approval. */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'springboard_p2p_private_campaign_approval';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['relationships']['uid_1']['table'] = 'node';
  $handler->display->display_options['relationships']['uid_1']['field'] = 'uid';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'p2p_personal_campaign' => 'p2p_personal_campaign',
  );

  /* Display: Search widget exposed form */
  $handler = $view->new_display('panel_pane', 'Search widget exposed form', 'panel_pane_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_always'] = TRUE;
  $handler->display->display_options['defaults']['use_more_text'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '4';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'sbp_first_name' => 'sbp_first_name',
    'sbp_last_name' => 'sbp_first_name',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-left',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sbp_first_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-left',
      'separator' => ' ',
      'empty_column' => 0,
    ),
    'sbp_last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['exposed_block'] = TRUE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<h4 class="search-results">Search results</h4>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['footer'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: P2P: User requesting approval. */
  $handler->display->display_options['relationships']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['relationships']['uid_1']['table'] = 'springboard_p2p_private_campaign_approval';
  $handler->display->display_options['relationships']['uid_1']['field'] = 'uid';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  /* Field: User: First name */
  $handler->display->display_options['fields']['sbp_first_name']['id'] = 'sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['table'] = 'field_data_sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['field'] = 'sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['sbp_first_name']['label'] = 'Name';
  $handler->display->display_options['fields']['sbp_first_name']['element_type'] = '0';
  $handler->display->display_options['fields']['sbp_first_name']['element_label_type'] = '0';
  $handler->display->display_options['fields']['sbp_first_name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['sbp_first_name']['element_wrapper_type'] = '0';
  /* Field: User: Last name */
  $handler->display->display_options['fields']['sbp_last_name']['id'] = 'sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['table'] = 'field_data_sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['field'] = 'sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['sbp_last_name']['label'] = '';
  $handler->display->display_options['fields']['sbp_last_name']['element_type'] = '0';
  $handler->display->display_options['fields']['sbp_last_name']['element_label_type'] = '0';
  $handler->display->display_options['fields']['sbp_last_name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['sbp_last_name']['element_wrapper_type'] = '0';
  /* Field: User: E-mail */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['relationship'] = 'uid';
  $handler->display->display_options['fields']['mail']['exclude'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'p2p_personal_campaign' => 'p2p_personal_campaign',
  );
  /* Filter criterion: Global: Combine fields filter */
  $handler->display->display_options['filters']['combine']['id'] = 'combine';
  $handler->display->display_options['filters']['combine']['table'] = 'views';
  $handler->display->display_options['filters']['combine']['field'] = 'combine';
  $handler->display->display_options['filters']['combine']['operator'] = 'contains';
  $handler->display->display_options['filters']['combine']['exposed'] = TRUE;
  $handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['identifier'] = 'combine';
  $handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['combine']['fields'] = array(
    'title' => 'title',
    'sbp_first_name' => 'sbp_first_name',
    'sbp_last_name' => 'sbp_last_name',
    'mail' => 'mail',
  );
  $handler->display->display_options['pane_category']['name'] = 'Springboard P2P';
  $handler->display->display_options['pane_category']['weight'] = '0';
  $handler->display->display_options['link_to_view'] = '0';
  $handler->display->display_options['inherit_panels_path'] = '1';

  /* Display: Search widget */
  $handler = $view->new_display('block', 'Search widget', 'block_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_always'] = TRUE;
  $handler->display->display_options['defaults']['use_more_text'] = FALSE;
  $handler->display->display_options['defaults']['footer'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'p2p_personal_campaign' => 'p2p_personal_campaign',
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );

  /* Display: Search Results */
  $handler = $view->new_display('page', 'Search Results', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Search results';
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'landing-search-view-page';
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_always'] = TRUE;
  $handler->display->display_options['defaults']['use_more_text'] = FALSE;
  $handler->display->display_options['use_more_text'] = '';
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '8';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'sbp_first_name' => 'sbp_first_name',
    'sbp_last_name' => 'sbp_first_name',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-left',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sbp_first_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-left',
      'separator' => ' ',
      'empty_column' => 0,
    ),
    'sbp_last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: User: First name */
  $handler->display->display_options['fields']['sbp_first_name']['id'] = 'sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['table'] = 'field_data_sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['field'] = 'sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['relationship'] = 'uid_1';
  $handler->display->display_options['fields']['sbp_first_name']['label'] = 'Name';
  $handler->display->display_options['fields']['sbp_first_name']['element_type'] = '0';
  $handler->display->display_options['fields']['sbp_first_name']['element_label_type'] = '0';
  $handler->display->display_options['fields']['sbp_first_name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['sbp_first_name']['element_wrapper_type'] = '0';
  /* Field: User: Last name */
  $handler->display->display_options['fields']['sbp_last_name']['id'] = 'sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['table'] = 'field_data_sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['field'] = 'sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['relationship'] = 'uid_1';
  $handler->display->display_options['fields']['sbp_last_name']['label'] = '';
  $handler->display->display_options['fields']['sbp_last_name']['element_type'] = '0';
  $handler->display->display_options['fields']['sbp_last_name']['element_label_type'] = '0';
  $handler->display->display_options['fields']['sbp_last_name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['sbp_last_name']['element_wrapper_type'] = '0';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'p2p_personal_campaign' => 'p2p_personal_campaign',
  );
  /* Filter criterion: Global: Combine fields filter */
  $handler->display->display_options['filters']['combine']['id'] = 'combine';
  $handler->display->display_options['filters']['combine']['table'] = 'views';
  $handler->display->display_options['filters']['combine']['field'] = 'combine';
  $handler->display->display_options['filters']['combine']['operator'] = 'contains';
  $handler->display->display_options['filters']['combine']['fields'] = array(
    'title' => 'title',
    'sbp_first_name' => 'sbp_first_name',
    'sbp_last_name' => 'sbp_last_name',
  );
  $handler->display->display_options['path'] = 'peer-to-peer-campaign-search';
  $export['p2p_search_for_a_campaign'] = $view;

  return $export;
}
