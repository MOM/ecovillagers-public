<?php
/**
 * @file
 * Provide a handler for donation amounts.
 */

class fundraiser_handler_field_donation_amounts extends views_handler_field_prerender_list {

  /**
   * Break up our field into a proper list.
   */
  public function pre_render($values) {
    $this->items = array();
    foreach ($values as $value) {
      $field = $value->{$this->field_alias};
      $this->items[$field] = array();
      foreach (explode(',', $field) as $item) {
        if ($item != '' && $item !== NULL) {
          $this->items[$field][] = array('item' => $item);
        }
      }
    }
  }

}
