<?php
/**
 * @file
 * This template renders a webform node in 2 columns.
 */

?>

<div id="webform-form-column-wrapper" class="form-layout-container form-top">
  <div class="form-row">
    <div id="left" class="form-col-row top">
      <?php print render($element['webform']); ?>
    </div>
    <div id="right" class="form-col-row below">
      <h1 class="form-layout-title"><?php print render($element['title']); ?></h1>
      <?php print render($element['body']); ?>
    </div>
  </div>
</div>
