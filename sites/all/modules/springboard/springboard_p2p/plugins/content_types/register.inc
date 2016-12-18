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
  'title' => t('User register'),
  'description' => t('Displays the P2P user register form.'),
  'category' => t('Springboard P2P'),
  // Despite having no "settings" we need this function to pass back a form,
  // or we'll loose the context and title settings.
  'edit form' => 'springboard_p2p_register_edit_form',
  'render callback' => 'springboard_p2p_register_render',
  // 'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Render a single content pane.
 */
function springboard_p2p_register_render($subtype, $conf, $panel_args, $context) {
  module_load_include('inc', 'springboard_p2p', 'includes/springboard_p2p.register');

  // Build the content type block.
  $block = new stdClass();
  $block->title = 'Create a new account';
  $block->content = drupal_get_form('springboard_p2p_user_register_form');

  return $block;
}

/**
 * Settings form.
 */
function springboard_p2p_register_edit_form($form, &$form_state) {
  // No settings beyond context, which has already been handled.
  return $form;
}
