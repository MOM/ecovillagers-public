<div id="page-wrapper"><div id="page">

  <div id="header"><div class="section clearfix">
    <?php print render($page['header']); ?>
  </div></div> <!-- /.section, /#header -->

  <div id="main-wrapper" class="clearfix"><div id="main" class="clearfix">

    <?php if ($messages): ?>
      <div id="messages"><div class="section clearfix">
        <?php print $messages; ?>
      </div></div> <!-- /.section, /#messages -->
    <?php endif; ?>

    <?php if ($breadcrumb): ?>
      <div id="breadcrumb"><?php print $breadcrumb; ?></div>
    <?php endif; ?>

    <a id="main-content"></a>
    <?php if ($page['highlighted']): ?><div id="highlighted"><?php print render($page['highlighted']); ?></div><?php endif; ?>

    <div id="content-wrapper">
      <?php print render($title_prefix); ?>
      <?php if ($title): ?>
        <h1 class="title" id="page-title">
          <?php print $title; ?>
        </h1>
      <?php endif; ?>
      <?php print render($title_suffix); ?>
      <?php if ($tabs): ?>
        <div class="tabs">
          <?php print render($tabs); ?>
        </div>
      <?php endif; ?>
      <?php print render($page['help']); ?>
      <?php if ($action_links): ?>
        <ul class="action-links">
          <?php print render($action_links); ?>
        </ul>
      <?php endif; ?>

      <div id="content">
        <?php print render($page['content']); ?>
      </div> <!-- /#content -->

    </div> <!-- /#content-wrapper -->

    <?php if ($page['sidebar_first']): ?>
      <div id="sidebar-first" class="sidebar<?php print (count(element_children($page['sidebar_first'])) > 1) ? ' with-bottom' : ' top-only'; ?>">
        <?php print render($page['sidebar_first']); ?>
      </div> <!-- /#sidebar-first -->
    <?php endif; ?>

    <?php if ($page['sidebar_second']): ?>
      <div id="sidebar-second" class="sidebar">
        <?php print render($page['sidebar_second']); ?>
      </div> <!-- /#sidebar-second -->
    <?php endif; ?>

    </div></div> <!-- /#main, /#main-wrapper -->

  <?php if ($page['footer']): ?>
    <div id="footer" class="clearfix">
      <?php print render($page['footer']); ?>
    </div> <!-- /#footer -->
  <?php endif; ?>

</div></div> <!-- /#page, /#page-wrapper -->
