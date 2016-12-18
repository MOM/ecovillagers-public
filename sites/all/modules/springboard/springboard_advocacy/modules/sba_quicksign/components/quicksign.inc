<?php

/**
 * @file
 * Webform module quicksign component.
 */

/**
 * Implements _webform_defaults_component().
 */
function _webform_defaults_quicksign() {
  return array(
    'name' => '',
    'form_key' => 'sba_quicksign',
    'pid' => 0,
    'weight' => 0,
    'value' => '',
    'mandatory' => 0,
    'extra' => array(
      'width' => '',
      'unique' => 0,
      'disabled' => 0,
      'title_display' => 0,
      'description' => '',
      'attributes' => array(),
      'private' => FALSE,
    ),
  );
}

/**
 * Implements _webform_edit_component().
 */
function _webform_edit_quicksign($component) {

  return array();
}



