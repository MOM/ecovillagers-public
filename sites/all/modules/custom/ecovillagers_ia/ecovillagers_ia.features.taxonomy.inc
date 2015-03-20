<?php
/**
 * @file
 * ecovillagers_ia.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ecovillagers_ia_taxonomy_default_vocabularies() {
  return array(
    'inspiration_categories' => array(
      'name' => 'Inspiration Categories',
      'machine_name' => 'inspiration_categories',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'inspiration_series' => array(
      'name' => 'Inspiration Series',
      'machine_name' => 'inspiration_series',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
