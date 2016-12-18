<?php

/**
 * @file
 * Definition of SalesforceLogHandlerFieldDrupalId.
 */

/**
 * Filter by Drupal Id.
 *
 * @ingroup views_filter_handlers
 */
class SalesforceLogHandlerFieldDrupalId extends views_handler_field_numeric {

  /**
   * Render link to Drupal item.
   */
  public function render($values) {
    $value = $output = $values->{$this->field_alias};
    // If the module field is present link this id to the drupal object.
    $module_field_alias = $this->view->base_table . '_module';
    if (!empty($values->{$module_field_alias})) {
      switch ($values->{$module_field_alias}) {
        case 'webform':
          // Need the nid to link to the webform submission.
          $nid = db_query('SELECT nid FROM webform_submissions WHERE sid = :sid', array(':sid' => $value))->fetchField();
          if ($nid) {
            $output = l($value, 'node/' . $nid . '/submission/' . $value);
          }
          break;

        case 'user':
          $output = l($value, 'user/' . $value);
          break;

        case 'salesforce_donation':
        case 'fundraiser_sustainers_series':
          $output = l($value, 'springboard/donations/' . $value);
          break;
      }
    }
    return $output;
  }

}
