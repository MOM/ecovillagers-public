<?php

/**
 * @file
 * Administration page callbacks for the salesforce queue module.
 */

/**
 * Page callback for the admin form.
 */
function salesforce_queue_admin_page() {
  $build = array();
  $build['content'] = array(
    'page_description' => array(
      '#id' => 'salesforce-queue-admin-helptext-page',
      '#type' => 'markup',
      '#markup' => '<p>' . t('Configure settings for Salesforce Queue.') . '</p>',
      '#prefix' => '<div class="salesforce-queue-admin-helptext">',
      '#suffix' => '</div>',
    ),
    'salesforce_queue_admin_form' => drupal_get_form('salesforce_queue_admin_form'),
  );
  return $build;
}

/**
 * Configuration form for handling queues.
 */
function salesforce_queue_admin_form($form, &$form_state) {
  $form = array();

  $sfapi = salesforce_get_api();
  if (!$sfapi->isAuthorized()) {
    return array(
      'no_sfapi' => array(
        '#markup' => '<p>' . t('Cannot connect to Salesforce, preventing the ability to configure the Salesforce queue.  !ConfigureSalesforce',
            array('!ConfigureSalesforce' => l(t('Configure Salesforce'), 'admin/config/salesforce/authorize'))) . '</p>',
        '#prefix' => '<div class="salesforce-map-error salesforce-map-error-salesforce">',
        '#suffix' => '</div>',
      ),
    );
  }

  $sf_objects = _sfq_salesforce_object_list($sfapi);

  // Variable salesforce_queue_max_items.
  $form['max_items'] = array(
    '#id' => 'salesforce-queue-max-items',
    '#title' => t('Maximum Items to Process'),
    '#description' => t('The maximum number of items that can be processed in a
      single run.  This is the maximum number of items your server can hold in
      memory.'),
    '#type' => 'textfield',
    '#size' => 6,
    '#default_value' => _sfq_get_value('max_items', $form_state),
  );

  // Variable salesforce_queue_max_retries.
  $form['max_retries'] = array(
    '#id' => 'salesforce-queue-max-retries',
    '#title' => t('Maximum Retries of a Queue Item'),
    '#description' => t('The maximum number of times a queue item will be processed before it is placed in the "fail" queue.'),
    '#type' => 'textfield',
    '#size' => 6,
    '#default_value' => _sfq_get_value('max_retries', $form_state),
  );

  // Variable salesforce_queue_lease_time.
  $form['lease_time'] = array(
    '#id' => 'salesforce-queue-lease-time',
    '#title' => t('Queue Lease Limit'),
    '#description' => t('The maximum length of time a single process can lock
      the queue.  A processor will only process items while the queue is locked
      and will cease processing items once the lease is expired.  This value
      should be set for the maximum amount of time a queue processor can be
      allowed to run. The value is in minutes.'),
    '#type' => 'textfield',
    '#size' => 6,
    // Convert value from seconds to minutes.
    '#default_value' => (_sfq_get_value('lease_time', $form_state) / 60),
  );

  // Variable salesforce_queue_cron_frequency.
  $form['cron_frequency'] = array(
    '#id' => 'salesforce-queue-cron-frequency',
    '#title' => t('Minimum Cron Frequency'),
    '#description' => t('The minimum amount of time that can pass before the
      queue processor can run again through cron and on-demand.  The value is in
      minutes.'),
    '#type' => 'textfield',
    '#size' => 6,
    // Convert value from seconds to minutes.
    '#default_value' => (_sfq_get_value('cron_frequency', $form_state) / 60),
  );

  // Variable salesforce_queue_cron_enabled
  $form['cron_enabled'] = array(
    '#id' => 'salesforce-queue-cron-standalone',
    '#title' => t('Run queue processor during core cron'),
    '#description' => t('Whether or not the queue processor should be executed
      during core cron runs.  The queue processor may need to be decoupled from
      core cron if the processing of queue items is too processor intensive
      causing time-outs.  The queue processor can be run on-demand by hitting
      "salesforce-queue/process" or "salesforce-queue/process/foobar" where
      "foobar" is the name of the specific queue to process.'),
    '#type' => 'checkbox',
    '#default_value' => _sfq_get_value('cron_enabled', $form_state),
  );

  // Variable salesforce_queue_tracked_queues.
  // Which queues does the multi-queue processor (e.g. 'all') track?
  // NOTE: Not displaying this option because it may be too confusing to a
  // non-developer and something we don't even want to offer to site builders.
  // I'm throwing the code out there if for whatever reason a specific instance
  // needs more than 'new', 'retry' and 'fail' queues to meet their needs and we
  // have a site builder who needs to manage those additional queues.
  $display_tracked_queue_config = variable_get('salesforce_queue_tracked_queues_show_config', FALSE);
  if ($display_tracked_queue_config) {
    $form['tracked_queues'] = array(
      '#id' => 'salesforce-queue-tracked-queues',
      '#title' => t('Tracked Queues of the Multi-Queue Processor'),
      '#description' => t('Pick which queues should be tracked when working with
        the multi-queue processor.'),
      '#type' => 'checkboxes',
      '#default_value' => _sfq_get_value('tracked_queues', $form_state),
      '#options' => salesforce_queue_get_queue_names(),
      '#required' => TRUE,
    );
  }

  // Variable salesforce_queue_object_order.
  $form['object_order_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Queue Sort Order for Salesforce Objects'),
    '#description' => t('Sort the Salesforce objects below by the least
      dependant objects first, and the objects with the most dependencies last.
      Ensure objects are below the objects they directly depend upon.'),
    '#collapsible' => FALSE,
  );

  $object_order = _sfq_get_value('object_order', $form_state);

  // Get the labels from the Salesforce object list, then append the remaining
  // Salesforce objects to the end of the list.
  $objects = array();
  foreach ($object_order as $object) {
    $objects[$object] = $sf_objects[$object];
    unset($sf_objects[$object]);
  }
  $objects = $objects + $sf_objects;

  // Build up the object ordering form. The magic for making it a reorder table
  // is in the theme hook for this form.
  $object_count = count($objects);
  $form['object_order_fieldset']['object_order'] = array(
    '#tree' => TRUE,
  );
  foreach ($objects as $object => $object_label) {
    $form['object_order_fieldset']['object_order'][$object] = array(
      'label' => array(
        '#markup' => $object_label,
      ),
      'value' => array(
        '#type' => 'hidden',
        '#value' => $object,
      ),
      'weight' => array(
        '#type' => 'weight',
        '#default_value' => 0,
        '#delta' => $object_count,
      ),
    );
  }

  // Save.
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );
  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel',
  );
  return $form;
}

/**
 * Returns HTML for the salesforce queue configuration form.
 *
 * This is really just so we can render the draggable table.  Such a complicated
 * thing that beast is.
 */
function theme_salesforce_queue_admin_form($variables) {
  $form = $variables['form'];

  // Can't connect to Salesforce, so skip the custom theming of the rest
  // of the form.
  if (isset($form['no_sfapi'])) {
    return drupal_render_children($form);
  }

  $rows = array();
  foreach (element_children($form['object_order_fieldset']['object_order']) as $object) {
    $form['object_order_fieldset']['object_order'][$object]['weight']['#attributes']['class'] = array('salesforce-queue-object-order-weight');
    $rows[] = array(
      'data' => array(
        drupal_render($form['object_order_fieldset']['object_order'][$object]['label']),
        drupal_render($form['object_order_fieldset']['object_order'][$object]['value']),
        drupal_render($form['object_order_fieldset']['object_order'][$object]['weight']),
      ),
      'class' => array('draggable'),
    );
  }
  $header = array();
  $table_config = array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => 'salesforce-queue-object-order'),
  );
  $table = theme('table', $table_config);
  $form['object_order_fieldset']['object_order'] = array('#markup' => $table);
  $output = drupal_render_children($form);

  drupal_add_tabledrag('salesforce-queue-object-order', 'order', 'sibling', 'salesforce-queue-object-order-weight');

  return $output;
}

/**
 * Validation callback for configuration form.
 */
function salesforce_queue_admin_form_validate($form, &$form_state) {
  foreach ($form_state['input'] as $var => $value) {
    switch ($var) {
      case 'lease_time':
      case 'cron_frequency':
      case 'max_items':
      case 'max_retries':
        $title = $form[$var]['#title'];
        if (!is_numeric($value)) {
          form_set_error($var, 'Value for "' . $title . '" must be numeric.');
        }
        if ($value < 0) {
          form_set_error($var, 'Value for "' . $title . '" must be a positive number.');
        }
        break;
    }
  }
}

/**
 * Submit callback for the configuration form.
 */
function salesforce_queue_admin_form_submit($form, &$form_state) {
  if ($form_state['input']['op'] == 'Cancel') {
    drupal_set_message(t('The form has been reset to its original values.'));
    return;
  }
  elseif ($form_state['input']['op'] != 'Save') {
    drupal_set_message(t('The form was submitted unexpectedly.  No action was taken, nothing was saved.'), 'error');
    return;
  }

  foreach ($form_state['input'] as $var => $value) {
    switch ($var) {
      case 'cron_enabled':
      case 'cron_frequency':
      case 'lease_time':
      case 'max_items':
      case 'max_retries':
      case 'object_order':
      case 'tracked_queues':
        $converted_value = _sfq_get_value($var, $form_state);
        variable_set('salesforce_queue_' . $var, $converted_value);
        break;
    }
  }
  drupal_set_message(t('Your settings have been saved.'));
}

/**
 * Helper function to find the value for the given field for the current state.
 */
function _sfq_get_value($field, $form_state) {
  $value = NULL;
  if ($field == 'cron_enabled' && !empty($form_state['input'])) {
    $value = isset($form_state['input']['cron_enabled']) && $form_state['input']['cron_enabled'] ? 1 : 0;
  }
  elseif (isset($form_state['input'][$field])) {
    // Convert the user contributed value into an expected format.
    $value = $form_state['input'][$field];
    switch ($field) {
      case 'cron_frequency':
      case 'lease_time':
        // Convert the user input from minutes to seconds.
        $value = ($value * 60);
        break;

      case 'tracked_queues':
        // Extract null items, or else it will confuse future uses of this var.
        foreach ($value as $key => $queue_name) {
          if (is_null($queue_name)) {
            unset($value[$key]);
          }
        }
        break;

      case 'object_order':
        // If they used drag and drop, it is already in the correct order.
        // However, if they used the weight drop down boxes, then we need to
        // sort them ourselves. We could use the handy little drupal_sort_weight
        // uasort callback to help us out with this.  _Unfortunately_, it is not
        // smart enough to not mess up the order of everything that is set to
        // the same value (which is a huge mess when it is '0' which would
        // happen alot since it is the default value).  We're going to have to
        // sort this ourselves so we make sure we keep everything that is set to
        // the same weight the same order it was to the user when they hit save.
        $weights = array();
        foreach ($value as $object => $object_info) {
          $weights[$object_info['weight']][$object] = $object_info;
        }
        ksort($weights);

        // Now just make a simple array to save because everything that uses
        // this var assumes it is a simple array.
        $value = array();
        foreach ($weights as $objects) {
          foreach ($objects as $object => $object_info) {
            $value[] = $object;
          }
        }
        break;
    }
  }
  else {
    // Use current configured value, or default value.
    switch ($field) {
      case 'cron_enabled':
        $value = variable_get('salesforce_queue_cron_enabled', 1);
        break;

      case 'cron_frequency':
        $value = variable_get('salesforce_queue_cron_frequency', SALESFORCE_QUEUE_CRON_FREQUENCY_DEFAULT);
        break;

      case 'lease_time':
        $value = variable_get('salesforce_queue_lease_time', SALESFORCE_QUEUE_LEASE_TIME_DEFAULT);
        break;

      case 'max_items':
        $value = variable_get('salesforce_queue_max_items', SALESFORCE_QUEUE_MAX_ITEMS_DEFAULT);
        break;

      case 'max_retries':
        $value = variable_get('salesforce_queue_max_retries', SALESFORCE_QUEUE_MAX_RETRIES_DEFAULT);
        break;

      case 'object_order':
        $default_order = array('Account', 'Contact', 'Opportunity');
        $value = variable_get('salesforce_queue_object_order', $default_order);
        break;

      case 'tracked_queues':
        $default_queues = array(
          'new' => 'new',
          'retry' => 'retry',
        );
        $value = variable_get('salesforce_queue_tracked_queues', $default_queues);
        break;

      default:
        $value = variable_get('salesforce_queue_' . $field, NULL);
    }
  }
  return $value;
}

/**
 * Gather a simple list of Salesforce objects.
 *
 * NOTE: This is a straight-up copy from salesforce_genmap.  I wonder if there
 *       is any way this could be made in some sharable format?
 *
 * @param Salesforce $sfapi
 *   A Salesforce API object
 *
 * @return array
 *   Array of Salesforce objects keyed by the object's name and the label as the
 *   value
 */
function _sfq_salesforce_object_list(Salesforce $sfapi) {
  // Salesforce module v4 filters down to updatable and triggerable so it is
  // easier to visually consume the list.
  $objects_info = $sfapi->objects(array('updateable' => TRUE, 'triggerable' => TRUE));

  $objects_list = array();
  $dupes = array();
  foreach ($objects_info as $object) {
    // Some objects have the same label, which just makes things confusing
    // I could make only subsequent duplicates unique, but I figure that users
    // may wonder what the first instance is referencing.
    if (in_array($object['label'], $objects_list)) {
      $dupes[] = $object['label'];
    }

    $objects_list[$object['name']] = $object['label'];
  }

  // Now make duplicate labels be unique.
  if (!empty($dupes)) {
    foreach ($objects_list as $object_name => $object_label) {
      if (in_array($object_label, $dupes)) {
        $objects_list[$object_name] = $object_label . ' (' . $object_name . ')';
      }
    }
  }

  return $objects_list;
}
