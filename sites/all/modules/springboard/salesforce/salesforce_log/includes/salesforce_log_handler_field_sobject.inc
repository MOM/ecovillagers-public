<?php

/**
 * @file
 * Definition of SalesforceLogHandlerFieldSobject.
 */

/**
 * Filter by sObject.
 *
 * @ingroup views_filter_handlers
 */
class SalesforceLogHandlerFieldSobject extends views_handler_field {

  public function pre_render(&$values) {
    $this->options['element_class'] .= " expander";
  }

  /**
   * Render sObject.
   */
  public function render($values) {
    $value = $values->{$this->field_alias};
    return '<pre style = "width:150px">' . check_plain(print_r(json_decode($value), TRUE)) . '</pre>';
  }
}
