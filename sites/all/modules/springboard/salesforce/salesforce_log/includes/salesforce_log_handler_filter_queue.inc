<?php

/**
 * @file
 * Definition of SalesforceLogHandlerFilterQueue.
 */

/**
 * Filter by queue.
 *
 * @ingroup views_filter_handlers
 */
class SalesforceLogHandlerFilterQueue extends views_handler_filter_in_operator {

  /**
   * List of possible queues.
   */
  public function getValueOptions() {
    $this->value_options = salesforce_queue_get_queue_names();
  }

  // Ignnore required method names that do not pass coding standards
  // @codingStandardsIgnoreStart
  public function get_value_options() {
    $this->getValueOptions();
  }
  // @codingStandardsIgnoreEnd
}
