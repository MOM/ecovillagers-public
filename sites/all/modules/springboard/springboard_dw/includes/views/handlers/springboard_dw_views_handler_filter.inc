<?php

/**
 * @file springboard_dw_views_handler_filter.inc
 */
class springboard_dw_views_handler_filter extends views_handler_filter {
  /**
   *  Exposed filter element:
   */
  function value_form(&$form, &$form_state) {
    $form['value']['dw_global_search'] = array(
      '#type' => 'textfield',
      '#default_value' => '',
      '#size' => 42,
    );
    return $form;
  }

  function admin_summary() {}
}
