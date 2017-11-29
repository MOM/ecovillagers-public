<?php

/**
 * @file
 * Definition of views_handler_area_text.
 */

/**
 * Views area text handler for special handling of an empty result.
 */
class SpringboardAdminViewsHandlerAreaEmptyContentTypeResult extends views_handler_area {

  /**
   * Render a message for a content of the type in the argument.
   *
   * On an empty result this looks to see if the site has any of that type.
   */
  public function render($empty = false) {
    // The first argument should be a content type name.
    if ($this->view->args && is_string($this->view->args[0])) {
      $type = node_type_get_type($this->view->args[0]);

      if (!empty($type->type)) {
        // Query to see if the site has any of these node types.
        $no_nodes = FALSE;
        $query = new EntityFieldQuery();
        $query->entityCondition('entity_type', 'node')
          ->entityCondition('bundle', $type->type);
        $result = $query->execute();

        if (empty($result['node'])) {
          $no_nodes = TRUE;
        }

        // If there are no nodes then show the message.
        if ($no_nodes) {
          // Hide the exposed form on the view.
          $this->view->exposed_widgets = FALSE;

          $output = '<p>';
          $output .= t(
            "You haven't created any @names yet.",
            ['@name' => $type->name]
          );
          $output .= '</p>';

          // Add the button for users with access.
          if (node_access('create', $type->type)) {
            $output .= l(
              t('Create @name', ['@name' => $type->name]),
              'node/add/' . preg_replace('/_/', '-', $type->type),
              [
                'attributes' => [
                  'class' => ['button', 'add-button'],
                ],
              ]
            );
          }

          return $output;
        }
      }
    }

    // Return a standard message for an empty result.
    return t('Your search returned 0 results, please try again.');
  }

}
