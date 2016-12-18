<?php

/**
 * Implements template_preprocess_html().
 */
function springboard_base_preprocess_html(&$variables) {
  // Show a warning message if jQuery Update is not enabled.
  if (!module_exists('jquery_update') && user_access('administer theme')) {
    drupal_set_message(t("Please install the !link with version 1.7 of jQuery or higher.", array('!link' => l(t('jQuery Update module'), 'http://drupal.org/project/jquery_update'))), 'warning');
  }
  // Show a warning message if jQuery Update is not set to at least version 1.7
  elseif (module_exists('jquery_update') && version_compare(variable_get('jquery_update_jquery_version', 0), '1.7', '<') && user_access('administer theme')) {
    drupal_set_message(t("Please enable jQuery version 1.7 or higher in the !link.", array('!link' => l(t('jQuery Update settings'), 'admin/config/development/jquery_update'))), 'warning');
  }

  // Compile a list of classes that are going to be applied to the body element.
  // This allows advanced theming based on context (home page, node of certain type, etc.).
  // Add a class that tells us whether we're on the front page or not.
  $variables['classes_array'][] = $variables['is_front'] ? 'front' : 'not-front';
  // Add a class that tells us whether the page is viewed by an authenticated user or not.
  $variables['classes_array'][] = $variables['logged_in'] ? 'logged-in' : 'not-logged-in';

  // If on an individual node page, add the node type to body classes.
  if ($node = menu_get_object()) {
    $variables['classes_array'][] = drupal_html_class('node-type-' . $node->type);
  }

  // Add node edit / add / view classes.
  if (arg(0) == 'node' && arg(2) == 'edit') {
    $variables['classes_array'][] = 'page-node-edit';
  }

  if (arg(0) == 'node' && arg(1) == 'add') {
    $variables['classes_array'][] = 'page-node-add';
  }

  if (arg(0) == 'node' && arg(2) === null) {
    $variables['classes_array'][] = 'page-node-view';
  }

  // RDFa allows annotation of XHTML pages with RDF data, while GRDDL provides
  // mechanisms for extraction of this RDF content via XSLT transformation
  // using an associated GRDDL profile.
  $variables['rdf_namespaces'] = drupal_get_rdf_namespaces();
  $variables['grddl_profile'] = 'http://www.w3.org/1999/xhtml/vocab';
  $variables['language'] = $GLOBALS['language'];
  $variables['language']->dir = $GLOBALS['language']->direction ? 'rtl' : 'ltr';

  // Add favicon.
  if (theme_get_setting('toggle_favicon')) {
    $favicon = theme_get_setting('favicon');
    $type = theme_get_setting('favicon_mimetype');
    drupal_add_html_head_link(array('rel' => 'shortcut icon', 'href' => drupal_strip_dangerous_protocols($favicon), 'type' => $type));
  }

  // Construct page title.
  if (drupal_get_title()) {
    $head_title = array(
      'title' => strip_tags(drupal_get_title()),
      'name' => check_plain(variable_get('site_name', 'Drupal')),
    );
  }
  else {
    $head_title = array('name' => check_plain(variable_get('site_name', 'Drupal')));
    if (variable_get('site_slogan', '')) {
      $head_title['slogan'] = filter_xss_admin(variable_get('site_slogan', ''));
    }
  }
  $variables['head_title_array'] = $head_title;
  $variables['head_title'] = implode(' | ', $head_title);

  // Add an ie 10 and 11 classes for better theming.
  // Note, @cc_on did not seem to work for ie11 even changing doc mode and class to '11'.
  $inline_script = <<<EOL
  <!--[if !IE]><!--><script>if (Function('/*@cc_on return document.documentMode===10@*/') ()) {
        document.documentElement.className+=' ie10';
      }
    var isIE11 = !!navigator.userAgent.match(/Trident\/7\./)
    if (isIE11 == true) {
    document.documentElement.className += ' ie11';
  }
  </script><!--<![endif]-->
EOL;
  $element = array(
    '#type' => 'markup',
    '#markup' => $inline_script,
  );
  drupal_add_html_head($element, 'javascript');

}

/**
 * Implements template_preprocess_page().
 */
