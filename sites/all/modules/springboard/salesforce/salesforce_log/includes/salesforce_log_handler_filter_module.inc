<?php

/**
 * @file
 * Definition of SalesforceLogHandlerFilterModule.
 */

/**
 * Filter by module.
 *
 * @ingroup views_filter_handlers
 */
class SalesforceLogHandlerFilterModule extends views_handler_filter_in_operator {

  /**
   * List of possible modules.
   */
  public function getValueOptions() {
    if (!isset($this->value_options)) {
      $result = db_query("SELECT distinct(module) FROM {" . $this->view->base_table . "}");
      if ($result->rowCount()) {
        foreach ($result as $record) {
          $this->value_options[$record->module] = $record->module;
        }
      }
      else {
        $this->value_options = array(0 => 'No module entries found');
      }
    }
  }

  // Ignnore required method names that do not pass coding standards
  // @codingStandardsIgnoreStart
  public function get_value_options() {
    $this->getValueOptions();
  }
  // @codingStandardsIgnoreEnd
}
