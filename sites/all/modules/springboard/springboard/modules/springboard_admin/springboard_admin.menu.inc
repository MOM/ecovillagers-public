<?php

/**
 * @file
 * Definitions for the Springboard Administration menu.
 */

/**
 * Defines the custom menu "Springboard Administration".
 *
 * @return array
 *   A associative array describing a Drupal custom menu, as defined by
 *   menu_save().
 */
function springboard_admin_admin_menu() {
  return array(
    'menu_name' => 'springboard_admin_menu',
    'title' => 'Springboard Administration',
    'description' => 'Menu for the custom Springboard administration interface'
  );
}

/**
 * Defines menu items for the custom menu "Springboard Administration".
 *
 * @return array
 *   A heirarchical array of menu items for the Springboard Administratio menu.
 *
 *   Each item in the array is a associative array representing a menu link
 *   item, with elements as defined by menu_link_save().
 */
function springboard_admin_admin_menu_items() {
  global $user;

  $items = array();
  // Top Level: Sprinboard (dashboard).
  $items['admin/springboard'] = array(
    'link_path' => 'admin/springboard',
    'link_title' => t('Springboard'),
    'menu_name' => 'springboard_admin_menu',
    'expanded' => 1,
    'customized' => 1,
    'weight' => -110,
    '_children' => array(),
  );

  // Populate the springboard logo drop-down links:
  $default_logo_links = 
    'Your Website|' . variable_get('springboard_drupal_path', 'http://drupal.org') . "\n" .
    'Salesforce.com|http://login.salesforce.com';
  $logo_links_field_value = variable_get('springboard_logo_links', $default_logo_links);
  $logo_links = _springboard_admin_parse_header_logo_links($logo_links_field_value);
  $count = 0;
  foreach ($logo_links as $link_title => $link_path) {
    $items['admin/springboard']['_children']['website-' . $count] = array(
      'link_path' => $link_path,
      'link_title' => $link_title,
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 1,
      'external' => 1,
      'customized' => 1,
      'weight' => $count,
      'options' => array('attributes' => array('target' => '_blank')),
    );
    $count++;
  }

  if (module_exists('fundraiser')) {
    // Top Level: Fundraiser.
    $items['admin/springboard/donation-forms/all'] = array(
      'link_path' => 'admin/springboard/donation-forms/all',
      'link_title' => t('Fundraising'),
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 1,
      'customized' => 1,
      'weight' => -100,
      '_children' => array(),
    );

    // Create a menu item for each type of webform.
    // In the future, we will use an intermediate page to choose the form type.
    $types = node_type_get_types();

    foreach ($types as $type) {
      if ($type && fundraiser_is_donation_type($type->type) && user_access('Access the Springboard dashboard')) {
        $link_path = 'admin/springboard/donation-forms/' . $type->type;
        // Add an s to the name.
        $link_title = $type->name . (substr($type->name, -1) != 's' ? 's' : '');

        $items['admin/springboard/donation-forms/all']['_children'][$link_path] = array(
          'link_path' => $link_path,
          'link_title' => t('@link_title', ['@link_title' => $link_title]),
          'menu_name' => 'springboard_admin_menu',
          'expanded' => 1,
          'customized' => 1,
        );
      }
    }
  }

  if(module_exists('webform_user')) {
    // Top Level: Custom Forms.
    $items['admin/springboard/forms/all'] = array(
      'link_path' => 'admin/springboard/forms/all',
      'link_title' => t('Custom Forms'),
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 1,
      'customized' => 1,
      'weight' => -60,
      '_children' => array(),
    );

    // List all non-Springboard webform types:
    $webform_node_types = array_filter(variable_get('webform_node_types', array()));
    foreach ($webform_node_types as $type) {
      $result = fundraiser_is_donation_type($type);
      if (function_exists('fundraiser_is_donation_type') && fundraiser_is_donation_type($type)) {
        continue;
      }
      if (function_exists('springboard_advocacy_is_action_type') && springboard_advocacy_is_action_type($type)) {
        continue;
      }
      if (function_exists('springboard_petition_is_petition_type') && springboard_petition_is_petition_type($type)) {
        continue;
      }
      if (module_exists('fundraiser_sustainers_upgrade') && $type == 'sustainers_upgrade_form') {
        continue;
      }
      $items['admin/springboard/forms/all']['_children']['admin/springboard/forms/' . $type] = array(
        'link_path' => 'admin/springboard/forms/' . $type,
        'link_title' => node_type_get_name($type) . (substr($type, -1) != 's' ? 's' : ''),
        'menu_name' => 'springboard_admin_menu',
        'expanded' => 1,
        'customized' => 1,
      );
    }
  }

  // Top Level: Assets
  $items['admin/springboard/asset-library'] = array(
    'link_path' => 'admin/springboard/asset-library',
    'link_title' => t('Assets'),
    'menu_name' => 'springboard_admin_menu',
    'expanded' => 1,
    'customized' => 1,
    'weight' => -40,
    '_children' => array(),
  );

  if(module_exists('email_wrappers')) {
    // Assets > Email Templates.
    $items['admin/springboard/asset-library']['_children']['admin/springboard/asset-library/email_wrapper'] = array(
      'link_path' => 'admin/springboard/asset-library/email_wrapper',
      'link_title' => t('Email Templates'),
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 1,
      'customized' => 1,
      'weight' => -100,
    );
  }

  if(module_exists('page_wrappers')) {
    // Assets > Page Wrappers.
    $items['admin/springboard/asset-library']['_children']['admin/springboard/asset-library/page_wrapper'] = array(
      'link_path' => 'admin/springboard/asset-library/page_wrapper',
      'link_title' => t('Page Wrappers'),
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 1,
      'customized' => 1,
      'weight' => -90,
    );
  }

  // Top Level: Marketing
  $items['admin/springboard/marketing-analytics'] = array(
    'link_path' => 'admin/springboard/marketing-analytics',
    'link_title' => t('Marketing'),
    'menu_name' => 'springboard_admin_menu',
    'expanded' => 1,
    'customized' => 1,
    'weight' => -50,
    '_children' => array(),
  );

  if(module_exists('webform_ab')) {
    // Marketing > Multivariate Testing.
    $items['admin/springboard/marketing-analytics']['_children']['admin/content/webform_ab'] = array(
      'link_path' => 'admin/content/webform_ab',
      'link_title' => t('Multivariate Tests'),
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 1,
      'customized' => 1,
      'weight' => -90,
    );
  }

  // Top Level: Settings.
  $items['admin/springboard/settings'] = array(
    'link_path' => 'admin/springboard/settings/config',
    'link_title' => t('Options'),
    'menu_name' => 'springboard_admin_menu',
    'expanded' => 1,
    'customized' => 1,
    'weight' => 6,
    '_children' => array(),
  );

  // This is used as a parent for items on the links list here: /springboard/settings/config 
  $items['admin/springboard/settings']['_children']['admin/springboard/settings/config'] = array(
    'disabled' => TRUE,
    'link_path' => 'admin/springboard/settings/config',
    'link_title' => 'Settings',
    'menu_name' => 'springboard_admin_menu',
    'expanded' => 0,
    'customized' => 1,
    'weight' => 2,
    '_children' => array(),
  );

  if (is_array($user->roles) && in_array('Administrator', array_values($user->roles))) {
    $items['admin/springboard/settings']['_children']['admin/springboard/settings/config']['_children']['admin/springboard/settings/springboard'] = array(
      'link_path' => 'admin/springboard/settings/springboard',
      'link_title' => 'Admin Settings',
      'attributes' => array('sb_link_group' => t('Springboard Settings')),
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 0,
      'customized' => 1,
    );
  }

  if (module_exists('salesforce_mapping')) {
    // Settings > Settings > Add salesforce mapping.
    if (user_access('map salesforce objects')) {
      $items['admin/springboard/settings']['_children']['admin/springboard/settings/config']['_children']['admin/structure/salesforce/mappings/add'] = array(
        'link_path' => 'admin/structure/salesforce/mappings/add',
        'link_title' => 'Add Salesforce Mapping',
        'attributes' => array('sb_link_group' => t('Salesforce')),
        'menu_name' => 'springboard_admin_menu',
        'expanded' => 0,
        'customized' => 1,
      );
      // Settings > Settings > Import salesforce mapping.
      $items['admin/springboard/settings']['_children']['admin/springboard/settings/config']['_children']['admin/structure/salesforce/mappings/import'] = array(
        'link_path' => 'admin/structure/salesforce/mappings/import',
        'link_title' => 'Import Salesforce Mapping',
        'attributes' => array('sb_link_group' => t('Salesforce')),
        'menu_name' => 'springboard_admin_menu',
        'expanded' => 0,
        'customized' => 1,
      );
      // Settings > Settings > Fieldmaps.
      $items['admin/springboard/settings']['_children']['admin/springboard/settings/config']['_children']['admin/structure/salesforce/mappings'] = array(
        'link_path' => 'admin/structure/salesforce/mappings',
        'link_title' => 'Fieldmaps',
        'attributes' => array('sb_link_group' => t('Salesforce')),
        'menu_name' => 'springboard_admin_menu',
        'expanded' => 0,
        'customized' => 1,
      );
    }
  }

  if(module_exists('webform_ab') && user_access('administer webform_ab')) {
    $items['admin/springboard/settings']['_children']['admin/springboard/settings/config']['_children']['admin/config/content/webform_ab'] = array(
      'link_path' => 'admin/config/content/webform_ab',
      'link_title' => 'Multivariate Testing Settings',
      'attributes' => array('sb_link_group' => t('Springboard Settings')),
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 0,
      'customized' => 1,
    );
  }

  $items['admin/springboard/settings']['_children']['admin/springboard/settings/config']['_children']['admin/springboard/settings/administrators'] = array(
    'link_path' => 'admin/springboard/settings/administrators',
    'link_title' => 'Springboard Administrators',
    'attributes' => array('sb_link_group' => t('Springboard Settings')),
    'menu_name' => 'springboard_admin_menu',
    'expanded' => 0,
    'customized' => 1,
  );

  if (module_exists('redirect') && user_access('administer redirects')) {
    // Settings > Settings > URL Redirects
    $items['admin/springboard/settings']['_children']['admin/springboard/settings/config']['_children']['admin/config/search/redirect'] = array(
      'link_path' => 'admin/config/search/redirect',
      'link_title' => 'URL Redirects',
      'attributes' => array('sb_link_group' => t('Springboard Settings')),
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 0,
      'customized' => 1,
    );
  }

  if (user_access('Administer users')) {
    // Settings > Settings > User Fields
    $items['admin/springboard/settings']['_children']['admin/springboard/settings/config']['_children']['admin/config/people/accounts/fields'] = array(
      'link_path' => 'admin/config/people/accounts/fields',
      'link_title' => 'User Fields',
      'attributes' => array('sb_link_group' => t('Springboard Settings')),
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 0,
      'customized' => 1,
    );
    $items['admin/springboard/settings']['_children']['admin/springboard/settings/config']['_children']['admin/config/people/accounts/display'] = array(
      'link_path' => 'admin/config/people/accounts/display',
      'link_title' => 'User Profile Fields',
      'attributes' => array('sb_link_group' => t('Springboard Settings')),
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 0,
      'customized' => 1,
    );
  }

  if (module_exists('springboard_p2p')) {
    // Settings > Settings > Rules
    if (user_access('administer springboard p2p rules')) {
      $items['admin/springboard/settings']['_children']['admin/springboard/settings/config']['_children']['admin/springboard/p2p/rules'] = array(
        'link_path' => 'admin/springboard/p2p/rules',
        'link_title' => 'Rules',
        'attributes' => array('sb_link_group' => t('Peer to Peer')),
        'menu_name' => 'springboard_admin_menu',
        'expanded' => 0,
        'customized' => 1,
      );
    }
    // Settings > Settings > Settings
    if (user_access('administer springboard p2p')) {
      $items['admin/springboard/settings']['_children']['admin/springboard/settings/config']['_children']['admin/springboard/p2p/settings'] = array(
        'link_path' => 'admin/springboard/p2p/settings',
        'link_title' => 'Settings',
        'attributes' => array('sb_link_group' => t('Peer to Peer')),
        'menu_name' => 'springboard_admin_menu',
        'expanded' => 0,
        'customized' => 1,
      );
    }
    // Settings > Settings > Starter Content
    if (user_access('create p2p starter content')) {
      $items['admin/springboard/settings']['_children']['admin/springboard/settings/config']['_children']['admin/springboard/p2p/starter'] = array(
        'link_path' => 'admin/springboard/p2p/starter',
        'link_title' => 'Starter Content',
        'attributes' => array('sb_link_group' => t('Peer to Peer')),
        'menu_name' => 'springboard_admin_menu',
        'expanded' => 0,
        'customized' => 1,
      );
    }
  }

  if (module_exists('springboard_measurement_protocol') && user_access('administer springboard measurement_protocol')) {
    // Settings > Settings > Configuration
    $items['admin/springboard/settings']['_children']['admin/springboard/settings/config']['_children']['admin/springboard/ga'] = array(
      'link_path' => 'admin/springboard/ga',
      'link_title' => 'Configuration',
      'attributes' => array('sb_link_group' => t('Analytics')),
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 0,
      'customized' => 1,
    );
    // Settings > Settings > Integration
    $items['admin/springboard/settings']['_children']['admin/springboard/settings/config']['_children']['admin/springboard/options/ga'] = array(
      'link_path' => 'admin/springboard/options/ga',
      'link_title' => 'Integration',
      'attributes' => array('sb_link_group' => t('Analytics')),
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 0,
      'customized' => 1,
    );
  }

  drupal_alter('springboard_admin_admin_menu_items', $items);
  return $items;
}

