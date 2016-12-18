<?php
/**
 * @file
 * Plugin to display a get started pane.
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('Get Started'),
  'description' => t('Get started pane'),
  'category' => t('Springboard P2P'),
  // A category to put this under.
  'edit form' => 'springboard_p2p_get_started_edit_form',
  // A function that will return the settings form for the pane.
  'render callback' => 'springboard_p2p_get_started_render',
  // A function that will return the renderable content.
  'admin info' => 'springboard_p2p_get_started_admin_info',
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
function springboard_p2p_get_started_edit_form($form, &$form_state) {
  // No settings beyond context, which has already been handled.
  return $form;
}

/**
 * Run-time rendering of the body of the block (content type).
 *
 * See ctools_plugin_examples for more advanced info.
 */
function springboard_p2p_get_started_render($subtype, $conf, $args, $contexts) {

  // Title.
  $title = t('Start Your Own Campaign');

  // Define the reg link.
  $getstarted_link = "/p2p/register";

  // Define the site name.
  $site_name = variable_get('site_name');

  $output = array();

  // Create the output to be rendered.
  $output[] = '<p>' . t('Want to start your own personal campaign for @site_name?', array('@site_name' => $site_name)) . '</p>';
  $output[] = '<a class="get-started-link" href=" ' .  $getstarted_link  . ' ">' . t('Get Started') . '<i class="fa fa-cog  get-started-spinner"></i></a>';

  // Initial content is blank.
  // Build the content type block.
  $block = new stdClass();
  $block->title = $title;
  $block->content = implode('', $output);
  return $block;

}
