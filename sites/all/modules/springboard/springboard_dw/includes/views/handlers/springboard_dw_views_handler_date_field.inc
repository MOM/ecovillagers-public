<?php

/**
 * @file springboard_dw_views_handler_date_field.inc
 *
 */

class springboard_dw_views_handler_date_field extends views_handler_field_date
{
  /**
   * Override the parent method
   * We aren't using a DB, so we won't have to lookup aliases
   */
  function query()
  {
    $this->field_alias = $this->real_field;
  }

  /**
   * Make target search results click sortable
   * @param $order
   */
  function click_sort($order)
  {
    if (isset($this->field_alias)) {
      $params = $this->options['group_type'] != 'group' ? array('function' => $this->options['group_type']) : array();
      $this->query->add_orderby(NULL, NULL, $order, $this->field_alias, $params);
    }
  }

  /**
   * Override parent render.
   * @param $values
   * @return mixed|string
   */
  function render($values) {
    $value = $this->get_value($values);
    $value = $this->sanitize_value($value);
    $alias = isset($field) ? $this->aliases[$field] : $this->field_alias;
    if ($value == '1969-12-31 19:00:01') {
      return 'N/A';
    }

    // Re-format:
    $value = date('n/j/Y - H:i', strtotime($value));
    return $value;
  }
}
