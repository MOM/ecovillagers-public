<?php

/**
 * @file
 * Definition of fundraiser_handler_filter_fundraiser_gateways
 */

/**
 * Filter by a donation form's gateways
 */
class fundraiser_handler_filter_fundraiser_gateways extends views_handler_filter {
  /**
   * Setup the exposed form as a select
   */
  public function exposed_form(&$form, &$form_state) {
    parent::exposed_form($form, $form_state);
    $form['gateways']['#type'] = 'select';
    unset($form['gateways']['#size']);
    $gateways = _fundraiser_gateway_info($id = NULL);
    $form['gateways']['#options'] = array();
    $form['gateways']['#options']['All'] = 'All';
    foreach ($gateways as $gateway) {
      $form['gateways']['#options'][$gateway['id']] = $gateway['title'];
    }

    $form[$value]['#default_value'] = 'All';
  }

  /**
   * Add this filter to the query.
   *
   * The gateways are saved as a serialized string so using a LIKE query is the best way to search it
   */
  public function query() {
    $this->ensure_my_table();
    if (!empty($this->value[0])) {
      $field = "$this->table_alias.$this->real_field";
      $this->query->add_where($this->options['group'], $field, '%' . db_like($this->value[0]) . '%', 'LIKE');
    }
  }
}
