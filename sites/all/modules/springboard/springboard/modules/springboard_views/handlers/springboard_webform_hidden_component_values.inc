<?php

/**
 * @file
 * Defines a Views field handler for displaying values
 *   of webform hidden components.
 */

class springboard_webform_hidden_component_values extends views_handler_field {
  // Add an option to the field handler to choose
  // which component's value is displayed.
  public function option_definition() {
    $options = parent::option_definition();
    $options['webform_component_options'] = array('default' => NULL);
    return $options;
  }

  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    // Build a list of distinct hidden components
    // defined by webform or other modules.
    $result = db_select('webform_component', 'wc')
      ->fields('wc', array('form_key', 'name'))
      ->condition('wc.type', 'hidden', '=')
      ->distinct()
      ->execute();
    $options = array();
    while ($record = $result->fetchAssoc()) {
      $options[$record['form_key']] = $record['name'];
    }
    // Create a form item of options for which component's value to display.
    $form['webform_component_options'] = array(
      '#title' => t('Choose a component to display a value for'),
      '#type' => 'radios',
      '#options' => $options,
      '#required' => TRUE,
      '#default_value' => $this->options['webform_component_options'],
    );
  }

  public function query() {
    // Join in an instance of the webform_component table
    // for the form_key value chosen.
    $this->ensure_my_table();
    $first = array(
      'left_table' => 'node',
      'left_field' => 'nid',
      'table' => 'webform_component',
      'field' => 'nid',
    );
    $join = new views_join();
    $join->definition = $first;
    $join->construct();
    $join->adjusted = TRUE;

    $alias = 'webform_component_' . $this->options['webform_component_options'];
    $this->query->add_field($alias, 'value', $alias . '_value');
    $this->query->add_relationship($alias, $join, 'node');
    $this->query->add_where(
      0,
      db_and()
        ->condition('webform_component_' . $this->options['webform_component_options'] . '.form_key', $this->options['webform_component_options'], "=")
    );
  }

  public function render($values) {
    // Output the value.
    $alias = 'webform_component_' . $this->options['webform_component_options'] . '_value';
    return check_plain($values->$alias);
  }
}
