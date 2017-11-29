<?php

/**
 * @file springboard_dw_views_handler_field.inc
 *
 */

class springboard_dw_views_handler_field extends views_handler_field
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

    if (!$value && is_array($values) && isset($values[$alias])) {
      $value = $values[$alias];
    }

    // Re-format donation stats first and last donation date values:
    if ($alias == 'first_submission' || $alias == 'latest_submission') {
      $value = date('m/d/Y H:i', strtotime($value));
    }

    // Remove status underscores:
    elseif ($alias == 'status') {
      $value = ucwords(str_replace('_', ' ', $value));
    }

    // Format donation stats latest fetch value:
    elseif ($alias == 'latest_fetch') {
      // Round down to the nearest 15 minutes if the fetch was recent; otherwise, use the exact fetch time:
      if (time() - $value > (60 * 15)) {
        $sync_time = $value;
      }
      else {
        $seconds = $value;
        $sync_time = floor($seconds / (15 * 60)) * (15 * 60);
        // Pad with 1 extra minute:
        $sync_time -= 60;
      }
      $value = format_interval(time() - $sync_time);
    }

    // Link emails to user pages if available:
    elseif ($alias == 'email') {
     
      $uid = db_query("SELECT uid FROM {users} WHERE mail = :email",
        array(':email' => $value))->fetchField();
      if ($uid) {
        $value = l($value, 'user/' . $uid . '/edit');
      }
    }
    // Replace transaction ID value with on-site link, if available:
    elseif ($alias == 'payment_link' && isset($values->donation_id)) {
      $value = $values->donation_id;
      if (!is_numeric($value)) {
        $value = 'N/A';
      }
      else {
        $order_id_exists = db_query("SELECT order_id FROM {commerce_order} WHERE order_id = :donation_id",
          array(':donation_id' => $value))
          ->fetchField();
        if ($order_id_exists) {
          $value = l('Payment', 'admin/commerce/orders/' . $value);
        }
        else {
          $value = 'N/A';
        }
      }
    }
    // Replace the form name with on-site link, if available:
    elseif ($alias == 'form_name' && isset($values->form_name['form_name']) && isset($values->form_name['form_id'])) {
      $value = l($values->form_name['form_name'], 'node/' . $values->form_name['form_id']);
    }
    elseif ($alias == 'recurs_monthly') {
      if ($value == 'recurs' || $value == '1') {
        $value = t('Yes');
      }
      else {
        $value = t('No');
      }
    }
    elseif ($alias == 'gateway') {
      if (strpos($value, '|') !== FALSE) {
        list($gateway_machine, $gateway_machine2) = explode('|', $value);
        if (isset($gateway_machine)) {
          $gateway_title = commerce_payment_method_get_title('title', $gateway_machine);
          if ($gateway_title) {
            $value = $gateway_title;
          }
          else {
            $value = $gateway_machine;
          }
        }
      }
      elseif (!isset($value) || empty($value)) {
        $value = 'N/A';
      }
    }
    return $value;
  }
}
