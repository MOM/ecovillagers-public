<?php

/**
 * @file springboard_views_views_handler_field.inc
 *
 */

class springboard_views_views_handler_field extends views_handler_field
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
   * Override parent render.
   * @param $values
   * @return mixed|string
   */
  function render($values) {
    // print_r(array_keys((array)$values));
    if (!isset($values->node_fundraiser_donation_nid) || !isset($values->commerce_order_fundraiser_donation_order_id)) {
      return json_encode(array());
    }
    // Get the webform submission ID:
    $order_id = $values->commerce_order_fundraiser_donation_order_id;
    $sid = db_query("SELECT did FROM {fundraiser_donation} WHERE did = :order_id", array(':order_id' => $order_id))->fetchField();
    $nid = $values->node_fundraiser_donation_nid;

    $field_key = isset($field) ? $this->aliases[$field] : $this->field_alias;

    // Extract extra props:
    if ($field_key == 'unique_id') {
      return $order_id . '-' . uniqid($order_id + rand(1,100), TRUE); 
    }
    elseif ($field_key == 'extra_props') {
      static $node_components = array();
      module_load_include('inc', 'webform', 'includes/webform.submissions');

      // Fetch webform values:
      $submission = webform_get_submission($nid, $sid);

      if (!isset($node_components[$nid])) {
        $node = node_load($nid);
        $node_components[$nid] = $node->webform['components'];
      }
      $submitted_data = springboard_dw_convert_submission_to_keyvalue($submission, $node_components[$nid]);
      $props = springboard_dw_extract_submission_extra_props($submitted_data, $submission);

      // Extract extra props:
      $extra_props = array();
      $donation_keys = _springboard_dw_get_donation_data_keys_labels();
      foreach ($props as $prop_key => $prop_value) {
        if (!array_key_exists($prop_key, $donation_keys)) {
          $extra_props[$prop_key] = $prop_value;
        }
      }
      return json_encode($extra_props);
    }
  }
}
