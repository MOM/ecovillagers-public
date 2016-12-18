<?php
/**
 * @file
 * Plugin to display a get started pane.
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('Top Links'),
  'description' => t('Campaign top links'),
  'category' => t('Springboard P2P'),
  // A category to put this under.
  'edit form' => 'springboard_p2p_top_links_edit_form',
  // A function that will return the settings form for the pane.
  'render callback' => 'springboard_p2p_top_links_render',
  // A function that will return the renderable content.
  'admin info' => 'springboard_p2p_top_links_admin_info',
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
function springboard_p2p_top_links_edit_form($form, &$form_state) {
  // No settings beyond context, which has already been handled.
  return $form;
}

/**
 * Run-time rendering of the body of the block (content type).
 *
 * See ctools_plugin_examples for more advanced info.
 */
function springboard_p2p_top_links_render($subtype, $conf, $args, $contexts) {

  // Global node.
  $node = menu_get_object();

  // Define the reg link passing the string id.
  $loginlink = '/p2p/login';

  // Define the user.
  global $user;
  $account = $user->uid;
  $accountlink = '/user/' . $account . '/personal-campaigns';

  $output = array();

  // Create the output to be rendered.

  if ($user->uid == 0) {
    // Logged out.
    if (!empty($node) && $node->type == 'p2p_personal_campaign' && arg(2) === NULL) {
      $message = t('Is this your campaign? Login to manage it.');
    }
    else {
      $message = t('Already have a campaign? Click here to login.');
    }

    $output[] = '<a class="get-started-link account-link" href=" ' . $loginlink . ' ">' . $message . '<i class="fa fa-cog get-started-spinner"></i></a>';
  }

  else {
    // Logged in.
    $message = t('Go to your account');
    $output[] = '<a class="get-started-link account-link" href=" ' . $accountlink . ' ">' . $message . '<i class="fa fa-cog get-started-spinner"></i></a>';
  }

  // Initial content is blank.
  // Build the content type block.
  $block = new stdClass();
  $block->title = '';
  $block->content = implode('', $output);
  return $block;
}
