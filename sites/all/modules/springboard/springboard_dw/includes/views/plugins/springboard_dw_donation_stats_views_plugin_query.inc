<?php
/**
 * @file springboard_dw_donation_stats_views_plugin_query.inc
 */

/**
 * Class springboard_dw_donation_stats_views_views_plugin_query
 * Override views default db query with data warehouse guzzle request.
 */
class springboard_dw_donation_stats_views_plugin_query extends views_plugin_query {
  /**
   * @param $base_table
   * @param $base_field
   * @param $options
   */
  function init($base_table, $base_field, $options) {
    parent::init($base_table, $base_field, $options);
  }

  /**
   * @param view $view
   */
  function execute(&$view) {
    if (!isset($view->args[0]) || !is_numeric($view->args[0])) {
      $view->result = array();
      return;    
    } 

    $start = microtime(TRUE);
    $method = 'GET';
    $target_donation_id = $view->args[0];
    $params = array(
      'formId' => $target_donation_id,
    );
    $view->result = array();

    // Fetch the statistics
    $endpoint = 'metrics/donation/count';
    $response = springboard_dw_api_call($endpoint, $params, $method);
    if (is_object($response) && method_exists($response, 'getBody')) {
      $response_data = json_decode((string) $response->getBody(), TRUE);
    }

    if (!empty($response_data)) {
      foreach ($response_data as $response_key => $value) {
        if (!is_array($value)) {
          continue;
        }
        // Break up first/latest donation data into individual fields:
        if (isset($value['donation_id']) && isset($value['transaction_date'])) {
          if ($response_key == 'first_submission') {
            $response_data['first_donation_id'] = $value['donation_id'];
            $response_data['first_submission_date'] = $value['transaction_date'];
          }
          elseif ($response_key == 'latest_submission') {
            $response_data['latest_donation_id'] = $value['donation_id'];
            $response_data['latest_submission_date'] = $value['transaction_date'];
          }
          unset($response_data[$response_key]);
        }
      }
      $response_data['latest_fetch'] = time();

      // Populate the status based on donation ID:
      $node_status = db_query("SELECT status FROM {node} WHERE nid = :nid", array(':nid' => $target_donation_id))
        ->fetchField();
      if ($node_status !== FALSE){
        $response_data['node_status'] = $node_status == 0 ? t('Not Published') : t('Published');
      }
      else {
        $response_data['node_status'] = t('N/A');
      }

      // Add commas to numeric values (See SB ticket #2128):
      $fields_needed_numeric_formatting = array('gifts', 'sustainers', 'first_time_donors', 'new_contacts');
      foreach ($fields_needed_numeric_formatting as $numeric_field_id) {
        if (isset($response_data[$numeric_field_id]) && is_numeric($response_data[$numeric_field_id])) {
          $response_data[$numeric_field_id] = number_format($response_data[$numeric_field_id], 0, '.', ',');
        }
      }

      $view->result[] = $response_data;
    }

    // Add currency symbol to amount raised:
    if (isset($view->result[0]['raised'])) {
      $default_currency_code = variable_get('commerce_default_currency', 'USD');
      $view->result[0]['raised'] = commerce_currency_format($view->result[0]['raised'], $default_currency_code, NULL, FALSE);
    }

    $view->execute_time = microtime(TRUE) - $start;
  }

  function add_orderby() {}
  function build(&$view) {}
  function add_field() {}
  function add_where() {}
  function add_where_expression() {}
  function ensure_table() {}
  function placeholder() {}
}
