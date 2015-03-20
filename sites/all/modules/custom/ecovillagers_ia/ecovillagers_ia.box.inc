<?php
/**
 * @file
 * ecovillagers_ia.box.inc
 */

/**
 * Implements hook_default_box().
 */
function ecovillagers_ia_default_box() {
  $export = array();

  $box = new stdClass();
  $box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $box->api_version = 1;
  $box->delta = 'anonymous_user_notice';
  $box->plugin_key = 'simple';
  $box->title = 'Are You an Ecovillager?';
  $box->description = 'Notice to display to anonymous users';
  $box->options = array(
    'body' => array(
      'value' => '<p>Ecovillagers is a cooperative movement, and anyone can join. The discussions, gatherings, and most of the inspirations here are a part of what we share with each other as a community. Please, join in!</p><p><strong>If you are a member, <a href="/user">sign in here</a>.</strong></p><p><strong>If you&#39;d like to become an ecovillager, <a href="/about/membership">here&#39;s how that works</a>.</strong></p>',
      'format' => 'full_html',
    ),
    'additional_classes' => '',
  );
  $export['anonymous_user_notice'] = $box;

  return $export;
}
