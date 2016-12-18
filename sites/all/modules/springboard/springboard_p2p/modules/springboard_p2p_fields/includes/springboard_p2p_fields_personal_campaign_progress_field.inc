<?php
/**
 * @file
 * Filed api implementation code for the Personal Campaign progress field.
 */

class SpringboardP2pPersonalCampaignProgressField {

  /**
   * Validate.
   */
  public function validate($field, $langcode, $items, &$errors) {

  }

  /**
   * Field is empty.
   */
  public function isEmpty($item) {
    return FALSE;
  }

  /**
   * Presave.
   */
  public function presave(&$items) {

  }

  /**
   * Widget form.
   */
  public function widgetForm($instance, $items, $delta, $element) {
    $widget = $element;

    switch ($instance['widget']['type']) {
      case 'springboard_p2p_fields_personal_campaign_progress_widget':

        // Make this a fieldset with the three text fields.
        $widget += array(
          '#type' => 'fieldset',
          '#title' => t('Campaign progress'),
          // #delta is set so that the validation function will be able
          // to access external value information which otherwise would be
          // unavailable.
          '#delta' => $delta,
        );

        $widget['submissions'] = array(
          '#type' => 'textfield',
          // '#disabled' => TRUE,
          '#default_value' => isset($items[$delta]['submissions']) ? $items[$delta]['submissions'] : 0,
          '#title' => t('Submissions'),
        );

        $widget['amount'] = array(
          '#type' => 'textfield',
          // '#disabled' => TRUE,
          '#default_value' => isset($items[$delta]['amount']) ? $items[$delta]['amount'] : 0,
          '#title' => t('Amount'),
        );

        break;
    }

    $element = $widget;
    return $element;
  }

  /**
   * Formatter view.
   */
  public function formatterView($entity_type, $entity, $items, $display) {
    $element = array();

    if ($display['type'] == 'springboard_p2p_fields_personal_campaign_progress_auto') {

      if (isset($entity->field_p2p_campaign[$entity->language][0]['entity'])) {
        $campaign = $entity->field_p2p_campaign[$entity->language][0]['entity'];
      }
      else {
        $nid = $entity->field_p2p_campaign[$entity->language][0]['target_id'];
        $campaign = node_load($nid);
      }

      $goal_type = springboard_p2p_get_goal_type_from_campaign($campaign);

      foreach ($items as $delta => $value) {

        $value = springboard_p2p_format_progress($items[$delta], $goal_type);

        $element[$delta]['campaign_progress'] = array(
          '#markup' => '<div>' . $value . '</div>',
        );
      }
    }
    elseif ($display['type'] == 'springboard_p2p_fields_personal_campaign_progress_count') {
      $campaign = $entity->field_p2p_campaign[$entity->language][0]['entity'];
      $goal_type = springboard_p2p_get_goal_type_from_campaign($campaign);

      foreach ($items as $delta => $value) {

        $value = springboard_p2p_format_progress($items[$delta], $goal_type, FALSE);

        $element[$delta]['campaign_progress'] = array(
          '#markup' => $value,
        );
      }
    }
    elseif ($display['type'] == 'springboard_p2p_fields_personal_campaign_progress_amount') {
      foreach ($items as $delta => $value) {
        $element[$delta]['campaign_progress'] = array(
          '#markup' => springboard_p2p_format_progress($items[$delta], 'amount'),
        );
      }
    }
    elseif ($display['type'] == 'springboard_p2p_fields_personal_campaign_progress_submissions') {
      foreach ($items as $delta => $value) {
        $element[$delta]['campaign_progress'] = array(
          '#markup' => springboard_p2p_format_progress($items[$delta], 'submissions'),
        );
      }
    }

    return $element;
  }

  /**
   * Don't need to delete anything extra.
   */
  public function delete(&$items) {

  }

}
