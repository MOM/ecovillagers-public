<?php

/**
 * Implements template_preprocess_page().
 * Remove the main menu from the page template
 */
function springboard_frontend_preprocess_page(&$variables) {
  $variables['main_menu'] = NULL;
}


/**
 * Add pills class to D7 main menu
 */
function springboard_base_menu_tree__main_menu($variables) {
  return '<ul class="menu nav nav-pills">' . $variables['tree'] . '</ul>';
}

/**
 * Remove the drupal standard classes from the menu, set active on li
 */
function springboard_base_menu_link__main_menu(array $variables) {
  //unset all the classes
  unset($variables['element']['#attributes']['class']);

  $path = current_path();
  $current = menu_get_item();
  if ($current == $path) {
    array_unshift($variables['element']['#attributes']['class'], 'active');
  }

  $element = $variables['element'];

  $sub_menu = '';

  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}