/**
 * Recreate the Springboard admin menu.
 *
 * @param bool $show_message
 *   Boolean to control the display of the message, defaults to TRUE.
 */
function springboard_admin_recreate_menu($show_message = TRUE) {
  $sb_menu = springboard_admin_admin_menu();
  if (menu_load($sb_menu['menu_name'])) {
    menu_delete($sb_menu);
  }
  springboard_admin_create_menu(TRUE);

  if ($show_message) {
    drupal_set_message('The Springboard Admin Menu has been rebuilt.');
  }
}

/**
 * Sets a session flag to recreate the SB menu on exit.
 *
 * @see springboard_admin_exit().
 */
function springboard_admin_recreate_menu_on_exit() {
  $_SESSION['springboard_admin_recreate_menu_on_exit'] = TRUE;
}

/**
 * Helper function, creates the Springboard Admin Menu.
 */
function springboard_admin_create_menu($rebuild = FALSE) {
  // Define and save the Springboard Administration menu.
  $sb_menu = springboard_admin_admin_menu();
  menu_save($sb_menu);
  // Define and add default menu items to the Springboard Administration menu.
  $sb_menu_items = springboard_admin_admin_menu_items();
  /*
   * Iterate through each item. Save the parent and then the children using the
   * parent's newly assign mlid as the child's plid. If the menu ever advances
   * to more than two levels, we will need to rewrite this to be recursive.
   */
  $mlids = array();
  foreach ($sb_menu_items as $key => $item) {
    springboard_admin_create_menu_item($item, $mlids);
  }
  // Set menu links as customized so they don't get wiped out in the
  // router check.
  $result = db_update('menu_links')
  ->fields(array(
    'customized' => 1,
  ))
  ->condition('mlid', $mlids, 'IN')
  ->execute();
  if(!$rebuild) {
    drupal_set_message('The Springboard Admin menu has been created. If you need to rebuild the menu for any reason, visit the <a href="/admin/springboard/settings/springboard">Springboard Configuration</a> page.');
  }
}

function springboard_admin_create_menu_item($item, &$mlids, $plid = 0, $parent = array()) {
  $children = isset($item['_children']) ? $item['_children'] : array();
  // Set the item' parent ID if applicable
  if ($plid > 0) {
    $item['plid'] = $plid;
  }

  // Set a default module value.
  if (!isset($item['module'])) {
    $item['module'] = 'menu';
  }

  // Save a the item.
  $mlid = menu_link_save($item, array(), array($plid => $parent));
  $mlids[] = $mlid;
  // If save was successful, loop through child items.
  if ($mlid) {
    $mlids[] = $mlid;
    if (!empty($children)) {
      foreach ($children as $key => $child) {
        springboard_admin_create_menu_item($child, $mlids, $mlid, $item);
      }
    }
  }
  else {
    drupal_set_message(t('springboard admin menu item @item and its children were not created due to an error', array('@item' => check_plain($item['title']))), 'warning');
  }
}
