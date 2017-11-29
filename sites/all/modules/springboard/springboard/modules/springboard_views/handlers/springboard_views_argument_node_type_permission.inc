<?php

/**
 * @file
 * Definition of springboard_views_argument_node_type_permission.
 */

/**
 * Argument handler to accept a node type with an additional permission check.
 */
class SpringboardViewsArgumentNodeTypePermission extends views_handler_argument_node_type {
  /**
   * Add the variable to the view argument options.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['permission_check'] = array('default' => FALSE, 'bool' => TRUE);
    return $options;
  }

  /**
   * Add the checkbox to the form.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Add the option to do the additional permission check.
    $form['permission_check'] = array(
      '#type' => 'checkbox',
      '#title' => t('Validate Permissions'),
      '#description' => t("If selected the user's permissions will be checked against the arguments."),
      '#default_value' => !empty($this->options['permission_check']),
      '#fieldset' => 'more',
    );
  }

  /**
   * Do the additional permission check on the node types.
   */
  function set_argument($arg) {
    if (
      !empty($arg)
      && !empty($this->options['permission_check'])
    ) {
      // Explode the argument string.
      $args = explode('+', $arg);
      foreach ($args as $key => $type) {
        // Remove types this user is not allowed to create.
        if (!node_access('create', $type)) {
          unset($args[$key]);
        }
      }

      // Put the remaining types back into the arg string.
      $arg = implode($args, '+');
    }

    return parent::set_argument($arg);
  }
}
