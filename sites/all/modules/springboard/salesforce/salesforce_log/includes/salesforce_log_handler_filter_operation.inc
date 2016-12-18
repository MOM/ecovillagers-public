<?php

/**
 * @file
 * Definition of SalesforceLogHandlerFilterOperation.
 */

/**
 * Filter by Salesforce operation.
 *
 * @ingroup views_filter_handlers
 */
class SalesforceLogHandlerFilterOperation extends views_handler_filter_in_operator {

  /**
   * List of possible Salesforce operations.
   */
  public function getValueOptions() {
    $this->value_options = array(
      'CREATE' => 'Create',
      'UPDATE' => 'Update',
      'UPSERT' => 'Upsert',
    );
  }

  // Ignnore required method names that do not pass coding standards
  // @codingStandardsIgnoreStart
  public function get_value_options() {
    $this->getValueOptions();
  }
  // @codingStandardsIgnoreEnd
}
