<?php
/**
 * @file
 * Template for a 2 column panel layout.
 *
 * This template provides a two column panel display layout, with
 * each column roughly equal in width. It is 5 rows high; the top
 * middle and bottom rows contain 1 column, while the second
 * and fourth rows contain 2 columns.
 *
 * Variables:
 * - $id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['top']: Content in the top row.
 *   - $content['left_above']: Content in the left column in row 2.
 *   - $content['right_above']: Content in the right column in row 2.
 *   - $content['middle']: Content in the middle row.
 *   - $content['left_below']: Content in the left column in row 4.
 *   - $content['right_below']: Content in the right column in row 4.
 *   - $content['right']: Content in the right column.
 *   - $content['bottom']: Content in the bottom row.
 */
?>
<div class="panel-display panel-2col-bricks clearfix" <?php if (!empty($css_id)) {
  print "id=\"$css_id\"";
} ?>>

  <?php if ($content['top']): ?>
    <div class="panels-top-wrapper">
      <div class="panel-panel panel-col-top">
        <div class="inside"><?php print $content['top']; ?></div>
      </div>
    </div>
  <?php endif; ?>

  <div class="center-wrapper">

    <div class="panel-panel panel-col-first">
      <div class="inside">

          <div class="panel-panel panel-middle-top-wrapper">
            <?php if ($content['middle_top_left']): ?>
            <div class="panel-middle-top-left"><?php print $content['middle_top_left']; ?></div>
            <?php endif; ?>

            <?php if ($content['middle_top_right']): ?>
              <div class="panel-middle-top-right"><?php print $content['middle_top_right']; ?></div>
            <?php endif; ?>

          </div>

        <?php if ($content['middle_left']): ?>
          <?php print $content['middle_left']; ?>
        <?php endif; ?>

      </div>
    </div>

    <?php if ($content['middle_right']): ?>
      <div class="panel-panel panel-col-last">
        <div class="inside"><?php print $content['middle_right']; ?></div>
      </div>
    <?php endif; ?>

  </div>
  <!-- // center-wrapper-->

  <?php if ($content['bottom']): ?>
    <div class="panel-panel panel-col-bottom">
      <div class="inside"><?php print $content['bottom']; ?></div>
    </div>
  <?php endif; ?>

</div>