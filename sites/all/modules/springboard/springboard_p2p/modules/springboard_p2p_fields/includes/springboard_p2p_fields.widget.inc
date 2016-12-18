<?php

/**
 * @file
 * The theme function for the campaign goals widget.
 */


/**
 * Theme function for the p2p campaign goals widget.
 */
function theme_springboard_p2p_fields_campaign_goals($variables) {
  $widget = $variables['springboard_p2p_fields_campaign_goals'];

  $output = '';

  // The content types tables.
  $header = array(
    t('Type'),
    t('Default form'),
    t('Campaign override'),
    t('Goal type'),
    t('Goal'),
  );
  foreach (array('fundraiser', 'webform_user') as $type) {
    $rows = springboard_p2p_fields_form_types_table_rows($widget, $type);
    if (count($rows)) {
      $widget['form_types'][$type]['#markup'] = theme('table', array(
          'header' => $header,
          'rows' => $rows,
          'attributes' => array(
            'class' => array('springboard_p2p_campaign_goal_table_' . $type),
          ),
        ));
    }
  }

  // Everything else.
  $output .= drupal_render_children($widget);

  return $output;
}
