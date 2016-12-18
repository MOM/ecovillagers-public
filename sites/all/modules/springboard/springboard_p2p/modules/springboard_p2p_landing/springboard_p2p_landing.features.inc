<?php
/**
 * @file
 * springboard_p2p_landing.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function springboard_p2p_landing_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "panelizer" && $api == "panelizer") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function springboard_p2p_landing_image_default_styles() {
  $styles = array();

  // Exported image style: p2p_campaign_image_landing.
  $styles['p2p_campaign_image_landing'] = array(
    'name' => 'p2p_campaign_image_landing',
    'label' => 'P2P Campaign Image Thumb',
    'effects' => array(
      3 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 400,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => -10,
      ),
      4 => array(
        'label' => 'Crop',
        'help' => 'Cropping will remove portions of an image to make it the specified dimensions.',
        'effect callback' => 'image_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_crop_form',
        'summary theme' => 'image_crop_summary',
        'module' => 'image',
        'name' => 'image_crop',
        'data' => array(
          'width' => 400,
          'height' => 230,
          'anchor' => 'center-top',
        ),
        'weight' => -9,
      ),
    ),
  );

  // Exported image style: p2p_campaign_image_slideshow.
  $styles['p2p_campaign_image_slideshow'] = array(
    'name' => 'p2p_campaign_image_slideshow',
    'label' => 'P2P Campaign Image Slideshow',
    'effects' => array(
      3 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 1170,
          'height' => 360,
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      4 => array(
        'label' => 'Crop',
        'help' => 'Cropping will remove portions of an image to make it the specified dimensions.',
        'effect callback' => 'image_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_crop_form',
        'summary theme' => 'image_crop_summary',
        'module' => 'image',
        'name' => 'image_crop',
        'data' => array(
          'width' => 1170,
          'height' => 360,
          'anchor' => 'center-center',
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
function springboard_p2p_landing_node_info() {
  $items = array(
    'p2p_campaign_landing' => array(
      'name' => t('Peer to Peer Campaign Landing'),
      'base' => 'node_content',
      'description' => t('Peer to Peer landing page content type that will aggregate and pull in data from various areas of the site.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
