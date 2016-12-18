<?php
/**
 * @file
 * A class to manage form layouts.
 */

class FormLayout {

  // Public so drupal_write_record can change it.
  public $record;

  /**
   * Pass a nid in the constructor to attempt to load a layout immediately.
   *
   * @param int|null $nid
   *   Node id.
   */
  public function __construct($nid = NULL) {
    if (!is_null($nid)) {
      $this->load($nid);
    }
  }

  /**
   * Get the nid.
   *
   * @return int|null
   *   Node id if we have a template record for the node.
   *   Otherwise NULL;
   */
  public function getNid() {
    if (is_array($this->record) && !empty($this->record['nid'])) {
      $nid = $this->record['nid'];
    }
    else {
      $nid = NULL;
    }

    return $nid;
  }

  /**
   * Get the name of the form layout.
   *
   * @return string
   *   Name of the form layout, or the default layout if one can't be found.
   */
  public function getName() {
    if (is_array($this->record) && !empty($this->record['layout_name'])) {
      $name = $this->record['layout_name'];
    }
    else {
      $name = variable_get('form_layouts_default', 'one_column');
    }

    return $name;
  }

  /**
   * Save a new form layout record.
   *
   * @param int $nid
   *   Node id.
   * @param string $name
   *   Name of the form layout.
   *
   * @return array
   *   The record array as modified by drupal_write_record().
   */
  public function create($nid, $name) {
    $this->record = array(
      'nid' => $nid,
      'layout_name' => $name,
    );

    drupal_write_record('form_layouts_node', $this->record);

    return $this->record;
  }

  /**
   * Save the existing record.
   *
   * @param string $name
   *   The new form layout name.
   *
   * @return array
   *   The record array as modified by drupal_write_record().
   */
  public function update($name) {
    $this->record['layout_name'] = $name;

    drupal_write_record('form_layouts_node', $this->record, array('nid'));

    return $this->record;
  }

  /**
   * Deletes the form layout record for the currently loaded node.
   */
  public function delete() {
    if (isset($this->record['nid'])) {
      db_delete('form_layouts_node')
        ->condition('nid', $this->record['nid'])
        ->execute();
    }
  }

  /**
   * Load the form layout record.
   *
   * @param int $nid
   *   Node id.
   *
   * @return array
   *   The full record array.
   */
  public function load($nid) {
    $this->record = db_query('SELECT * FROM {form_layouts_node} WHERE nid = :nid',
      array(':nid' => $nid)
    )->fetchAssoc();

    return $this->record;
  }

}
