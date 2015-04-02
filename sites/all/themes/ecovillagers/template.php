<?php 
	
/**
 * Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 *   An array containing the breadcrumb links.
 * @return
 *   A string containing the breadcrumb output.
 */
function simplecorp_breadcrumb($variables){
  $breadcrumb = $variables['breadcrumb'];
  $breadcrumb_separator=theme_get_setting('breadcrumb_separator');

  if (!empty($breadcrumb)) {
	$breadcrumb[] = drupal_get_title();
	return '<div id="breadcrumb">' . implode(' <span class="breadcrumb-separator">' . $breadcrumb_separator . ' </span>' , $breadcrumb) . '</div>';
  }
}


/**
 * Preprocess function for node.tpl.php.
 */
/*
function ecovillagers_preprocess_node(&$variables) {
	$node = $variables['node'];
}
*/

/**
 * Implements hook_preprocess_html().
 */
function ecovillagers_preprocess_html(&$vars) {
  $vars['base_path'] = base_path();

  $vars['rdf'] = new stdClass;
  if (module_exists('rdf')) {
	$vars['doctype'] = '<!DOCTYPE html PUBLIC "-//W3C//DTD HTML+RDFa 1.1//EN">' . "\n";
	$vars['rdf']->version = ' version="HTML+RDFa 1.1"';
	$vars['rdf']->namespaces = $vars['rdf_namespaces'];
	$vars['rdf']->profile = ' profile="' . $vars['grddl_profile'] . '"';
  }
  else {
	$vars['doctype'] = '<!DOCTYPE html>' . "\n";
	$vars['rdf']->version = '';
	$vars['rdf']->namespaces = '';
	$vars['rdf']->profile = '';
  }
}
