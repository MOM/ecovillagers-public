<?php
/**
 * @file
 * User facing page callbacks and forms for Springboard P2P.
 */


/**
 * Page callback for the personal dashboard.
 *
 * @param object $account
 *   The user that matches the uid in the path.
 *
 * @return array
 *   Render array.
 */
function springboard_p2p_personal_dashboard($account) {
  $dashboard_content = views_embed_view('p2p_personal_campaigns_by_campaigner', 'page', $account->uid);

  $title = 'Personal campaign dashboard';
  $full_name = springboard_p2p_format_user_full_name($account);
  if (!empty($full_name)) {
    $title .= ' for ' . $full_name;
  }
  drupal_set_title($title);

  return array(
    'content' => array(
      '#markup' => $dashboard_content,
    ),
  );
}
