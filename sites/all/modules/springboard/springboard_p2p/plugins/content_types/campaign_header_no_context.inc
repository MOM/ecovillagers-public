<?php

/**
 * @file
 * Plugin to display a campaign header image.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('Campaign header (Node context)'),
  'description' => t('Displays the P2P campaign header image.'),
  'category' => t('Springboard P2P'),
  // Despite having no "settings" we need this function to pass back a form,
  // or we'll loose the context and title settings.
  'render callback' => 'springboard_p2p_campaign_header_no_context_render',
);

/**
 * Render a single content pane.
 */
function springboard_p2p_campaign_header_no_context_render($subtype, $conf, $panel_args, $context) {
  $campaign = NULL;

  if (isset($_GET['p2p_cid']) && is_numeric($_GET['p2p_cid'])) {
    $node = node_load($_GET['p2p_cid']);
    if ($node->type == 'p2p_campaign') {
      $campaign = $node;
    }
    else {
      return;
    }
  }
  elseif (isset($_GET['p2p_pcid']) && is_numeric($_GET['p2p_pcid'])) {
    $node = node_load($_GET['p2p_pcid']);
    if ($node->type == 'p2p_personal_campaign' && isset($node->field_p2p_campaign[$node->language][0]['target_id'])) {
      $campaign = node_load($node->field_p2p_campaign[$node->language][0]['target_id']);
    }
    else {
      return;
    }
  }

  if (!is_null($campaign)) {
    // Build the content type block.
    $block = new stdClass();
    $block->title = '';
    $block->content = springboard_p2p_format_campaign_form_header($campaign);
    return $block;
  }

}
