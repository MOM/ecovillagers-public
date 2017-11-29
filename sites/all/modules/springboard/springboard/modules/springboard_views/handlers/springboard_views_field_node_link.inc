<?php

/**
 * @file
 * Definition of SpringboardViewsFieldNodeLink.
 */

/**
 * Field handler to present a link to a node.
 *
 * @ingroup views_field_handlers
 */
class SpringboardViewsFieldNodeLink extends views_handler_field_node {

  /**
   * Render whatever the data is as a link to the node.
   *
   * Data should be made XSS safe prior to calling this function.
   */
  function render_link($data, $values) {
    $data = parent::render_link($data, $values);

    if (!empty($this->options['alter']['make_link'])) {
      // Add title.
      $this->options['alter']['alt'] = 'View';
    }

    return $data;
  }
}
