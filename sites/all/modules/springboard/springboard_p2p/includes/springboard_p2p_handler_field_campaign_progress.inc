<?php
/**
 * @file
 * Views field handler to calculate and display campaing progress.
 */


class springboard_p2p_handler_field_campaign_progress extends views_handler_field {

  /**
   * Overload the query method.
   */
  public function query() {
  }

  /**
   * Render the field value.
   *
   * Sums the progress across all personal campaigns in the campaign.
   */
  public function render($values) {
    $output = '';
    $progress_sums = array(
      'submissions' => 0,
      'amount' => 0,
    );
    $goal_type = NULL;

    if (isset($values->nid)) {
      $campaign = entity_load('node', array($values->nid));
      $campaign = array_pop($campaign);
      $goal_type = springboard_p2p_get_goal_type_from_campaign($campaign);

      $personal_campaigns = springboard_p2p_get_personal_campaigns($values->nid);

      foreach ($personal_campaigns as $personal_campaign) {
        $language = $personal_campaign->language;
        if (isset($personal_campaign->field_p2p_campaign_progress[$language][0])) {
          $progress = $personal_campaign->field_p2p_campaign_progress[$language][0];
          $progress_sums[$goal_type] += $progress[$goal_type];
        }
      }
      $output = springboard_p2p_format_progress($progress_sums, $goal_type, TRUE);
    }

    return $output;
  }
}
