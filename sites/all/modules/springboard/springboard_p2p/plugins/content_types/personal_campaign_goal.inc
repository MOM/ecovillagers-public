<?php

/**
 * @file
 * Plugin to display a personal campaign's goal.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('Personal campaign goal'),
  'description' => t('Displays the P2P personal campaign goal.'),
  'category' => t('Springboard P2P'),
  // Despite having no "settings" we need this function to pass back a form,
  // or we'll loose the context and title settings.
  'edit form' => 'springboard_p2p_personal_campaign_goal_edit_form',
  'render callback' => 'springboard_p2p_personal_campaign_goal_render',
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Render a single content pane.
 */
function springboard_p2p_personal_campaign_goal_render($subtype, $conf, $panel_args, $context) {
  $personal_campaign = springboard_p2p_get_personal_campaign_from_context_or_url($context);

  if (is_object($personal_campaign)) {
    $campaign = springboard_p2p_get_campaign_from_personal_campaign($personal_campaign);
    if (is_object($campaign)) {
      $output = array();
      $language = $personal_campaign->language;
      $goal_type = springboard_p2p_get_goal_type_from_campaign($campaign);

      if ($goal_type == 'submissions' && isset($personal_campaign->field_p2p_personal_submit_goal[$language][0]['value'])) {
        $goal_value = $personal_campaign->field_p2p_personal_submit_goal[$language][0]['value'];
        $title = t('Submission Goal');
      }
      elseif ($goal_type == 'amount' && isset($personal_campaign->field_p2p_personal_campaign_goal[$language][0]['value'])) {
        $goal_value = $personal_campaign->field_p2p_personal_campaign_goal[$language][0]['value'];
        $title = t('Personal Fundraising Goal');
      }
      else {
        return;
      }

      $output[] = '<div class="goal-label">' . $title . '</div>';
      $output[] = '<span class="goal-amount">';
      $output[] = springboard_p2p_format_progress($goal_value, $goal_type);
      $output[] = '</span>';

      // Build the content type block.
      $block = new stdClass();
      $block->title = '';
      $block->content = implode($output);

      return $block;

    }
  }

}

/**
 * Settings form.
 */
function springboard_p2p_personal_campaign_goal_edit_form($form, &$form_state) {
  // No settings beyond context, which has already been handled.
  return $form;
}
