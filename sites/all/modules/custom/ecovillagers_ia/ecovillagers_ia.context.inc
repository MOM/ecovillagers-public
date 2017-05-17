<?php
/**
 * @file
 * ecovillagers_ia.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function ecovillagers_ia_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'home';
  $context->description = 'Viewing the home page';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'home' => 'home',
        '<front>' => '<front>',
      ),
    ),
  );
  $context->reactions = array(
    'theme_html' => array(
      'class' => 'home',
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Viewing the home page');
  $export['home'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'inspiration_anonymous_notice';
  $context->description = 'Display the notice to anonymous users below Inspiration content.';
  $context->tag = '';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'inspiration' => 'inspiration',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
    'user' => array(
      'values' => array(
        'anonymous user' => 'anonymous user',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'boxes-anonymous_user_notice' => array(
          'module' => 'boxes',
          'delta' => 'anonymous_user_notice',
          'region' => 'content',
          'weight' => '10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Display the notice to anonymous users below Inspiration content.');
  $export['inspiration_anonymous_notice'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'inspiration_authenticated';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'inspiration' => 'inspiration',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
    'user' => array(
      'values' => array(
        'authenticated user' => 'authenticated user',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-comments-block' => array(
          'module' => 'views',
          'delta' => 'comments-block',
          'region' => 'content',
          'weight' => '9',
        ),
        'commentsblock-comment_form_block' => array(
          'module' => 'commentsblock',
          'delta' => 'comment_form_block',
          'region' => 'content',
          'weight' => '10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;
  $export['inspiration_authenticated'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'inspiration_node';
  $context->description = 'Inspiration node is being viewed';
  $context->tag = '';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'inspiration' => 'inspiration',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-inspirations-block_body_teaser' => array(
          'module' => 'views',
          'delta' => 'inspirations-block_body_teaser',
          'region' => 'content',
          'weight' => '1',
        ),
        'views-inspirations-block_body_full' => array(
          'module' => 'views',
          'delta' => 'inspirations-block_body_full',
          'region' => 'content',
          'weight' => '2',
        ),
        'views-inspirations-block_author' => array(
          'module' => 'views',
          'delta' => 'inspirations-block_author',
          'region' => 'sidebar_first',
          'weight' => '-9',
        ),
        'views-inspirations-block_gathering' => array(
          'module' => 'views',
          'delta' => 'inspirations-block_gathering',
          'region' => 'sidebar_first',
          'weight' => '-8',
        ),
        'views-inspirations-block_categories' => array(
          'module' => 'views',
          'delta' => 'inspirations-block_categories',
          'region' => 'sidebar_first',
          'weight' => '-7',
        ),
        'service_links-service_links' => array(
          'module' => 'service_links',
          'delta' => 'service_links',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Inspiration node is being viewed');
  $export['inspiration_node'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'overview_node';
  $context->description = 'Overview node is being viewed';
  $context->tag = '';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'overview' => 'overview',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'service_links-service_links' => array(
          'module' => 'service_links',
          'delta' => 'service_links',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Overview node is being viewed');
  $export['overview_node'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'sitewide';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '~admin' => '~admin',
        '~admin/*' => '~admin/*',
      ),
    ),
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu_block-2' => array(
          'module' => 'menu_block',
          'delta' => '2',
          'region' => 'header',
          'weight' => '-10',
        ),
        'ecovillagers_ia-slogan' => array(
          'module' => 'ecovillagers_ia',
          'delta' => 'slogan',
          'region' => 'footer',
          'weight' => '-10',
        ),
        'menu_block-1' => array(
          'module' => 'menu_block',
          'delta' => '1',
          'region' => 'footer',
          'weight' => '-9',
        ),
        'boxes-site_social_links' => array(
          'module' => 'boxes',
          'delta' => 'site_social_links',
          'region' => 'footer',
          'weight' => '-8',
        ),
        'boxes-footer_home_link' => array(
          'module' => 'boxes',
          'delta' => 'footer_home_link',
          'region' => 'footer',
          'weight' => '-7',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;
  $export['sitewide'] = $context;

  return $export;
}
