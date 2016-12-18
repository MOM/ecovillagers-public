<?php
/**
 * @file
 * Definition of silverpop_transact_handler_silverpop_message_field.
 */

/**
 * Translates the int form db table status to readable text.
 *
 * @ingroup views_field_handlers
 */
class silverpop_transact_handler_silverpop_message_field extends views_handler_field {
  /**
   *
   */
  function init(&$view, &$data) {
    parent::init($view, $data);
  }

  /**
   *
   */
  function render($values) {
    $status_text = '';
    $value = $this->get_value($values);
    // $value = an int at the moment.
    switch ($value) {
      case "0":
        $status_text = 'Success';
        break;

      case "1":
        $status_text = 'Not sent - errors during the send';
        break;

      case "2":
        $status_text = 'Not sent - errors with the XML submission';
        break;
    }
    return $status_text;
  }

}
