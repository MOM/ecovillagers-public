<?php

/**
 * @file
 * Views field handler to display the percent complete campaign progress.
 */


class springboard_p2p_handler_field_campaign_progress_percent_complete extends views_handler_field {

  /**
   * Overload query().
   */
  public function query() {
  }

  /**
   * Render the percent complete.
   *
   * Calculates and displays percent complete based across all
   * personal campaigns in the campaign.
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

      $goal = springboard_p2p_get_goal_from_campaign($campaign);
      $goal_type = $goal['goal_type'];
      $goal_value = $goal['goal_value'];

      if (!empty($goal_type) && !empty($goal_value)) {
        $personal_campaigns = springboard_p2p_get_personal_campaigns($values->nid);

        foreach ($personal_campaigns as $personal_campaign) {
          $language = $personal_campaign->language;
          if (isset($personal_campaign->field_p2p_campaign_progress[$language][0])) {
            $progress = $personal_campaign->field_p2p_campaign_progress[$language][0];
            $progress_sums[$goal_type] += $progress[$goal_type];
          }
        }
        $output = springboard_p2p_format_percent($progress_sums[$goal_type], $goal_value);
      }
    }

    return $output;
  }
}
