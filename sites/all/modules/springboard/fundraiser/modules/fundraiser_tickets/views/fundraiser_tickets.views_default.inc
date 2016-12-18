<?php
/**
 * @file
 * fundraiser_tickets_views.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function fundraiser_tickets_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'donation_forms';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Donation forms';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  
  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Fundraiser donation forms: Fundraiser node */
  $handler->display->display_options['relationships']['nid']['id'] = 'nid';
  $handler->display->display_options['relationships']['nid']['table'] = 'fundraiser';
  $handler->display->display_options['relationships']['nid']['field'] = 'nid';
  /* Field: Content: Internal Name */
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['id'] = 'field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['table'] = 'field_data_field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['field'] = 'field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['label'] = '';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[field_fundraiser_internal_name] ([title])';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Sort criterion: Content: Internal Name (field_fundraiser_internal_name) */
  $handler->display->display_options['sorts']['field_fundraiser_internal_name_value']['id'] = 'field_fundraiser_internal_name_value';
  $handler->display->display_options['sorts']['field_fundraiser_internal_name_value']['table'] = 'field_data_field_fundraiser_internal_name';
  $handler->display->display_options['sorts']['field_fundraiser_internal_name_value']['field'] = 'field_fundraiser_internal_name_value';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  
  /* Filter criterion: Fundraiser donation forms: Show other amount */
  $handler->display->display_options['filters']['show_other_amount']['id'] = 'show_other_amount';
  $handler->display->display_options['filters']['show_other_amount']['table'] = 'fundraiser';
  $handler->display->display_options['filters']['show_other_amount']['field'] = 'show_other_amount';
  $handler->display->display_options['filters']['show_other_amount']['value'] = '1';
  
  /* Display: Entity Reference */
  $handler = $view->new_display('entityreference', 'Entity Reference', 'entityreference_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'field_fundraiser_internal_name' => 'field_fundraiser_internal_name',
    'title' => 0,
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $export['donation_forms'] = $view;

  return $export;
}
