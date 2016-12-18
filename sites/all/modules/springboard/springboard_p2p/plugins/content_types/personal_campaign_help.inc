<?php
/**
 * @file
 * Plugin to display a personal campaign help pane.
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('Personal campaign help'),
  'description' => t('Starter help for logged in personal campaigners'),
  'category' => t('Springboard P2P'),
  'edit form' => 'springboard_p2p_personal_campaign_help_edit_form',
  'render callback' => 'springboard_p2p_personal_campaign_help_render',
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Run-time rendering of the body of the block (content type).
 *
 * See ctools_plugin_examples for more advanced info.
 */
function springboard_p2p_personal_campaign_help_render($subtype, $conf, $panel_args, $context) {

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
    $block->title = '';

    $campaign_wrapper = entity_metadata_wrapper('node', $campaign);
    $help_text = $campaign_wrapper->field_p2p_help_content->value();

    if (isset($help_text['safe_value'])) {
      $block->content = $help_text['safe_value'];
    }
    else {
      $block->content = check_markup($help_text['value'], $help_text['format']);
    }

    return $block;
  }
}

/**
 * An edit form for the pane's settings.
 */
function springboard_p2p_personal_campaign_help_edit_form($form, &$form_state) {
  // No settings beyond context, which has already been handled.
  return $form;
}
