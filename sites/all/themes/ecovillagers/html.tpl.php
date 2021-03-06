<?php print $doctype; ?>
<html lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>"<?php print $rdf->version . $rdf->namespaces; ?>>
    <head<?php print $rdf->profile; ?>>
        <meta name="viewport" content="width=device-width, initial-scale=1.0" />
        <?php print $head; ?>
        <title><?php print $head_title; ?></title>
        <?php print $styles; ?>

        <!--[if lt IE 9]>
        <script src="<?php print $base_path . path_to_theme() ?>/js/respond.min.js"></script>
        <script src="https://oss.maxcdn.com/html5shiv/3.7.3/html5shiv.min.js"></script>
        <![endif]-->

        <?php print $scripts; ?>
    </head>

    <body class="<?php print $classes; ?>" <?php print $attributes;?>>
        <div id="skip-link">
          <a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>
        </div>
        <?php print $page_top; ?>
        <?php print $page; ?>
        <?php print $page_bottom; ?>
    </body>
</html>
