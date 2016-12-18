<?php

/**
 * @file
 * Theme implementation to display a social action node.
 *
 * @var $use_layouts - Does the node use a form layout?
 */

  hide($content['comments']);
  hide($content['links']);
  hide($content['body']);
  hide($content['field_sba_social_action_img']);
  hide($content['field_sba_social_call_to_action']);
  //hide($content['sba_quicksign']);

?>

<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <div class="content"<?php print $content_attributes; ?>>

    <?php if(!$use_layouts): ?>
    <div class="container-fluid">
      <div class="row-fluid">
      <?php if(!empty($content['field_sba_social_action_img'][0]))  : ?>
        <div id="call-to-action" class="span8">
          <div id="call-to-action-call"><h2><?php print render($content['field_sba_social_call_to_action']); ?></h2></div>
          <div id="call-to-action-call-body"><?php print render($content['body']); ?></div>
        </div>
        <div id="image" class="span4"><?php  print render($content['field_sba_social_action_img']) ?></div>
      <?php else: ?>
        <div id="call-to-action" class="span12">
          <div id="call-to-action-call"><h2><?php print render($content['field_sba_social_call_to_action']); ?></h2></div>
          <div id="call-to-action-call-body"><?php print render($content['body']); ?></div>
        </div>
      <?php endif; ?>
      </div>
    </div>
    <div class="container-fluid">
    <?php endif; ?>

    <?php print render($content);?>

    <?php if(!$use_layouts): ?>
    </div>
    <?php //print render($content['sba_quicksign']); ?>
    <?php if(!empty($participants)): ?>
    <div id="participants-container" ><h4>Recent participants</h4><?php print $participants ?></div>
    <?php endif; ?>
  <?php endif; ?>

  </div>
  <?php print render($content['links']); ?>
  <?php print render($content['comments']); ?>
</div>
