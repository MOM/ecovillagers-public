<?php
/**
 * @file
 * Plugin to display the help message as a content pane within panels.
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('Custom Help Message'),
  'description' => t('Help Message'),
  'category' => t('Springboard P2P'),
  // A category to put this under.
  'edit form' => 'springboard_p2p_help_message_edit_form',
  // A function that will return the settings form for the pane.
  'render callback' => 'springboard_p2p_help_message_render',
  // A function that will return the renderable content.
  'admin info' => 'springboard_p2p_help_message_admin_info',
  // A function that will return the information displayed on the admin screen (optional).
  'defaults' => array( // Array of defaults for the settings form.
    'text' => '',
  ),
  'all contexts' => TRUE,
  // This is NEEDED to be able to use substitution strings in your pane.
);

/**
 * An edit form for the pane's settings.
 */
function springboard_p2p_help_message_edit_form($form, &$form_state) {
  // No settings beyond context, which has already been handled.
  return $form;
}

/**
 * Run-time rendering of the body of the block (content type).
 *
 * See ctools_plugin_examples for more advanced info.
 */
function springboard_p2p_help_message_render($subtype, $conf, $args, $contexts) {

  // Provide a default title.
  $title = t('Need Help?');

  // Provide for an overidden title.
  if ($conf['override_title'] && !empty($conf['override_title_text'])) {
    $title = filter_xss_admin($conf['override_title_text']);
  }

  // Pull the help message text from P2P Settings.
  $helptext = variable_get('springboard_p2p_help_message_area');

  $output = array();

  // Create the output to be rendered.
  if (isset($helptext['value'])) {
    $output[] = '<div class="help-text-wrapper"> ';
    $output[] = $helptext['value'];
    $output[] = '</div>';
  }

  // Initial content is blank.
  // Build the content type block.
  $block = new stdClass();
  $block->title = $title;
  $block->content = implode('', $output);
  return $block;

}
