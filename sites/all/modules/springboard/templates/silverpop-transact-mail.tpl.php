<?php
/**
 * @TODO documntation here.
 */
?>

<XTMAILING>
  <CAMPAIGN_ID><?php print $mailing_id; ?></CAMPAIGN_ID>
  <RECIPIENT>
    <EMAIL><?php print $recipient_email; ?></EMAIL>
    <BODY_TYPE>HTML</BODY_TYPE>
    <?php foreach($personalization as $key => $value):?>
    <PERSONALIZATION>
      <TAG_NAME><?php print $key; ?></TAG_NAME>
      <VALUE><?php print $value; ?></VALUE>
    </PERSONALIZATION>
    <?php endforeach; ?>
  </RECIPIENT>
  <?php if($save_columns): ?>
  <SAVE_COLUMNS>
    <?php foreach($personalization as $key => $value):?>
      <COLUMN_NAME><?php print $key; ?></COLUMN_NAME>
    <?php endforeach; ?>
  </SAVE_COLUMNS>
  <?php endif; ?>
</XTMAILING>
