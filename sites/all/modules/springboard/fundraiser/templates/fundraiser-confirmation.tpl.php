<?php

/**
 * @file
 * Customize confirmation screen after successful donation.
 *
 * This file may be renamed "fundraiser-confirmation-[nid].tpl.php" to target a
 * specific donation form on your site. Or you can leave it
 * "fundraiser-confirmation.tpl.php" to affect all donation confirmations on your
 * site.
 *
 * Available variables:
 * - $node: The node object for this donation form.
 * - $confirmation_message: The confirmation message input by the donation form author.
 * - $sid: The unique submission ID of this submission.
 */
?>

<div class="fundraiser-confirmation">
  <?php if (isset($confirmation_message)): ?>
    <?php print $confirmation_message ?>
  <?php else: ?>
    <p><?php print t('Thank you, your submission has been received.'); ?></p>
  <?php endif; ?>
</div>
<div class="share">
  <?php if (isset($springboard_social_share) && !empty($springboard_social_share)) {
    print $springboard_social_share;
  } ?>
</div>
<div class="links">
  <a href="<?php print url('node/'. $node->nid) ?>"><?php print t('Go back to the form') ?></a>
</div>
