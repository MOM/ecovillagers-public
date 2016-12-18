<header class="clearfix container">
  <?php if ($logo) : print '<a href="/"><img src="'. check_url($logo) .'" alt="'. $site_name .'" id="logo" /></a>'; endif; ?>
  <?php print render($main_menu); ?>
  <?php print render($page['header']); ?>
</header>
<div id="main" class="container clearfix">
  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <h1 class="page-title"><?php print $title; ?></h1>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
  <?php if ($messages){ print $messages; } ?>
  <?php print render($tabs); ?>
  <div class="element-invisible"><a id="main-content"></a></div>
  <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
  <?php print render($page['content']); ?>
</div><!-- /main -->
<footer id="footer" class="clearfix region container">
    <?php print render($page['footer']); ?>
</footer>
