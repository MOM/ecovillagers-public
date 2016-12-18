<?php
/**
 * @file
 * Customize form report for the modal output.
 *
 * Available variables:
 * - $access_results: Tracking results for the given form.
 * - $nid: Node id for the form.
 * - $total_donations: Total donations for the given form.
 */
?>
<div class="springboard-form-report">
  <h2>
  <?php print isset($variables['access_results']->internal_name) ? $variables['access_results']->internal_name : ''; ?>
  <?php print isset($variables['nid']) ? l(t('view'), 'node/' . $variables['nid']) . ' | ' : ''; ?>
  <?php print isset($variables['nid']) ? l(t('edit'), 'node/' . $variables['nid']. '/edit') . ' | ' : ''; ?>
  <?php print isset($variables['nid']) ? l(t('donation history'), 'node/' . $variables['nid'] . '/webform-results') : ''; ?>
  </h2>
  <div class="springboard-form-data">
  Pageviews: <?php isset($variables['access_results']->pageviews) ? $variables['access_results']->pageviews : 0; ?> <br />
  Total conversions: <?php isset($variables['access_results']->conversions) ? $variables['access_results']->conversions : 0; ?> <br />
  # of local failures: <?php isset($variables['access_results']->local_failures) ? $variables['access_results']->local_failures : 0; ?> <br />
  # of gateway failures: <?php isset($variables['access_results']->gateway_failures) ? $variables['access_results']->gateway_failures : 0; ?> <br />
  Total donations:$<?php isset($variables['total_donations']) ? $variables['total_donations'] : ''; ?> <br />
  </div>
</div>
