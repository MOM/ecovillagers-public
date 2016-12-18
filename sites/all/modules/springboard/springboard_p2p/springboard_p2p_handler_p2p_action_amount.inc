<?php

/**
 * @file
 * Views handler for formatting amount fields.
 */

/**
 * Description of what my handler does.
 */
class springboard_p2p_handler_p2p_action_amount extends views_handler_field {
  /**
   * Add some required fields needed on render().
   */
  public function construct() {
    parent::construct();
    $this->additional_fields['action_type'] = array(
      'table' => 'springboard_p2p_personal_campaign_action',
      'field' => 'action_type',
    );
    $this->additional_fields['action_amount'] = array(
      'table' => 'springboard_p2p_personal_campaign_action',
      'field' => 'amount',
    );
  }

  /**
   * Loads additional fields.
   */
  public function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  /**
   * Default options form.
   */
  public function option_definition() {
    $options = parent::option_definition();
    return $options;
  }

  /**
   * Creates the form item for the options added.
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  }

  /**
   * Renders the field handler.
   */
  public function render($values) {
    if ($values->springboard_p2p_personal_campaign_action_action_type == 'fundraiser') {
      $value = '$' . number_format($values->springboard_p2p_personal_campaign_action_amount * .01, 2);
    }
    else {
      $value = $values->springboard_p2p_personal_campaign_action_amount;
    }
    return $value;
  }
}
