<?php
/**
 * @file
 * springboard_p2p_personal_campaign.default_video_embed_styles.inc
 */

/**
 * Implements hook_default_video_embed_styles().
 */
function springboard_p2p_personal_campaign_default_video_embed_styles() {
  $export = array();

  $video_embed_style = new stdClass();
  $video_embed_style->disabled = FALSE; /* Edit this to true to make a default video_embed_style disabled initially */
  $video_embed_style->api_version = 1;
  $video_embed_style->name = 'p2p_video';
  $video_embed_style->title = 'P2P Video';
  $video_embed_style->data = array(
    'youtube' => array(
      'width' => '640px',
      'height' => '360px',
      'theme' => 'light',
      'autoplay' => 0,
      'vq' => 'hd720',
      'rel' => 0,
      'showinfo' => 1,
      'modestbranding' => 0,
      'iv_load_policy' => '1',
      'autohide' => '2',
    ),
    'vimeo' => array(
      'width' => '640px',
      'height' => '360px',
      'color' => '00adef',
      'portrait' => 1,
      'title' => 1,
      'byline' => 1,
      'autoplay' => 0,
      'loop' => 0,
    ),
    'data__active_tab' => 'edit-data-youtube',
  );
  $export['p2p_video'] = $video_embed_style;

  return $export;
}
