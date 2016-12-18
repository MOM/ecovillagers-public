<?php
/**
 * @file
 * Field implementation code for the campaign goals field.
 */

class SpringboardP2pCampaignGoalsField {

  /**
   * Validation.
   */
  public function validate($field, $langcode, $items, &$errors) {
    foreach ($items as $delta => $item) {
      $enabled_types = 0;
      $no_form_selected = FALSE;
      $goal_not_configured = FALSE;
      if (!empty($item['campaign_goals'])) {
        foreach ($item['campaign_goals']['form_types'] as $form_type => $content_types) {
          foreach ($content_types as $content_type) {
            $enabled_types += $content_type['enabled'];

            if ($content_type['enabled']) {
              if ($content_type['nid'] == '') {
                $no_form_selected = TRUE;
              }
              if (empty($content_type['goal_type']) || empty($content_type['goal_value'])) {
                $goal_not_configured = TRUE;
              }
            }
          }
        }

        if ($enabled_types > 1) {
          $errors[$field['field_name']][$langcode][$delta][] = array(
            'error' => 'springboard_p2p_fields_campaign_goals_too_many',
            'message' => t('Select only one goal type.'),
          );
        }
        elseif ($enabled_types < 1) {
          $errors[$field['field_name']][$langcode][$delta][] = array(
            'error' => 'springboard_p2p_fields_campaign_goals_not_enough',
            'message' => t('Select a goal type.'),
          );
        }
        elseif ($no_form_selected) {
          $errors[$field['field_name']][$langcode][$delta][] = array(
            'error' => 'springboard_p2p_fields_campaign_goals_no_nid',
            'message' => t('Select a form for the enabled goal type.'),
          );
        }
        elseif ($goal_not_configured) {
          $errors[$field['field_name']][$langcode][$delta][] = array(
            'error' => 'springboard_p2p_fields_campaign_goals_not_configured',
            'message' => t('Configure the goal type and goal value for the enabled goal.'),
          );
        }
      }
    }
  }

  /**
   * Item is empty.
   */
  public function isEmpty($item) {
    foreach ($item['campaign_goals']['form_types'] as $form_type => $content_types) {
      foreach ($content_types as $content_type) {
        if ($content_type['enabled'] || $content_type['nid'] != '') {
          return FALSE;
        }
      }
    }

    return TRUE;
  }

  /**
   * Presave of the field.
   */
  public function presave(&$items) {
    $rows = array();
    foreach ($items as $delta => $item) {
      $goal_set_id = isset($item['campaign_goals']['goal_set_id']) ? $item['campaign_goals']['goal_set_id'] : NULL;

      // This won't be set if we're saving somewhere other than a node add/edit
      // page, so skip attempting to save this goal set item.
      if (!isset($item['campaign_goals']['form_types'])) {
        continue;
      }

      foreach ($item['campaign_goals']['form_types'] as $form_type => $content_types) {
        foreach ($content_types as $content_type => $settings) {
          // Format the data as a record for the DB.
          $rows[$content_type] = $settings;
          $rows[$content_type]['type'] = $content_type;
        }
      }

      // Save the rows, get back a goal set id.
      // Then set the item to that goal set id.
      $items[$delta]['goal_set_id'] = $this->save($goal_set_id, $rows);
    }
  }

  /**
   * Delete the campaign goals for the given field items.
   *
   * @param array $items
   *   The field items..
   */
  public function delete(&$items) {
    foreach ($items as $item) {
      db_delete('springboard_p2p_fields_campaign_goals')
        ->condition('goal_set_id', $item['goal_set_id'])
        ->execute();
    }
  }

  /**
   * Saves campaign goals settings to the DB.
   *
   * @param int|null $goal_set_id
   *   If this is an existing set of records, the goal set ID.
   *   If this is a new set, NULL.
   * @param array $rows
   *   Each row is an array keyed by column name.
   *
   * @return int
   *   The goal set ID that the rows were saved with.
   */
  public function save($goal_set_id, $rows) {
    $table = 'springboard_p2p_fields_campaign_goals';

    if (is_null($goal_set_id)) {
      $next_id = db_query("SELECT MAX(goal_set_id) FROM {springboard_p2p_fields_campaign_goals}")->fetchField();
      $goal_set_id = ++$next_id;
    }

    foreach ($rows as $row) {
      $row['goal_set_id'] = $goal_set_id;

      $args = array(
        ':goal_set_id' => $row['goal_set_id'],
        ':type' => $row['type'],
      );
      $row_exists = db_query_range("SELECT COUNT(*) FROM {springboard_p2p_fields_campaign_goals} WHERE goal_set_id = :goal_set_id AND type = :type", 0, 1, $args)->fetchField();

      if ($row_exists) {
        drupal_write_record($table, $row, array('goal_set_id', 'type'));
      }
      else {
        drupal_write_record($table, $row);
      }
    }

    // Return the ID so the field knows the reference to save.
    return $goal_set_id;
  }

  /**
   * Get the campaign goals for the given goal set ID.
   *
   * @param int $goal_set_id
   *   The goal set ID.
   *
   * @return array|bool
   *   An associate array of the results keyed by type.
   */
  public function load($goal_set_id) {
    if (!is_null($goal_set_id)) {
      return db_query("SELECT * FROM {springboard_p2p_fields_campaign_goals} WHERE goal_set_id = :id", array(':id' => $goal_set_id))
        ->fetchAllAssoc('type', PDO::FETCH_ASSOC);
    }

    return FALSE;
  }

