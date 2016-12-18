<?php
/**
 * @file
 * Provide views hook implementations and helper functions.
 */

/**
 * Implements hook_views_handlers().
 */
function springboard_views_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'springboard_views') . '/handlers',
    ),
    'handlers' => array(
      'fundraiser_handler_field_donation_amounts' => array(
        'parent' => 'views_handler_field_prerender_list',
      ),
      'queue_api_handler_field_batch_id' => array(
        'parent' => 'views_handler_field',
      ),
      'springboard_webform_hidden_component_values' => array(
        'parent' => 'views_handler_field',
      ),
    ),
  );
}

/**
 * Implements hook_views_data().
 */
function springboard_views_views_data() {
  $data = _springboard_views_invoke_all('views_data');

  // Add Views table information for Webform hidden components
  $data['webform_component']['table']['group'] = t('Webform');
  $data['webform_component']['table']['base'] = array(
    'field' => 'nid',
    'title' => t('Webform components'),
    'help' => t('Webform component values'),
  );
  $data['webform_component']['table']['join'] = array(
    'node' => array(
      'type' => 'INNER',
      'left_field' => 'nid',
      'field' => 'nid',
    ),
    'webform_submissions' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );
  $data['webform_component']['value'] = array(
    'title' => t('Webform Hidden Components'),
    'help' => t('Display default values of webform hidden components.'),
    'relationship' => array(
      'base' => 'node',
      'field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('Webform node'),
    ),
    'field' => array(
      'handler' => 'springboard_webform_hidden_component_values',
      'click sortable' => TRUE,
    ),
  );

  return $data;
}

/**
 * Scan the modules directory for enabled Springboard modules.
 *
 * @return array
 *   Enabled Springboard modules that have views integration in this module.
 */
function _springboard_views_load_includes() {
  static $modules_enabled = array();
  if (empty($modules_enabled)) {
    $path = drupal_get_path('module', 'springboard_views') . '/modules';
    $modules_list = file_scan_directory($path, '/\.views.inc/');
    if (!empty($modules_list) && is_array($modules_list)) {
      foreach ($modules_list as $path => $file) {
        if (!empty($file->name) && preg_match('/(.+)\.views/', $file->name, $match) !== FALSE) {
          $module = $match[1];
          if (module_exists($module)) {
            module_load_include('inc', 'springboard_views', 'modules/' . $file->name);
            $modules_enabled[$module] = $file;
          }
        }
      }
    }
  }
  return $modules_enabled;
}

/**
 * For all enabled Springboard modules, try calling $hook. Return all results.
 */
function _springboard_views_invoke_all($hook) {
  $data = array();
  foreach (_springboard_views_load_includes() as $module => $file) {
    $function = 'springboard_views_' . $module . '_' . $hook;
    if (function_exists($function)) {
      $module_data = $function();
      if (!empty($module_data) && is_array($module_data)) {
        if ($hook == 'views_handlers') {
          drupal_set_message('mod data: ' . print_r($module_data, TRUE)); // Coder: is ok.
        }
        $data = array_merge_recursive($data, $module_data);
        if ($hook == 'views_handlers') {
          drupal_set_message('first: ' . print_r($data, TRUE)); // Coder: is ok.
        }
      }
    }
  }
  if ($hook == 'views_handlers') {
    drupal_set_message(print_r($data, TRUE)); // Coder: is ok.
  }
  return $data;
}

/**
 * Enhancements to the standard views_join class that will allow extra fields
 * to be used in the join clause.
 *
 * 'extra' array now can accept the following keys:
 *   - table type: 'left' or 'right' (default).
 *   - value type: 'field' or 'value' (default).
 *   - value: can now be a field name, if value type is field.
 */
class springboard_views_join extends views_join {
  /**
   * Build the SQL for the join this object represents.
   */
  public function join($table, &$query) {
    if (empty($this->definition['table formula'])) {
      $right_table = "{" . $this->table . "}";
    }
    else {
      $right_table = $this->definition['table formula'];
    }

    if ($this->left_table) {
      $left = $query->get_table_info($this->left_table);
      $left_field = "$left[alias].$this->left_field";
    }
    else {
      // This can be used if left_field is a formula or something. It should be used only *very* rarely.
      $left_field = $this->left_field;
    }
    $output = " $this->type JOIN $right_table $table[alias] ON $left_field = $table[alias].$this->field";
    // Tack on the extra.
    if (isset($this->extra)) {
      if (is_array($this->extra)) {
        $extras = array();
        foreach ($this->extra as $info) {
          $extra = '';
          // Figure out the table name. Remember, only use aliases provided
          // if at all possible.
          $join_table = '';
          if (isset($info['table'])) {
            $table_type = isset($info['table type']) ? $info['table type'] : 'right';
            if ($table_type == 'left') {
              $extra_table = $query->get_table_info($this->left_table);
              $join_table = $extra_table['alias'] . '.';
            }
            else {
              $join_table = $info['table'] . '.';
            }
          }
          else {
            $join_table = $table['alias'] . '.';
          }
          // And now deal with the value and the operator.  Set $q to
          // a single-quote for non-numeric values and the
          // empty-string for numeric values, then wrap all values in $q.
          if (isset($info['value type']) && $info['value type'] == 'field') {
            $left = $query->get_table_info($this->left_table);
            if (!empty($left)) {
              $extra_left_field = "$left[alias].$info[field]";
              $extra_field = $info['value'];
              $extras[] = "$extra_left_field = $join_table$extra_field";
            }
          }
          else {
            $raw_value = $this->db_safe($info['value'], $info);
            $q = (empty($info['numeric']) ? "'" : '');
            if (is_array($raw_value)) {
              $operator = !empty($info['operator']) ? $info['operator'] : 'IN';
              // Transform from IN() notation to = notation if just one value.
              if (count($raw_value) == 1) {
                $value = $q . array_shift($raw_value) . $q;
                $operator = $operator == 'NOT IN' ? '!=' : '=';
              }
              else {
                $value = "($q" . implode("$q, $q", $raw_value) . "$q)";
              }
            }
            else {
              $operator = !empty($info['operator']) ? $info['operator'] : '=';
              $value = "$q$raw_value$q";
            }
            $extras[] = "$join_table$info[field] $operator $value";
          }
        }
        if ($extras) {
          if (count($extras) == 1) {
            $output .= ' AND ' . array_shift($extras);
          }
          else {
            $output .= ' AND (' . implode(' ' . $this->extra_type . ' ', $extras) . ')';
          }
        }
      }
      elseif ($this->extra && is_string($this->extra)) {
        $output .= " AND ($this->extra)";
      }
    }
    return $output;
  }
}