function springboard_base_preprocess_page(&$variables) {
  // Move some variables to the top level for themer convenience and template cleanliness.
  $variables['show_messages'] = $variables['page']['#show_messages'];

  foreach (system_region_list($GLOBALS['theme']) as $region_key => $region_name) {
    if (!isset($variables['page'][$region_key])) {
      $variables['page'][$region_key] = array();
    }
  }

  // Set up layout variable.
  $variables['layout'] = 'none';
  if (isset($variables['page']['sidebar_first']) && !empty($variables['page']['sidebar_first'])) {
    $variables['layout'] = 'first';
  }
  if (isset($variables['page']['sidebar_second']) && !empty($variables['page']['sidebar_second'])) {
    $variables['layout'] = ($variables['layout'] == 'first') ? 'both' : 'second';
  }

  $variables['base_path'] = base_path();
  $variables['front_page'] = url();
  $variables['feed_icons'] = drupal_get_feeds();
  $variables['language'] = $GLOBALS['language'];
  $variables['language']->dir = $GLOBALS['language']->direction ? 'rtl' : 'ltr';
  $variables['logo'] = theme_get_setting('logo');

  $variables['secondary_menu'] = theme_get_setting('toggle_secondary_menu') ? menu_secondary_menu() : array();
  $variables['action_links'] = menu_local_actions();
  $variables['site_name'] = (theme_get_setting('toggle_name') ? filter_xss_admin(variable_get('site_name', 'Drupal')) : '');
  $variables['site_slogan'] = (theme_get_setting('toggle_slogan') ? filter_xss_admin(variable_get('site_slogan', '')) : '');
  $variables['tabs'] = menu_local_tabs();

  // Set up main-menu array to clean up page template.
  $variables['main_menu'] = array(
    'links' => theme_get_setting('toggle_main_menu') ? menu_main_menu() : array(),
    'attributes' => array(
      'id' => 'main-menu-links',
      'class' => array('nav', 'clearfix'),
    ),
    'heading' => array(
      'text' => t('Main menu'),
      'level' => 'h2',
      'class' => array('element-invisible'),
    ),
  );
  if ($node = menu_get_object()) {
    $variables['node'] = $node;
  }

  // Add Font awesome cdn.
  // http://fortawesome.github.io/Font-Awesome/get-started/
  drupal_add_css('//maxcdn.bootstrapcdn.com/font-awesome/4.1.0/css/font-awesome.css',
    array(
      'type' => 'external',
    )
  );

}

/**
 * Overrides theme_form_element().
 */

function springboard_base_form_element($variables) {
  $element = &$variables['element'];

  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  $type = $element['#type'];

  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }

  // Add bootstrap group class
  $attributes['class'] = array(
    'form-item',
    'form-type-' . $type,
  );

  // The VBO select all checkbox does not have #parents, so this check
  // is included to avoid issues.
  if (isset($element['#parents'])) {
    $concatenated_class = str_replace('_', '-', implode('-', $element['#parents']));
    $attributes['class'][] = 'form-item-' . $concatenated_class;
  }

  $attributes['class'][] = 'control-group';

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<div class="field-prefix">' . $element['#field_prefix'] . '</div>' : '';
  $suffix = isset($element['#field_suffix']) ? '<div class="field-suffix">' . $element['#field_suffix'] . '</div>' : '';

  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";
  switch ($element['#title_display']) {
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'after':
      $output .= ' ' . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }
  if (!empty($element['#description'])) {
    $output .= '<div class="description">' . $element['#description'] . "</div>\n";
  }
  $output .= '</div>';
  return $output;
}

/**
 * Overrides theme_webform_element()
 */

function springboard_base_webform_element($variables) {
  // Ensure defaults.
  $variables['element'] += array(
    '#title_display' => 'before',
  );

  $element = $variables['element'];

  // All elements using this for display only are given the "display" type.
  if (isset($element['#format']) && $element['#format'] == 'html') {
    $type = 'display';
  }
  else {
    $type = (isset($element['#type']) && !in_array($element['#type'], array('markup', 'textfield', 'webform_email', 'webform_number'))) ? $element['#type'] : $element['#webform_component']['type'];
  }

  // Convert the parents array into a string, excluding the "submitted" wrapper.
  $nested_level = $element['#parents'][0] == 'submitted' ? 1 : 0;
  $parents = str_replace('_', '-', implode('--', array_slice($element['#parents'], $nested_level)));

  $wrapper_classes = array(
    'form-item',
    'webform-component',
    'webform-component-' . $type,
    'control-group',
  );

  $output = '<div class="' . implode(' ', $wrapper_classes) . '" id="webform-component-' . $parents . '">' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }

  $prefix = isset($element['#field_prefix']) ? '<div class="field-prefix">' . _webform_filter_xss($element['#field_prefix']) . '</div>' : '';
  $suffix = isset($element['#field_suffix']) ? '<div class="field-suffix">' . _webform_filter_xss($element['#field_suffix']) . '</div>' : '';

  switch ($element['#title_display']) {
    case 'inline':
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'after':
      $output .= ' ' . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $element['#children'] . $suffix . "\n";
      break;
  }
  if (!empty($element['#description'])) {
    $output .= ' <div class="description">' . $element['#description'] . "</div>\n";
  }
  $output .= '</div>';

  return $output;
}

