<?php

/**
 * @file
 * Definition of SpringboardViewsFieldNodeLinkEdit.
 */

/**
 * Field handler to present a link node edit.
 *
 * @ingroup views_field_handlers
 */
class SpringboardViewsFieldNodeLinkEdit extends views_handler_field_node_link_edit {

  /**
   * Renders the link.
   */
  function render_link($node, $values) {
    $text = parent::render_link($node, $values);

    if (!empty($text)) {
      // Add title.
      $this->options['alter']['alt'] = 'Edit';
      return $text;
    }
  }
}
