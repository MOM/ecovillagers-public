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
        'service_links-service_links' => array(
          'module' => 'service_links',
          'delta' => 'service_links',
          'region' => 'content',
          'weight' => '0',
        ),
        'views-inspirations-block_author' => array(
          'module' => 'views',
          'delta' => 'inspirations-block_author',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
        'views-inspirations-block_gathering' => array(
          'module' => 'views',
          'delta' => 'inspirations-block_gathering',
          'region' => 'sidebar_first',
          'weight' => '-9',
        ),
        'views-inspirations-block_categories' => array(
          'module' => 'views',
          'delta' => 'inspirations-block_categories',
          'region' => 'sidebar_first',
          'weight' => '-8',
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
          'region' => 'content',
          'weight' => '0',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Overview node is being viewed');
  $export['overview_node'] = $context;

  return $export;
}
