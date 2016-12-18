<?php
/**
 * @file
 * Customize form report for the modal output.
 *
 * Available variables:
 * - $help_array: 2D array of help information, organized by category.
 */
?>
<div class="springboard-help">
  <?php
  foreach ($variables['help_array'] as $category => $helps) {
    print '<h2>' . $category . '</h2>';
    foreach ($helps as $help) {
      print '<p>' . $help . '</p>';
    }
  }
  ?>
</div>
