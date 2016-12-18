<?php
/**
 * @file
 * This template renders a webform node in 2 columns.
 */

?>

<div id="webform-form-column-wrapper" class="form-layout-container form-left">
  <div class="form-row">
    <div id="left" class="form-col">
      <?php print render($element['webform']); ?>
    </div>
    <div id="right" class="form-col">
      <h1 class="form-layout-title"><?php print render($element['title']); ?></h1>
      <?php print render($element['body']); ?>
    </div>
  </div>
</div>
