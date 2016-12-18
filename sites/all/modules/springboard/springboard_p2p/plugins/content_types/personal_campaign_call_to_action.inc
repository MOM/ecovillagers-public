<?php

/**
 * @file
 * Plugin to display a personal campaign's progress.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('Personal campaign call to action'),
  'description' => t('Displays the P2P personal campaign button to donate or submit.'),
  'category' => t('Springboard P2P'),
  // Despite having no "settings" we need this function to pass back a form,
  // or we'll loose the context and title settings.
  'edit form' => 'springboard_p2p_personal_campaign_call_to_action_edit_form',
  'render callback' => 'springboard_p2p_personal_campaign_call_to_action_render',
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Render a single content pane.
 */
function springboard_p2p_personal_campaign_call_to_action_render($subtype, $conf, $panel_args, $context) {
  $campaign = NULL;
  $personal_campaign = NULL;
  if (empty($context) || empty($context->data)) {
    if (isset($_GET['p2p_pcid']) && is_numeric($_GET['p2p_pcid'])) {
      $node = node_load($_GET['p2p_pcid']);
      if ($node->type == 'p2p_personal_campaign' && isset($node->field_p2p_campaign[$node->language][0]['target_id'])) {
        $campaign = node_load($node->field_p2p_campaign[$node->language][0]['target_id']);
        $personal_campaign = $node;
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

  if ($node->type == 'p2p_personal_campaign' && isset($node->field_p2p_campaign[$node->language][0]['target_id'])) {
    $campaign = node_load($node->field_p2p_campaign[$node->language][0]['target_id']);
    $personal_campaign = $node;
  }

  if (!is_null($campaign) && !is_null($personal_campaign)) {
    $output = array();
    $goal = springboard_p2p_get_goal_from_campaign($campaign);

    $output[] = '<div class="personal-campaign-call-to-action">';

    $campaign_wrapper = entity_metadata_wrapper('node', $campaign);
    $label = $campaign_wrapper->field_p2p_campaign_action_button->value();

    $output[] = l($label, 'node/' . $goal['nid'], array(
      'query' => array(
        'p2p_pcid' => $personal_campaign->nid,
      ),
    ));

    $output[] = '</div>';

    // Build the content type block.
    $block = new stdClass();
    $block->title = 'Personal campaign call to action';
    $block->content = implode('', $output);
    return $block;
  }
}

/**
 * Settings form.
 */
function springboard_p2p_personal_campaign_call_to_action_edit_form($form, &$form_state) {
  // No settings beyond context, which has already been handled.
  return $form;
}
