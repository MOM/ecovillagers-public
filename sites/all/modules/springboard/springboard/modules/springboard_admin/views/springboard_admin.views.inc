<?php

/**
 * @file
 * Provide views data and handlers.
 */

/**
 * Implements hook_views_data().
 */
function springboard_admin_views_data() {
  $data = [];

  $data['springboard_admin__global']['table']['group'] = t('Springboard Admin');
  $data['springboard_admin__global']['table']['join'] = [
    // #global is a special flag which let's a table appear all the time.
    '#global' => [],
  ];

  $data['springboard_admin__global']['content_type_empty_result'] = [
    'title' => t('Content Type Empty Result'),
    'help' => t('For an empty result hides the filters and shows a button per a content type argument.'),
    'area' => [
      'handler' => 'SpringboardAdminViewsHandlerAreaEmptyContentTypeResult',
    ],
  ];

  return $data;
}
