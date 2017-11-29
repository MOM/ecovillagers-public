<?php

/**
 * @file Share event tracking.
 */


/**
 * Track individual share event.
 *
 * @param string $service
 *   Social media service (facebook, twitter).
 * @param int $id
 *   Id associated with share event, submission id for webforms,
 *   node id for node pages, path for path-based shares.
 * @param string $type
 *    ID type, sid, nid, or path.
 * @param $market_source
 *   Market source value for the share event.
 */
function sb_social_share_tracker($service, $id, $type, $market_source) {
  $enabled_services = sb_social_get_enabled_services();

  if (!in_array($service, $enabled_services)) {
    return drupal_json_output(FALSE);
  }
  else {
    $share_url = sb_social_share_event_save($service, $id, $type, $market_source);
    if (!empty($share_url)) {
      $short_url = shorten_url($share_url);
      if (variable_get('springboard_social_debug_mode', 0)) {
        return drupal_json_output($share_url);
      }
      else {
        return drupal_json_output($short_url);
      }
    }
    return drupal_json_output(FALSE);
  }
}
