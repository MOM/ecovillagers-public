<?php

/**
 * Implements hook_drush_command().
 */
function springboard_export_drush_command() {
  $drupal_dependencies = array(
    'views',
    'commerce',
    'commerce_order',
    'webform',
    'fundraiser_webform',
    'fundraiser_commerce',
    'fundraiser',
    'springboard_views',
  );
  return array(
    'springboard-file-export' => array(
      'aliases' => array('sb-fe'),
      'description' => t('Exports a views_data_export-based file from the Drupal DB.'),
      'callback' => 'springboard_export_drush_export_views_data_export',
      'options' => array(
        'json' => t('JSON any key/value search filters, sort (the field on which to sort), and order (asc or desc).'),
      ),
      'drupal dependencies' => $drupal_dependencies,
      'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    ),
  );
}

/**
 * Callback for drush sb-export-donations-csv (alias: sb-edc)
 */
function springboard_export_drush_export_views_data_export($drush_options = NULL) {
  // Handle output buffering:
  ob_start();

  // Grant full access so the view can be executed:
  $start = time();
  global $user;
  drupal_save_session(FALSE);
  $user = user_load(1);

  // If params are not provided, pull JSON data from drush:
  if ($drush_options == NULL) {
    $drush_options = json_decode(drush_get_option('json'), true);
  }

  $debug_mode = FALSE;

  if ($debug_mode) {
    drush_print('Drush options:');
  }
  if (!is_array($drush_options) || empty($drush_options)) {
    if ($debug_mode) {
      drush_print('No Drush options available; aborting.');
    }
    return;
  }
  if ($debug_mode) {
    drush_print_r($drush_options);
  }



  $max_allowed_pages = 10000000;
  $max_allowed_results = 0; // 0 means unlimited.
  if ($debug_mode) {
    drush_print("BEGIN WRITING EXPORT CONTENT:");
  }
  $output_path = variable_get('springboard_dw_reports_export_path', '/tmp'); // Default output path if it is not overwritten.
  $filename = $output_path . '/' . date('Y-m-d--H-i-s', $start) . '-' . $drush_options['view_name'] . '--' . $drush_options['view_display'] . '.csv';
  $output_file_handle = fopen($filename, 'w');
  if ($debug_mode) {
    drush_print("Output file: $filename");
  }

  $current_page = 0;
  $total_results_exported = 0;
  $segment_size = 100; // The views_data_export default is 100.
  $sort_data = array();
  while ($current_page < $max_allowed_pages) {
    //drush_print('Current page = ' . $current_page); 
    $view = views_get_view($drush_options['view_name']);
    $view->set_display($drush_options['view_display']);
    $view->init_handlers();

    // Explicitly identify this as a custom export:
    $view->is_sb_export = TRUE;

    // After the view is loaded for the first time, gather info that will be needed for each page:
    if ($current_page == 0) {
      $segment_size = $view->display_handler->get_option('segment_size');
      // Let the view_data_export's display limit total export size based on the pagination setting:
      $pager_data = $view->display_handler->get_option('pager');
      if (isset($pager_data['options']['items_per_page']) && is_numeric($pager_data['options']['items_per_page'])) {
        $max_allowed_results = $pager_data['options']['items_per_page'];
      }
    }
    
    // Do not use batch mode if it is enabled:
    $view->preview = TRUE;
    $view->display_handler->set_option('use_batch', 'no_batch');

    // Only display the header row on the first page:
    $style_options = $view->display_handler->get_option('style_options');
    if ($current_page != 0 && $style_options['header'] == 1) {
      $style_options['header'] = 0;
      $view->display_handler->set_option('style_options', $style_options);
    }

    // Apply filtering:
    if (isset($drush_options['exposed_input'])) {
      $exposed_input = (array) $drush_options['exposed_input'];
      unset($exposed_input['attach']);
      $view->set_exposed_input($exposed_input);
    }

    // Apply sorting via query alter, using the query orderby array from the parent display:
    /* if (isset($drush_options['query_orderby']) && is_array($drush_options['query_orderby'])) {
      $view->sb_export_query_orderby = $drush_options['query_orderby'];
    } */

    // Limit the final page of results if the export size is limited via its display's pager (0 means export it all):
    if ($max_allowed_results != 0 && $max_allowed_results - $total_results_exported < $segment_size) {
      $segment_size = $max_allowed_results - $total_results_exported;
      $final_page_reached = TRUE;
    }
    $view->set_items_per_page($segment_size); 
    $view->set_offset($current_page * $segment_size);


    $view->pre_execute(); // TODO - need to account for view args just in case


    $rendered_output = $view->display_handler->preview();
    if ($debug_mode) {
      drush_print($rendered_output);
    }
    fputs($output_file_handle, $view->display_handler->preview());
  
    // The end of this export has been reached when no results are returned for the current page
    // or if a non-0 number is specificed for the View's pagination field:
    if (isset($final_page_reached) || !isset($view->result) || !is_array($view->result) || count($view->result) == 0) {
      $view->destroy();
      drupal_static_reset();
      break;
    }

    $segment_size = $view->display_handler->get_option('segment_size');

    $total_results_exported += count($view->result);
    $current_page++;

    // Free up memory:
    $view->destroy();
    drupal_static_reset();
  } // End file generation loop.

  fclose($output_file_handle);

  // Send the file to Amazon S3:
  
  $s3_pre_signed_urls = _springboard_export_drush_export_aws_files_upload(array($filename));

  if ($debug_mode) {
    drush_print('Amazon S3 pre-signed URLs:');
    drush_print_r($s3_pre_signed_urls);
  }

  if ($debug_mode) {
    drush_print('Export attempt complete.');
  }
  watchdog('springboard_export', 'Export complete: ' . $filename);

  $export_summary = array();
/*  $export_summary = array(
    'total_results_exported' => $total_results,
    'view_id' => $view_id,
    'view_display' => $export_display_id,
    'start' => date('Y-m-d - H:i:s', $start),
    'end' => date('Y-m-d - H:i:s'),
    'duration' => $duration,
    'internal_file_paths' => $file_paths,
    'export_file_count' => count($s3_pre_signed_urls),
    'export_file_paths' => $s3_pre_signed_urls,
  ); */
  $export_summary['internal_tmp_file_path'] = $filename;
  $export_summary['external_export_file_urls'] = $s3_pre_signed_urls;


  watchdog('springboard_export', 'CSV export result: ' . print_r($export_summary, 1));

  if ($debug_mode) {
    drush_print('Export summary:');
    drush_print_r($export_summary);
  }


  // Return the job summary.
  $drush_response = json_encode($export_summary);
  drush_print($drush_response);

  // Handle output buffering:
  ob_end_flush();

  return $export_summary;
}


/**
 * Send one or more files to AWS.
 */
function _springboard_export_drush_export_aws_files_upload($file_paths) {
  // Load up the Composer dependencies.
  require_once "sites/all/libraries/springboard_composer/vendor/autoload.php";

  // Enable Garbage Collection.
  gc_enable();

  // Setup the S3 config.
  $s3_config = array(
    'region'      => variable_get
    ('springboard_dw_reports_export_S3_region', NULL),
    'version'     => '2006-03-01',
    'credentials' => array(
      'key'    => variable_get
      ('springboard_dw_reports_export_S3_key', NULL),
      'secret' => variable_get
      ('springboard_dw_reports_export_S3_secret', NULL),
    )
  );

  // Create an S3 client instance.
  $s3_client = new \Aws\S3\S3Client($s3_config);

  // Register the stream wrapper.
  $s3_client->registerStreamWrapper();

  // Create new array shells to track the S3 uploads.
  $s3_uploaded_files = array();
  $s3_failed_files = array();
  $s3_pre_signed_urls = array();

  // Upload each file to S3 and return the pre-signed S3 URL.
  foreach ($file_paths as $key => $path) {
    $local_file_to_upload = $path;
    $new_s3_file_key = end(explode('/', $path));

    // Try the S3 upload, if it fails track the failure.
    try {
      // Instantiate a multi-part uploader.
      $uploader = new \Aws\S3\MultipartUploader($s3_client, $local_file_to_upload, [
        'bucket' => variable_get('springboard_dw_reports_export_S3_bucket', NULL),
        'key'    => $new_s3_file_key,
      ]);

      // Do the S3 upload.
      $result = $uploader->upload();

      // Track the upload success.
      $s3_uploaded_files[] = $path;

      // Add the GetObject client method so we can retrieve a pre-signed request.
      $cmd = $s3_client->getCommand('GetObject', [
        'Bucket' => variable_get
        ('springboard_dw_reports_export_S3_bucket', NULL),
        'Key'    => $new_s3_file_key,
      ]);

      // Create the pre-signed request and get the url.
      $request = $s3_client->createPresignedRequest($cmd, '+180 minutes');
      $presignedUrl = (string) $request->getUri();

      // Add the pre-signed url to the array to add back to the export summary.
      $s3_pre_signed_urls[] = $presignedUrl;

    } catch (Aws\Exception\MultipartUploadException $e) {
      // Track the upload failure.
      $s3_failed_files[] = $path;

      // Build out the error details to log to watchdog.
      $error_details = array(
        'exception' => $e->getMessage(),
        'file'      => $local_file_to_upload,
      );

      // Construct the watchdog string.
      $watchdog_string = "<pre>Springboard reports S3 upload error: \n" . print_r($error_details, TRUE) . "</pre>";

      watchdog_exception('Drupal reports export', $watchdog_string);
    }
  }

  // Merge the arrays of uploaded and failed because we will want to remove
  // the local CSV export for both since it will change the next attempt.
  $all_files = array_merge($s3_uploaded_files, $s3_failed_files);

  // Remove the local file.
  foreach ($all_files as $local_file) {
    unset($local_file);
  }

  return $s3_pre_signed_urls;
}
