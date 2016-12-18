<?php
/**
 * @file
 * springboard_p2p_personal_campaign.ctools_content.inc
 */

/**
 * Implements hook_default_ctools_custom_content().
 */
function springboard_p2p_personal_campaign_default_ctools_custom_content() {
  $export = array();

  $content = new stdClass();
  $content->disabled = FALSE; /* Edit this to true to make a default content disabled initially */
  $content->api_version = 1;
  $content->name = 'fundraising_title_pane';
  $content->admin_title = 'Fundraising Search Title';
  $content->admin_description = '';
  $content->category = 'Springboard P2P';
  $content->settings = array(
    'admin_title' => '',
    'title' => '',
    'body' => '<h3>Search for a personal campaign</h3>',
    'format' => 'full_html',
    'substitute' => 1,
  );
  $export['fundraising_title_pane'] = $content;

  $content = new stdClass();
  $content->disabled = FALSE; /* Edit this to true to make a default content disabled initially */
  $content->api_version = 1;
  $content->name = 'pane_search_link';
  $content->admin_title = 'Search Link Pane';
  $content->admin_description = '';
  $content->category = 'Springboard P2P';
  $content->settings = array(
    'admin_title' => '',
    'title' => '',
    'body' => '<a class="view-all-search" href="/peer-to-peer-campaign-search">View all campaigns</a>',
    'format' => 'filtered_html',
    'substitute' => 1,
  );
  $export['pane_search_link'] = $content;

  return $export;
}
