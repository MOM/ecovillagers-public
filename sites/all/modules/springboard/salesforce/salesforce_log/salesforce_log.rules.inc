<?php

/**
 * @file
 * Provides rules integration for Salesforce watchdog events.
 */

/**
 * Implements hook_rules_event_info().
 */
function salesforce_log_rules_event_info() {
  $events = array();
  $module_info = salesforce_log_info();
  foreach ($module_info['watchdog'] as $id => $label) {
    $events['salesforce_log-' . $id] = array(
      'group' => t('Salesforce Log'),
      'module' => 'salesforce_log',
      'label' => $label,
      'variables' => array(
        'watchdog_ip' => array(
          'type' => 'text',
          'label' => t('Watchdog log ip'),
          'description' => t('The IP address where the request for the page came from.'),
        ),
        'watchdog_link' => array(
          'type' => 'text',
          'label' => t('Watchdog log link'),
          'description' => t('An informational link provided by the module calling watchdog.'),
        ),
        'watchdog_message' => array(
          'type' => 'text',
          'label' => t('Watchdog log message'),
          'description' => t('The text of the message to be logged.'),
        ),
        'watchdog_referer' => array(
          'type' => 'text',
          'label' => t('Watchdog log referer'),
          'description' => t('The page that referred the user to the page where the event occurred.'),
        ),
        'watchdog_request_uri' => array(
          'type' => 'text',
          'label' => t('Watchdog log request URI'),
          'description' => t('The request URI for the page the event happened in.'),
        ),
        'watchdog_severity' => array(
          'type' => 'integer',
          'label' => t('Watchdog log severity'),
          'description' => t('The degree of severity of the event.'),
        ),
        'watchdog_timestamp' => array(
          'type' => 'integer',
          'label' => t('Watchdog log timestamp'),
          'description' => t('The UNIX timetamp of the date/time the event occurred.'),
        ),
        'watchdog_uid' => array(
          'type' => 'integer',
          'label' => t('The UID of the logged in user when watchdog was called.'),
        ),
        'watchdog_user' => array(
          'type' => 'user',
          'label' => t('Logged in user when watchdog was called.'),
        ),
      ),
    );
  }
  return $events;
}
