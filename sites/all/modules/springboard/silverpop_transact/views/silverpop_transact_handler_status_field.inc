<?php
/**
 * @file
 * Definition of silverpop_transact_handler_status_field.
 */

/**
 * Translates the int form db table status to readable text.
 *
 * @ingroup views_field_handlers
 */
class silverpop_transact_handler_status_field extends views_handler_field {
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
        $status_text = 'Upload failure';
        break;

      case "1":
        $status_text = 'Success';
        break;

      case "2":
        $status_text = 'Queued for cron';
        break;

    }
    return $status_text;
  }

}
