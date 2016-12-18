<?php
/**
 * @file
 * Class with helpers for getting lists of tests to run.
 */

class SpringboardTests {

  protected $all = array();
  protected $springboardTests = array();
  protected $contribTests = array();
  protected $coreTests = array();

  protected $springboardPath = 'sites/all/modules/springboard';
  protected $contribPath = 'sites/all/modules/contrib';
  protected $corePath = 'modules';

  protected $blacklistFilename;
  protected $blacklist = array();

  /**
   * Set the full blacklist filename.
   */
  public function __construct() {
    $this->blacklistFilename = drupal_get_path('module', 'springboard_tests') . '/tests_blacklist.csv';
  }

  /**
   * Get a list of test classes based on type and filtered by the blacklist.
   *
   * @param string $type
   *   Type of tests to get.
   *
   * @return array
   *   The test class names.
   */
  public function getTests($type) {
    switch ($type) {
      case 'all':
        return $this->allTests();

      case 'springboard':
        return $this->springboardCoreTests();

      case 'core':
        return $this->drupalCoreTests();

      case 'contrib':
        return $this->contribTests();

    }

    return array();
  }

  /**
   * Get an array of all test class names.
   *
   * @return array
   *   All test class names, minus the blacklisted ones.
   */
  public function allTests() {
    if (empty($this->all)) {
      $tests = simpletest_test_get_all();

      foreach ($tests as $classes) {
        $this->all = array_merge($this->all, array_keys($classes));
      }

      $this->all = $this->applyBlacklist($this->all);
    }

    return $this->all;
  }

  /**
   * Get all Springboard Core tests.
   *
   * @return array
   *   Test class names filtered by the blacklist.
   */
  public function springboardCoreTests() {
    if (empty($this->springboardTests)) {
      $this->springboardTests = $this->findTestsByPath($this->springboardPath);
    }

    return $this->springboardTests;
  }

  /**
   * Get all Drupal core tests.
   *
   * @return array
   *   Test class names filtered by the blacklist.
   */
  public function drupalCoreTests() {
    if (empty($this->coreTests)) {
      $this->coreTests = $this->findTestsByPath($this->corePath);
    }

    return $this->coreTests;
  }

  /**
   * Get all contrib tests.
   *
   * @return array
   *   Test class names filtered by the blacklist.
   */
  public function contribTests() {
    if (empty($this->contribTests)) {
      $this->contribTests = $this->findTestsByPath($this->contribPath);
    }

    return $this->contribTests;
  }

  /**
   * Apply the blacklist to the test class names.
   *
   * @param array $tests
   *   The test class names to filter against.
   *
   * @return array
   *   Filtered tests.
   */
  public function applyBlacklist(array $tests) {
    return array_diff($tests, $this->getBlacklist());
  }

  /**
   * Parses the blacklist file and returns the list of blacklisted tests.
   *
   * @return array
   *   The blacklist of test class names.
   */
  public function getBlacklist() {
    if (empty($this->blacklist)) {
      $this->blacklist = explode("\n", file_get_contents($this->blacklistFilename));
      $this->blacklist[] = '';
    }

    return $this->blacklist;
  }

  /**
   * Get a list of tests that exist in a certain path.
   *
   * @param string $path
   *   The beginning of the path to search in.
   *
   * @return array
   *   Test class names.
   */
  private function findTestsByPath($path) {
    $results = array();
    $tests = $this->allTests();

    foreach ($tests as $class) {
      $rows = db_select('registry', 'r')
        ->fields('r', array('filename'))
        ->condition('name', $class)
        ->condition('type', 'class')
        ->execute();

      foreach ($rows as $row) {
        if (strpos($row->filename, $path) === 0) {
          $results[] = $class;
        }
      }
    }

    return $results;
  }

}
