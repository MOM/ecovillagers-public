<?php
/**
 * @file
 * This renders a donation form in 2 columns.
 */

?>

<?php print drupal_render($form['submitted']); ?>

<div id="donation-form-column-wrapper" class="container-fluid">
  <div class="row-fluid">
    <div id="left" class="span6">
      <?php print $donor_information_fieldset; ?>
      <?php print $billing_information_fieldset; ?>
      <?php print $tribute_fieldset; ?>
    </div>
    <div id="right" class="span6">
      <?php print $donation_fieldset; ?>
      <?php print $payment_information_fieldset; ?>
    </div>
  </div>
  <div class="row-fluid">
    <div id="donation-form-footer">
      <?php print drupal_render_children($form); ?>
    </div>
    <?php print isset($recent_opt_in_donations) ? $recent_opt_in_donations : ''; ?>
  </div>
</div>
