<?php

/**
* @file
* Views field handler. Contains all relevant VBO options and related logic.
* Implements the Views Form API.
*/

class webform_ui_bulk_operations_handler_field_operations extends views_bulk_operations_handler_field_operations {
  /**
   * Need to override this so that vbo uses the webform the submissions belong to.
   */
  public function get_entity_type() {
    return 'node';
  }
}
