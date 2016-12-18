<?php
/**
 * @file
 * This renders a donation form in 2 columns.
 *
 * The entire form is available in the variable $form. This can be broken down
 * and rendered as individual fields if needed.
 * print drupal_render($form['submitted']); - prints the entire form as-is.
 *
 * Variables
 * -----------------------------------------------
 * $form['submitted'] - The entire raw form.
 *   Break out individual fields as needed.
 * $donation_fieldset - The rendered donation fields.
 * $billing_address_fieldset - The rendered billing address fields.
 * $donor_information_fieldset - The rendered donor information fields.
 * $credit_card_fielset - The rendered credit card fields.
 *
 * Always print out the entire $form. This renders the remaining pieces of the
 * form that haven't yet been rendered above.
 * print drupal_render($form);
 */
?>

<?php print drupal_render($form['submitted']); ?>

<div id="donation-form-column-wrapper" class="container-fluid">
  <div class="row-fluid">
    <?php print $donation_fieldset; ?>
  </div>
  <div class="row-fluid">
    <div id="left" class="span6">
      <?php print $donor_information_fieldset; ?>
      <?php print $billing_information_fieldset; ?>
    </div>
    <div id="right" class="span6">
      <?php print $tribute_fieldset; ?>
      <?php print $payment_information_fieldset; ?>
      <div id="donation-form-footer">
        <?php print drupal_render_children($form); ?>
      </div>
      <?php print isset($recent_opt_in_donations) ? $recent_opt_in_donations : ''; ?>
    </div>
  </div>
</div>
