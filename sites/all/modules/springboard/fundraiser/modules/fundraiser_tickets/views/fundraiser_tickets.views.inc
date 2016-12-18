<?php

/**
 * Implements hook_views_query_alter
 * Prevent ticket forms from appearing in the entity reference autocomplete
 */

function fundraiser_tickets_views_query_alter(&$view, &$query) {
  if ($view->name == 'donation_forms' && $view->current_display == 'entityreference_1') {
    $types = fundraiser_tickets_get_ticket_types();
    $omit = array();
    foreach ($types as $type => $value) {
      if ($value) {
        $omit[$type] = $type;
      }
    }
    $view->query->add_where('omit', 'node.type', array_keys($omit), 'NOT IN');
  }
}

/**
 * Implements hook_views_views_post_execute
 * Prevent donation forms with unmatched required fields from appearing in the entity reference auto-complete.
 */
function fundraiser_tickets_views_post_execute(&$view) {
  if ($view->name == 'donation_forms' && $view->current_display == 'entityreference_1') {
    if(arg(4) == 'node' && arg(0) == 'entityreference' && is_numeric(arg(6))) {
      $entity = entity_load('node', array(arg(6)));
      $entity = array_pop($entity);
    }
    if (!empty($entity->nid)) {
      foreach ($view->result as $index => $result) {
        if (!empty($result->nid)) {
          $required_fields_match = fundraiser_tickets_check_addon_required_fields($result->nid, NULL, $entity);
          if (empty($required_fields_match)) {
            unset($view->result[$index]);
          }
        }
      }
    }
  }
}
