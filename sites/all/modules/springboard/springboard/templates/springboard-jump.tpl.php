<?php
/**
 * @file
 * Customize form report for the modal output.
 *
 * Available variables:
 * - $menu: The jump menu.
 */
?>
<div class="springboard-pane" id="springboard-jump-pane">
  <img src="<?php base_path() . drupal_get_path('module', 'springboard') . '/images/springboard.png'; ?>" width="300">
  <?php print $variables['menu']; ?>
</div>
