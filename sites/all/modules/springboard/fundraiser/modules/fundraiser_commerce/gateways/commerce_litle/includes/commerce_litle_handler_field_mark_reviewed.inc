<?php

/**
 * @file
 * Field handler to present a reviewed checkbox
 */

/**
 * Field handler to present a reviewed checkbox.
 */
class commerce_litle_handler_field_mark_reviewed extends views_handler_field {

  public function construct() {
    parent::construct();
    $this->additional_fields['mark_reviewed'] = 'mark_reviewed';
    $this->real_field = 'mark_reviewed';
  }

  public function render($values) {
    return '<!--form-item-' . $this->options['id'] . '--' . $this->view->row_index . '-->';
  }

  /**
   * Returns the form which replaces the placeholder from render().
   */
  public function views_form(&$form, &$form_state) {
    if (empty($this->view->result)) {
      return;
    }

    $form[$this->options['id']] = array(
      '#tree' => TRUE,
    );
    $form['order_id'] = array(
      '#tree' => TRUE,
    );
    foreach ($this->view->result as $row_id => $row) {
      $reviewed = $this->get_value($row);
      $form[$this->options['id']][$row_id] = array(
        '#type' => 'checkbox',
        '#title' => t('Reviewed'),
        '#default_value' => $reviewed,
        '#submit' => array_merge($form['#submit'], array('commerce_litle_handler_field_mark_reviewed_form_submit')),
      );
      $form['order_id'][$row_id] = array(
        '#type' => 'hidden',
        '#value' => $row->commerce_order_commerce_litle_fraud_order_id,
      );
    }
  }

  public function views_form_submit($form, &$form_state) {
    $reviewed = $form_state['values']['mark_reviewed'];
    $id = $form_state['values']['order_id'];
    foreach ($reviewed as $index => $review) {
      $record = array('order_id' => $id[$index] , 'mark_reviewed' => $review);
      drupal_write_record('commerce_litle_fraud', $record, 'order_id');
    } 
  }
}
