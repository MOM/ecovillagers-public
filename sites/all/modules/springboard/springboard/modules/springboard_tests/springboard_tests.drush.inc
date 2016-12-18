<?php
/**
 * @file
 * Drush commands to simplify testing Springboard via simpletest.
 */

/**
 * Implements hook_drush_command().
 */
function springboard_tests_drush_command() {
  $items = array();

  $items['springboard_tests-test_list'] = array(
    'callback' => 'drush_springboard_tests_test_list',
    'description' => 'Lists tests that would be run given a testing type. Applies test blacklist before display.',
    'arguments' => array(
      'type' => 'Types of tests. Can be springboard, core, contrib, all.',
    ),
    'require-arguments' => TRUE,
    'examples' => array(
      'sb-test-list all' => 'Show all tests.',
      'sb-test-list springboard' => 'Show all Springboard core test classes.',
      'sb-test-list core' => 'Show all Drupal core test classes.',
      'sb-test-list contrib' => 'Show all contrib test classes.',
    ),
    'aliases' => array(
      'springboard-test-list',
      'sb-test-list',
    ),
  );

  // Tools for running tests a little easier and output a little better.
  $items['springboard_tests-test_run'] = array(
    'callback' => 'drush_springboard_tests_run_the_tests',
    'description' => 'Run Springboard groups of tests. Applies a test blacklist.',
    'arguments' => array(
      'type' => 'What types of tests to run. Can be springboard, core, contrib, all.',
    ),
    'require-arguments' => TRUE,
    'options' => array(
      'xml' => 'Where to output the xml result files.',
    ),
    'examples' => array(
      'sb-test-run springboard --xml=/tmp/results/' => 'Run all Springboard tests.',
      'sb-test-run core --xml=/tmp/results/' => 'Run all Drupal core tests.',
      'sb-test-run contrib --xml=/tmp/results/' => 'Run all contrib modules tests.',
    ),
    'aliases' => array(
      'springboard-test-run',
      'sb-test-run',
    ),
  );

  return $items;
}

/**
 * Drush command callback: springboard_tests-test-list.
 *
 * @param string $type
 *   The group of tests to display.
 */
function drush_springboard_tests_test_list($type = '') {
  $st = new SpringboardTests();

  $tests = $st->getTests($type);
  drush_print(implode(',', $tests));
}

/**
 * Drush command callback: springboard_tests-test-run.
 */
function drush_springboard_tests_run_the_tests($type = '') {
  $st = new SpringboardTests();
  $tests = $st->getTests($type);

  if (empty($tests)) {
    return drush_set_error('SPRINGBOARD_TESTS_TEST_RUN_NONE', 'No tests found.');
  }

  drush_invoke_process('@self', 'test-clean');

  foreach ($tests as $test) {
    drush_invoke('test-run', array($test));
  }

}
