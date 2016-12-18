<?php
/**
 * @file
 * Customize form report for the modal output.
 *
 * Available variables:
 * - $status: The Salesforce connection status.
 * - $updated_time: The last time the WSDL was updated.
 * - $batch_status: The status of the latest batch.
 * - $identity: Array of Salesforce identity information. Only populated if $status is TRUE.
 */
?>
  <h2>Sync Status</h2>
  <div class="sf-status"><?php print $variables['status'] ? '<p class="sf-connected">' . t('Salesforce connected') . '</p>' : '<p class="sf-notconncected">' .
    t('Salesforce not connected ') . '</p>' . l(t('Update authentication'), 'admin/config/salesforce/authorize', array('attributes'=>array('class'=>array('button')))) . '</span>'; ?><?php print($status ? render($queue) : ''); ?></div>
  <?php if ($status): ?>
  <ul>
  <li>Connected as: <?php print $identity['username'];?></li>
  <li>Organization Id: <?php print $identity['organization_id'];?></li>
  <?php print isset($variables['batch_status']) ? '<li>' . $variables['batch_status'] . '</li>' : ''; ?>
  </ul>
  <?php endif; ?>
