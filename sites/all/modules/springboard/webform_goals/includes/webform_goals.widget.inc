<?php

/**
 * @file: widget serving code.
 */

/**
 * Rebuild widget markup for goals flagged for update.
 */
function webform_goals_rebuild_widgets() {
  $updated_goals = array();
  $update_limit = variable_get('webform_goals_widget_update_limit', 50);
  $results = db_query_range('
    SELECT
      *
    FROM {webform_goals}
    WHERE
      update_on_cron = 1
  ', 0, $update_limit);
  while ($goal = $results->fetchAssoc()) {
    $goal['extra'] = unserialize($goal['extra']);
    $args = array(
      'webform_goal' => $goal,
    );
    webform_goals_update_widget($args, 'gid');
    $updated_goals[] = $goal['gid'];
  }
  if (count($updated_goals)) {
    db_query('
      UPDATE {webform_goals}
      SET update_on_cron = 0
      WHERE gid IN (:gids)
    ', array(':gids' => $updated_goals));
  }
  return 'Webform goals update complete.';
}

function webform_goals_widget_display_embed($goal) {
  ctools_include('modal');
  ctools_include('ajax');
  $embed = theme('webform_goals_widget_loader', array('goal' => $goal));
  $output = '<p>' . t('Copy and paste this code to embed the goal widget.') . '</p>';
  $output .= $embed;
  return ctools_modal_render('Embeddable', $output);
}
