<?php
/**
 * @file
 * springboard_p2p_personal_campaign.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function springboard_p2p_personal_campaign_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ctools_custom_content" && $api == "ctools_content") {
    return array("version" => "1");
  }
  if ($module == "panelizer" && $api == "panelizer") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
  if ($module == "video_embed_field" && $api == "default_video_embed_styles") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function springboard_p2p_personal_campaign_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function springboard_p2p_personal_campaign_image_default_styles() {
  $styles = array();

  // Exported image style: p2p_pers_campaign_image_thumb.
  $styles['p2p_pers_campaign_image_thumb'] = array(
    'name' => 'p2p_pers_campaign_image_thumb',
    'label' => 'P2P Personal Campaign Image Thumb',
    'effects' => array(
      1 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 340,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
      2 => array(
        'label' => 'Crop',
        'help' => 'Cropping will remove portions of an image to make it the specified dimensions.',
        'effect callback' => 'image_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_crop_form',
        'summary theme' => 'image_crop_summary',
        'module' => 'image',
        'name' => 'image_crop',
        'data' => array(
          'width' => 340,
          'height' => 200,
          'anchor' => 'center-top',
        ),
        'weight' => 2,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function springboard_p2p_personal_campaign_node_info() {
  $items = array(
    'p2p_personal_campaign' => array(
      'name' => t('Peer to Peer Personal Campaign'),
      'base' => 'node_content',
      'description' => t('Peer to Peer personal campaign page. '),
      'has_title' => '1',
      'title_label' => t('Campaign Name'),
      'help' => '',
    ),
  );
  return $items;
}
