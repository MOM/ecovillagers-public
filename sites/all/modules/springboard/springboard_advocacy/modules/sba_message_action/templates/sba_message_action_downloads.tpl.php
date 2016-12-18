<?php print $tabs; ?>
<div class="container failed-messages-container">
  <div class="row">
    <div class="span3">
      <div class="well">
        <h2 class="text-info"><?php print $message_action_metrics->failed; ?></h2>
        Failed Messages<br />Available to Download
      </div>
    </div>
    <div class="span3">
      <div class="well">
        <h2 class="text-info"><?php print $message_action_metrics->hold; ?></h2>
        Hold Messages<br />&nbsp;
      </div>
    </div>
  </div>
</div>
<h2>Download Failed Messages</h2>
<div class="well">
  <?php print $form; ?>
</div>
<h2>Fail Held Messages</h2>
<div class="well">
  <?php print $fail_messages_form; ?>
</div>
<br />
