<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */

?>
<?php if (!empty($title)) : ?><div class="views-group <?php print(drupal_html_class($title)); ?>"><?php endif; ?>
<ul class="no-list-bg">
<?php foreach ($rows as $id => $row): ?>
  <li<?php if ($classes_array[$id]) { print ' class="' . $classes_array[$id] .'"';  } ?>>
    <?php print $row; ?>
  </li>
<?php endforeach; ?>
</ul>
<?php if (!empty($title)) : ?>
  </div>
<?php endif; ?>