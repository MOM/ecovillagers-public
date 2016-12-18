<?php
/**
 * @file
 * Provide a handler for the Batch ID
 */

class queue_api_handler_field_batch_id extends views_handler_field {

  public function option_definition() {
    $options = parent::option_definition();
    $options['queue_api_batch_id_items_link'] = array('default' => 1);
    return $options;
  }

  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['queue_api_batch_id_items_link'] = array(
      '#title' => t('Link to Items'),
      '#description' => t('Link to batch items'),
      '#type' => 'checkbox',
      '#default_value' => $this->options['queue_api_batch_id_items_link'],
    );
  }

  public function render($values) {
    if ($this->options['queue_api_batch_id_items_link']) {
      $output = l($values->{$this->field_alias}, 'admin/reports/salesforce/batch/' . $values->{$this->field_alias});
    }
    else {
      $output = $values->{$this->field_alias};
    }
    return $output;
  }
}
