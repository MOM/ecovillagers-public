<?php

/**
 * @file
 * Plugin to display a password reset request form.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('Password reset request form'),
  'description' => t('Displays the P2P password reset request form.'),
  'category' => t('Springboard P2P'),
  // Despite having no "settings" we need this function to pass back a form,
  // or we'll loose the context and title settings.
  'edit form' => 'springboard_p2p_password_reset_request_edit_form',
  'render callback' => 'springboard_p2p_password_reset_request_render',
  // 'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Render a single content pane.
 */
function springboard_p2p_password_reset_request_render($subtype, $conf, $panel_args, $context) {
  module_load_include('inc', 'springboard_p2p', 'includes/springboard_p2p.password');
  // Build the content type block.
  $block = new stdClass();
  $block->title = '';
  $block->content = drupal_get_form('springboard_p2p_request_password_reset_form');

  return $block;
}

/**
 * Settings form.
 */
function springboard_p2p_password_reset_request_edit_form($form, &$form_state) {
  // No settings beyond context, which has already been handled.
  return $form;
}
