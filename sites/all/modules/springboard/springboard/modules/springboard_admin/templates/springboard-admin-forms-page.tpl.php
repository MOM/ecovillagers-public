


<?php /* Start the count. */ $zebra = 0; ?>

<?php foreach ($types as $type) : ?>
  <?php
    // Define odd / even for use in the definition list.
    $zebra_class = ($zebra % 2) ? 'even' : 'odd';
  ?>
  <div class="types-wrapper <?php print $zebra_class; ?>">
    <h2 class="types"><?php print $type->name; ?></h2>
    <div class="buttons-wrapper">
      <?php if (node_access('create', $type->type)) : ?>
        <a href="<?php print base_path(); ?>node/add/<?php print preg_replace('/_/', '-', $type->type); ?>" class="button add-button"><?php print t('Create'); ?> <?php print $type->name; ?></a>
      <?php endif; ?>
    </div><!-- // buttons-wrapper -->
    <?php print($tables[$type->type]); ?>
    <?php $zebra++; ?>
    <a class="button more-button" href="<?php print base_path(); ?>admin/springboard/<?php print ($springboard_type == 'fundraiser') ? 'donation-forms' : 'forms'; ?>/<?php print $type->type; ?>">
      <?php print t('View all');?> <?php print $type->name; ?></a>
  </div>
<?php endforeach; ?>
