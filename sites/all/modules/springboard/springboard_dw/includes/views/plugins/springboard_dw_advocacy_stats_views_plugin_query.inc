<?php
/**
 * @file springboard_dw_advocacy_stats_views_plugin_query.inc
 */

/**
 * Class springboard_dw_advocacy_stats_views_views_plugin_query
 * Override views default db query with data warehouse guzzle request.
 */
class springboard_dw_advocacy_stats_views_plugin_query extends views_plugin_query {
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
    $target_node_id = $view->args[0];

    // Get the action ID for this form's node ID:
    $action_id = db_query("SELECT advocacy_id FROM {sba_form_id} WHERE nid = :nid", array(':nid' => $target_node_id))
      ->fetchField();

    if (!$action_id) {
      return;
    }

    $params = array(
      'actionId' => $action_id,
    );
    $view->result = array();
    $response_data = array();

    // Fetch the statistics
    $endpoint = 'metrics/action/count';
    $response = springboard_dw_api_call($endpoint, $params, $method);
    if (is_object($response) && method_exists($response, 'getBody')) {
      $response_data = json_decode((string) $response->getBody(), TRUE);
    }
    global $user;
    if ($user->uid == 1 && isset($_GET['debug']) && $_GET['debug'] == 1) {
      drupal_set_message('DW Request params:<pre>' . print_r($params, 1) . '</pre>');
      drupal_set_message('DW Response for metrics/action/count:<pre>' . print_r($response_data, 1) . '</pre>');
    }
    if (!empty($response_data)) {
      foreach ($response_data as $response_key => $value) {
        if (!is_array($value)) {
          continue;
        }
        // Break up first/latest donation data into individual fields:
        if (isset($value['action_id']) && isset($value['created_at']) && isset($value['action_id']) &&
          !empty($value['action_id']) && !empty($value['created_at'])) {
          if ($response_key == 'first_submission') {
            $response_data['first_action_id'] = $value['action_id'];
            $response_data['first_action_date'] = $value['created_at'];
          }
          elseif ($response_key == 'latest_submission') {
            $response_data['latest_action_id'] = $value['action_id'];
            $response_data['latest_action_date'] = $value['created_at'];
          }
          unset($response_data[$response_key]); 
        } 
      }
      $response_data['latest_fetch'] = time();

      // Populate the status based on node ID:
      $node_status = db_query("SELECT status FROM {node} WHERE nid = :nid", array(':nid' => $target_node_id))
        ->fetchField();
      if ($node_status){
        $response_data['node_status'] = $node_status == 0 ? t('Not Published') : t('Published');
      }
      else {
        $response_data['node_status'] = t('N/A');
      } 

      // Add commas to numeric values (See SB ticket #2128):
      $fields_needed_numeric_formatting = array('actions_count', 'messages_count', 'new_contacts');
      foreach ($fields_needed_numeric_formatting as $numeric_field_id) {
        if (isset($response_data[$numeric_field_id]) && is_numeric($response_data[$numeric_field_id])) {
          $response_data[$numeric_field_id] = number_format($response_data[$numeric_field_id], 0, '.', ',');
        }
      }

      $view->result[] = $response_data;
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