  /**
   * The widget form definition.
   */
  public function widgetForm($instance, $items, $delta, $element) {
    $goal_set_id = isset($items[$delta]['goal_set_id']) ? $items[$delta]['goal_set_id'] : NULL;
    if (!is_null($goal_set_id)) {
      $defaults = $this->load($goal_set_id);
    }

    $widget = $element;

    switch ($instance['widget']['type']) {
      case 'springboard_p2p_fields_campaign_goals_widget':
        $types = array(
          'fundraiser' => '<h2>Fundraising types</h2>',
          'webform_user' => '<h2>Other form types</h2>',
        );

        // Make this a fieldset with the three text fields.
        $widget += array(
          '#theme' => 'springboard_p2p_fields_campaign_goals',
          '#type' => 'fieldset',
          // #delta is set so that the validation function will be able
          // to access external value information which otherwise would be
          // unavailable.
          '#delta' => $delta,
          'goal_set_id' => array(
            '#type' => 'value',
            '#value' => $goal_set_id,
          ),
        );

        $widget['#attached']['js'] = array(
          drupal_get_path('module', 'springboard_p2p_fields') . '/springboard_p2p_fields.js',
        );

        $content_types = springboard_p2p_fields_get_sorted_content_types();
        foreach ($types as $form_type => $title) {
          $goal_options = array();
          $goal_type_default = NULL;
          if ($form_type == 'fundraiser') {
            $goal_type_default = 'amount';
            $goal_options['amount'] = t('Amount Raised');
          }
          else {
            // Non-fundraiser forms only support submissions.
            $goal_type_default = 'submissions';
            $goal_options['submissions'] = t('Submission Count');
          }

          $widget['form_types'][$form_type] = array(
            '#tree' => TRUE,
          );

          if (count($content_types[$form_type])) {
            $global_defaults = variable_get('springboard_p2p_' . $form_type . '_items', array());
            $display_title = FALSE;
            foreach ($content_types[$form_type] as $key => $name) {
              if (!isset($global_defaults[$key]) || $global_defaults[$key]['enabled'] == 0) {
                continue;
              }

              $display_title = TRUE;

              if (is_null($goal_type_default)) {
                $goal_type_default = isset($defaults[$key]['goal_type']) ? $defaults[$key]['goal_type'] : '';
              }

              $goal_value_prefix = '';
              $goal_value_suffix = '';

              if ($goal_type_default == 'submissions') {
                $goal_value_suffix = ' submissions';
              }
              elseif ($goal_type_default == 'amount') {
                $goal_value_prefix = '$ ';
              }

              $node_options = springboard_p2p_fields_get_node_options_by_types($key);
              $formatted_node_options = springboard_p2p_fields_format_node_options($node_options);

              $widget['form_types'][$form_type][$key] = array(
                'enabled' => array(
                  '#type' => 'checkbox',
                  '#title' => $name,
                  '#default_value' => isset($defaults[$key]['enabled']) ? $defaults[$key]['enabled'] : 0,
                ),
                'nid' => array(
                  '#type' => 'select',
                  '#options' => $formatted_node_options,
                  '#default_value' => isset($defaults[$key]['nid']) ? $defaults[$key]['nid'] : $global_defaults[$key]['nid'],
                  '#empty_value' => '',
                ),
                'campaign_id' => array(
                  '#type' => 'select',
                  '#options' => array(),
                  '#default_value' => isset($defaults[$key]['campaign_id']) ? $defaults[$key]['campaign_id'] : '',
                  '#empty_value' => '',
                  '#disabled' => TRUE,
                ),
                'goal_type' => array(
                  '#type' => 'select',
                  '#options' => $goal_options,
                  '#empty_value' => '',
                  '#default_value' => $goal_type_default,
                ),
                'goal_value' => array(
                  '#type' => 'textfield',
                  '#default_value' => isset($defaults[$key]['goal_value']) ? $defaults[$key]['goal_value'] : '',
                  '#field_prefix' => $goal_value_prefix,
                  '#field_suffix' => $goal_value_suffix,
                  '#prefix' => '<div class="springboard_p2p_goal_value">',
                  '#suffix' => '</div>',
                  '#maxlength' => 9,
                  '#size' => 8,
                ),
              );

              $widget['form_types'][$form_type][$key]['goal_type']['#attributes']['class'][] = 'springboard_p2p_goal_type';

              if (module_exists('market_source')) {
                $options = market_source_get_campaign_options();
                $widget['form_types'][$form_type][$key]['campaign_id']['#options'] += $options;
                $widget['form_types'][$form_type][$key]['campaign_id']['#disabled'] = FALSE;
              }

            }
            if ($display_title) {
              $widget['form_types'][$form_type]['#prefix'] = $title;
            }

          }
        }
        break;
    }

    $element['campaign_goals'] = $widget;
    return $element;
  }

  /**
   * Formatter view.
   */
  public function formatterView($entity_type, $entity, $items, $display) {
    $element = array();

    if ($display['type'] == 'springboard_p2p_fields_campaign_goals_default') {
      foreach ($items as $delta => $value) {
        $goals = $this->load($value['goal_set_id']);
        if ($goals) {
          foreach ($goals as $type => $goal) {
            if ($goal['enabled']) {
              $element[$delta][$type] = springboard_p2p_fields_format_campaign_goal_value($goal);
            }
          }
        }
      }
    }
    return $element;
  }

}
