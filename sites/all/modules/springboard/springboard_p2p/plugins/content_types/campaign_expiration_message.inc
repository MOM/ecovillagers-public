<?php

/**
 * @file
 * Plugin to display the P2P campaign expiration message.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('P2P campaign expiration message'),
  'description' => t('Displays the P2P campaign expiration message'),
  'category' => t('Springboard P2P'),
  // Despite having no "settings" we need this function to pass back a form,
  // or we'll loose the context and title settings.
  'edit form' => 'springboard_p2p_campaign_expiration_message_edit_form',
  'render callback' => 'springboard_p2p_campaign_expiration_message_render',
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Render a single content pane.
 */
function springboard_p2p_campaign_expiration_message_render($subtype, $conf, $panel_args, $context) {
  $personal_campaign = springboard_p2p_get_personal_campaign_from_context_or_url($context);

  if (is_object($personal_campaign)) {
    $campaign = springboard_p2p_get_campaign_from_personal_campaign($personal_campaign);
    $wrapper = entity_metadata_wrapper('node', $campaign);
    $value = $wrapper->field_p2p_expiration_message->value();

    // Build the content type block.
    $block = new stdClass();
    $block->title = '';
    $block->content = check_markup($value['value'], $value['format']);

    return $block;
  }

}

/**
 * Settings form.
 */
function springboard_p2p_campaign_expiration_message_edit_form($form, &$form_state) {
  // No settings beyond context, which has already been handled.
  return $form;
}
