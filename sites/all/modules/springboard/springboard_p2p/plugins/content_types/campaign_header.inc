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
  'title' => t('Campaign header'),
  'description' => t('Displays the P2P campaign header image.'),
  'category' => t('Springboard P2P'),
  // Despite having no "settings" we need this function to pass back a form,
  // or we'll loose the context and title settings.
  'edit form' => 'springboard_p2p_campaign_header_edit_form',
  'render callback' => 'springboard_p2p_campaign_header_render',
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Render a single content pane.
 */
function springboard_p2p_campaign_header_render($subtype, $conf, $panel_args, $context) {
  $campaign = NULL;
  if (empty($context) || empty($context->data)) {
    if (isset($_GET['p2p_pcid']) && is_numeric($_GET['p2p_pcid'])) {
      $node = node_load($_GET['p2p_pcid']);
      if ($node->type == 'p2p_personal_campaign' && isset($node->field_p2p_campaign[$node->language][0]['target_id'])) {
        $campaign = node_load($node->field_p2p_campaign[$node->language][0]['target_id']);
      }
      else {
        return;
      }
    }
    else {
      return;
    }
  }

  $node = $context->data;

  if ($node->type == 'p2p_campaign') {
    $campaign = $node;
  }
  elseif ($node->type == 'p2p_personal_campaign' && isset($node->field_p2p_campaign[$node->language][0]['target_id'])) {
    $campaign = node_load($node->field_p2p_campaign[$node->language][0]['target_id']);
  }

  if (!is_null($campaign)) {
    // Build the content type block.
    $block = new stdClass();
    $block->title = 'Campaign header';
    $block->content = springboard_p2p_format_campaign_form_header($campaign);
    return $block;
  }

}

/**
 * Settings form.
 */
function springboard_p2p_campaign_header_edit_form($form, &$form_state) {
  // No settings beyond context, which has already been handled.
  return $form;
}
