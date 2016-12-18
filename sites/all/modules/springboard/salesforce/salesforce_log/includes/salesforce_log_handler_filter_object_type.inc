<?php

/**
 * @file
 * Definition of SalesforceLogHandlerFilterObjectType.
 */

/**
 * Filter by Salesforce object type.
 *
 * @ingroup views_filter_handlers
 */
class SalesforceLogHandlerFilterObjectType extends views_handler_filter_in_operator {

  /**
   * List of possible Salesforce object types.
   */
  public function getValueOptions() {
    $result = db_query("SELECT distinct(object_type) FROM {" . $this->view->base_table . "}");
    if ($result->rowCount()) {
      foreach ($result as $record) {
        $this->value_options[$record->object_type] = $record->object_type;
      }
    }
    else {
      $this->value_options = array(0 => 'No object types found');
    }
  }

  // Ignnore required method names that do not pass coding standards
  // @codingStandardsIgnoreStart
  public function get_value_options() {
    $this->getValueOptions();
  }
  // @codingStandardsIgnoreEnd
}