/**
 * Overrides theme_form()
 */
function springboard_base_form($variables) {
  $element = $variables['element'];
  if (isset($element['#action'])) {
    $element['#attributes']['action'] = drupal_strip_dangerous_protocols($element['#action']);
  }
  element_set_attributes($element, array('method', 'id'));
  if (empty($element['#attributes']['accept-charset'])) {
    $element['#attributes']['accept-charset'] = "UTF-8";
  }
  // Anonymous DIV to satisfy XHTML compliance.
  return '<form' . drupal_attributes($element['#attributes']) . '>' . $element['#children'] . '</form>';
}

/**
 * Overrides theme_checkboxes()
 */
function springboard_base_checkboxes($variables) {
  $element = $variables['element'];
  $attributes = array();
  if (isset($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  if (isset($element['#attributes']['title'])) {
    $attributes['title'] = $element['#attributes']['title'];
  }
  return '<div' . drupal_attributes($attributes) . '>' . (!empty($element['#children']) ? $element['#children'] : '') . '</div>';
}

/**
 * Overrides theme_date()
 */
function springboard_base_date($variables) {
  $element = $variables['element'];

  $attributes = array();
  if (isset($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  if (!empty($element['#attributes']['class'])) {
    $attributes['class'] = (array) $element['#attributes']['class'];
  }

  return '<div' . drupal_attributes($attributes) . '>' . drupal_render_children($element) . '</div>';
}

/**
 * Overrides theme_file()
 */
function springboard_base_file($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'file';
  element_set_attributes($element, array('id', 'name', 'size'));
  //_form_set_class($element, array('form-file'));

  return '<input' . drupal_attributes($element['#attributes']) . ' />';
}

/**
 * Overrides theme_password()
 */
function springboard_base_password($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'password';
  element_set_attributes($element, array('id', 'name', 'size', 'maxlength'));
  _form_set_class($element, array('form-text'));

  return '<input' . drupal_attributes($element['#attributes']) . ' />';
}

/**
 * Overrides theme_radio()
 */
function springboard_base_radio($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'radio';
  element_set_attributes($element, array('id', 'name', '#return_value' => 'value'));

  if (isset($element['#return_value']) && $element['#value'] !== FALSE && $element['#value'] == $element['#return_value']) {
    $element['#attributes']['checked'] = 'checked';
  }
  //_form_set_class($element, array('form-radio'));

  return '<input' . drupal_attributes($element['#attributes']) . ' />';
}

/**
 * Overrides theme_radios()
 */
function springboard_base_radios($variables) {
  $element = $variables['element'];
  $attributes = array();
  if (isset($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  /*$attributes['class'] = 'form-radios';
  if (!empty($element['#attributes']['class'])) {
    $attributes['class'] .= ' ' . implode(' ', $element['#attributes']['class']);
  }*/
  if (isset($element['#attributes']['title'])) {
    $attributes['title'] = $element['#attributes']['title'];
  }
  return '<div' . drupal_attributes($attributes) . '>' . (!empty($element['#children']) ? $element['#children'] : '') . '</div>';
}

/**
 * Overrides theme_select()
 */
function springboard_base_select($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id', 'name', 'size'));
  _form_set_class($element, array('form-select'));

  return '<select' . drupal_attributes($element['#attributes']) . '>' . form_select_options($element) . '</select>';
}

/**
 * Overrides theme_textarea()
 */
function springboard_base_textarea($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id', 'name', 'cols', 'rows'));
  _form_set_class($element, array('form-textarea'));
  // Add resizable behavior.
  /*if (!empty($element['#resizable'])) {
    drupal_add_library('system', 'drupal.textarea');
    $wrapper_attributes['class'][] = 'resizable';
  }*/
  $output = '<textarea' . drupal_attributes($element['#attributes']) . '>' . check_plain($element['#value']) . '</textarea>';
  return $output;
}

/**
 * Overrides theme_textfield()
 */
function springboard_base_textfield($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'text';
  element_set_attributes($element, array('id', 'name', 'value', 'size', 'maxlength'));
  _form_set_class($element, array('form-text'));

  $extra = '';
  if ($element['#autocomplete_path'] && drupal_valid_path($element['#autocomplete_path'])) {
    drupal_add_library('system', 'drupal.autocomplete');
    $element['#attributes']['class'][] = 'form-autocomplete';

    $attributes = array();
    $attributes['type'] = 'hidden';
    $attributes['id'] = $element['#attributes']['id'] . '-autocomplete';
    $attributes['value'] = url($element['#autocomplete_path'], array('absolute' => TRUE));
    $attributes['disabled'] = 'disabled';
    $attributes['class'][] = 'autocomplete';
    $extra = '<input' . drupal_attributes($attributes) . ' />';
  }

  $output = '<input' . drupal_attributes($element['#attributes']) . ' />';

  return $output . $extra;
}

/**
 * Overrides theme_button()
 */
function springboard_base_button($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'submit';
  element_set_attributes($element, array('id', 'name', 'value'));

  /*$element['#attributes']['class'][] = 'form-' . $element['#button_type'];
  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'form-button-disabled';
  }*/

  return '<input' . drupal_attributes($element['#attributes']) . ' />';
}


/**
 * Overrdies theme_status_messages().
 * Add bootstrap's message classes to messages.
 */

function springboard_base_status_messages($variables) {
  $display = $variables['display'];
  $output = '';

  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
  );
  foreach (drupal_get_messages($display) as $type => $messages) {

    // $status throwing warning as undefined
    // $output .= "<div class=\"alert alert-$status \">\n";
    // Fix and re-add to output below
    $output .= "<div class=\"alert " . $type . "\">\n";
    // bootstrap dismiss button
    $output .= "<button type=\"button\" class=\"close\" data-dismiss=\"alert\">&times;</button>\n";
    if (!empty($status_heading[$type])) {
      $output .= '<h2 class="element-invisible">' . $status_heading[$type] . "</h2>\n";
    }
    if (count($messages) > 1) {
      $output .= " <ul>\n";
      foreach ($messages as $message) {
        $output .= '  <li>' . $message . "</li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      $output .= $messages[0];
    }
    $output .= "</div>\n";
  }
  return $output;
}

/**
 * Overrides theme_image_button()
 */
function springboard_base_image_button($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'image';
  element_set_attributes($element, array('id', 'name', 'value'));

  $element['#attributes']['src'] = file_create_url($element['#src']);
  if (!empty($element['#title'])) {
    $element['#attributes']['alt'] = $element['#title'];
    $element['#attributes']['title'] = $element['#title'];
  }

  //$element['#attributes']['class'][] = 'form-' . $element['#button_type'];
  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'form-button-disabled';
  }

  return '<input' . drupal_attributes($element['#attributes']) . ' />';
}

/**
 * Overrides theme_menu_tree().
 * Update classes to work with Bootstrap
 */

function springboard_base_menu_tree($variables) {
  return '<ul class="nav">' . $variables['tree'] . '</ul>';
}

/**
 * Overrides theme_menu_link().
 */
function springboard_base_menu_link(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';

  // Add a menu name as a class.
  $name_id = strtolower(strip_tags($element['#title']));
  $pattern = '/[^a-z]+/ ';
  $menu_name = preg_replace($pattern, '', $name_id);

  if (isset($element['#below'])) {
    // Prevent dropdown functions from being added to management menu so it
    // does not affect the navbar module.
    if (($element['#original_link']['menu_name'] == 'management') && (module_exists('navbar'))) {
      $sub_menu = drupal_render($element['#below']);
    }
    else {
      // Add our own wrapper.
      unset($element['#below']['#theme_wrappers']);
      $sub_menu = '<ul class="dropdown-menu">' . drupal_render($element['#below']) . '</ul>';
      $element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';
      $element['#localized_options']['attributes']['data-toggle'] = 'sb-dropdown';

      // Check if this element is nested within another.
      if ((!empty($element['#original_link']['depth'])) && ($element['#original_link']['depth'] > 1)) {
        // Generate as dropdown submenu.
        $element['#attributes']['class'][] = 'dropdown-submenu';
      }
      else {
        // Generate as standard dropdown.
        $element['#attributes']['class'][] = 'dropdown';
        $element['#localized_options']['html'] = TRUE;
      }

      // Set dropdown trigger element to # to prevent inadvertant page loading
      // when a submenu link is clicked.
      $element['#localized_options']['attributes']['data-target'] = $element['#href'];
    }
  }
  // On primary navigation menu, class 'active' is not set on active menu item.
  // @see https://drupal.org/node/1896674
  if (($element['#href'] == $_GET['q'] || ($element['#href'] == '<front>' && drupal_is_front_page())) && (empty($element['#localized_options']['language']))) {
    $element['#attributes']['class'][] = 'active';
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  // add an ID based on the mlid to each item for individualized styles
  $element['#attributes']['id'] = 'mlid-' . $element['#original_link']['mlid'];
  $element['#attributes']['class'][] = 'menu-' . $element['#original_link']['mlid'] . ' ' . $menu_name;
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Implements hook_form_alter()
 * Add button class to form submit buttons.
 */
function springboard_base_form_alter(&$form, &$form_state, $form_id) {
  $form['actions']['submit']['#attributes']['class'][] = 'btn';
}
