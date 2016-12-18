<?php

/**
 * @file
 * Plugin to display a personal campaign's share links.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('Personal campaign share links'),
  'description' => t('Displays the P2P personal campaign share links.'),
  'category' => t('Springboard P2P'),
  // Despite having no "settings" we need this function to pass back a form,
  // or we'll loose the context and title settings.
  'edit form' => 'springboard_p2p_personal_campaign_share_edit_form',
  'render callback' => 'springboard_p2p_personal_campaign_share_render',
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Render a single content pane.
 */
function springboard_p2p_personal_campaign_share_render($subtype, $conf, $panel_args, $context) {
  
  // Only render this if the sb_social module is enabled.
  if (!module_exists('sb_social')) {
    return;
  }
  
  // Find out which node types are enabled for sb_share. If the current
  // node, from $context, isn't among those enabled types, return empty.
  $enabled_sb_share_types = variable_get('springboard_social_enabled_content_types', NULL);
  if (isset($context->data) && isset($context->data->type)) {
    $node_type = $context->data->type;
    if (!in_array($node_type, $enabled_sb_share_types, TRUE)) {
      return;
    }
  }
  
  $personal_campaign = NULL;
  if (empty($context) || empty($context->data)) {
    if (isset($_GET['p2p_pcid']) && is_numeric($_GET['p2p_pcid'])) {
      $personal_campaign = node_load($_GET['p2p_pcid']);
    }
    else {
      return;
    }
  }
  else {
    $personal_campaign = $context->data;
  }

  if (!isset($personal_campaign->type) || $personal_campaign->type != 'p2p_personal_campaign' || !isset($personal_campaign->field_p2p_campaign[$personal_campaign->language][0]['target_id'])) {
    return;
  }
  else {
    $campaign = node_load($personal_campaign->field_p2p_campaign[$personal_campaign->language][0]['target_id']);
  }

  $output = array();

  // Social settings.
  $sid = _sb_social_sid_by_id($personal_campaign->nid);
  $settings = sb_social_settings_load($sid);

  $buttons = array();
  $plugins = sb_social_get_enabled_plugins();
  // Render button for each enabled service.
  foreach ($plugins as $service => $plugin) {
    $vars['service'] = $service;
    $vars['extra'] = '';
    $vars['contents'] = isset($plugin['button_contents']) ? $plugin['button_contents'] : '';

    if (isset($plugin['button_extra'])) {
      $func = $plugin['button_extra'];
      if (function_exists($func)) {
        $vars['extra'] = $func($settings['data'][$service], $personal_campaign);
      }
    }
    $buttons[] = theme('sb_social_share_button', $vars);
  }
  $buttons = implode("\n", $buttons);

  $output[] = '<i class="fa fa-share-alt share-icon"></i>';
  $output[] = theme('sb_social_share', array('buttons' => $buttons));

  // Build the content type block.
  $block = new stdClass();
  $block->title = 'Share';
  $block->content = implode('', $output);
  return $block;

}

/**
 * Settings form.
 */
function springboard_p2p_personal_campaign_share_edit_form($form, &$form_state) {
  // No settings beyond context, which has already been handled.
  return $form;
}
