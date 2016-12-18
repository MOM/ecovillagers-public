<?php

/**
 * @file
 * Plugin to display a campaign's organization introduction.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('Organization Introduction'),
  'description' => t("Displays the P2P campaign's org intro."),
  'category' => t('Springboard P2P'),
  // Despite having no "settings" we need this function to pass back a form,
  // or we'll loose the context and title settings.
  'edit form' => 'springboard_p2p_org_intro_edit_form',
  'render callback' => 'springboard_p2p_org_intro_render',
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Render a single content pane.
 */
function springboard_p2p_org_intro_render($subtype, $conf, $panel_args, $context) {

  $campaign = NULL;
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

  if ($personal_campaign->type == 'p2p_personal_campaign' && isset($personal_campaign->field_p2p_campaign[$personal_campaign->language][0]['target_id'])) {
    $campaign = node_load($personal_campaign->field_p2p_campaign[$personal_campaign->language][0]['target_id']);
  }

  if (!is_null($campaign) && $campaign->type == 'p2p_campaign') {

    $campaign_wrapper = entity_metadata_wrapper('node', $campaign);
    $output = array();

    $intro = $campaign_wrapper->field_p2p_org_intro->value();
    if (isset($intro['safe_value'])) {
      $output[] = $intro['safe_value'];
    }
    else {
      $output[] = check_markup($intro['value'], $intro['format']);
    }

    $output[] = '<div class="personal-campaign-call-to-action">';
    $goal = springboard_p2p_get_goal_from_campaign($campaign);
    $label = $campaign_wrapper->field_p2p_campaign_action_button->value();

    $output[] = l($label, 'node/' . $goal['nid'], array(
        'query' => array(
          'p2p_pcid' => $personal_campaign->nid,
        ),
      ));

    $output[] = '</div>';

    // Build the content type block.
    $block = new stdClass();
    $block->title = '';
    $block->content = implode('', $output);

    return $block;
  }
}

/**
 * Settings form.
 */
function springboard_p2p_org_intro_edit_form($form, &$form_state) {
  // No settings beyond context, which has already been handled.
  return $form;
}
