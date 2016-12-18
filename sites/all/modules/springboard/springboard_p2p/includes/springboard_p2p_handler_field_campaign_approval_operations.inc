<?php
/**
 * @file
 * Field handler to present a campaign approval's operations links.
 */

class springboard_p2p_handler_field_campaign_approval_operations extends views_handler_field {

  /**
   * Adds nid and uid fields.
   */
  public function construct() {
    parent::construct();

    $this->additional_fields['nid'] = 'nid';
    $this->additional_fields['uid'] = 'uid';
  }

  /**
   * Add the field to a query.
   */
  public function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  /**
   * Render the field.  Adds a placeholder comment.
   */
  public function render($values) {
    return '<!--form-item-' . $this->options['id'] . '--' . $this->view->row_index . '-->';
  }

  /**
   * Returns the form which replaces the placeholder from render().
   */
  public function views_form(&$form, &$form_state) {
    // The view is empty, abort.
    if (empty($this->view->result)) {
      return;
    }

    $form[$this->options['id']] = array(
      '#tree' => TRUE,
    );
    // At this point, the query has already been run, so we can access
    // the results in order to get the base key value (for example,
    // nid for nodes).
    foreach ($this->view->result as $row_id => $row) {

      $uid = $this->get_value($row, 'uid');
      $nid = $this->get_value($row, 'nid');

      $form[$this->options['id']][$row_id]['approve'] = array(
        '#type' => 'submit',
        '#value' => t('Approve'),
        '#name' => 'approve-' . $row_id,
        '#uid' => $uid,
        '#nid' => $nid,
      );

      $form[$this->options['id']][$row_id]['reject'] = array(
        '#type' => 'submit',
        '#value' => t('Reject'),
        '#name' => 'reject-' . $row_id,
        '#uid' => $uid,
        '#nid' => $nid,
      );
    }
  }

  /**
   * Submit handler for the field.  Saves the new status and triggers events.
   *
   * @todo Check the current status and don't do anything if it's not a change.
   */
  public function views_form_submit($form, &$form_state) {
    $field_name = $this->options['id'];

    foreach (element_children($form[$field_name]) as $row_id) {
      if ($form_state['triggering_element']['#name'] == 'approve-' . $row_id) {
        $data = $form[$field_name][$row_id]['approve'];
        $approval = new SpringboardP2pPrivateCampaignApproval($data['#uid'], $data['#nid']);
        $approval->approve();

        $event = new SpringboardP2pEvents();
        $event->userIsApproved(user_load($data['#uid']), node_load($data['#nid']));
      }
      elseif ($form_state['triggering_element']['#name'] == 'reject-' . $row_id) {
        $data = $form[$field_name][$row_id]['reject'];
        $approval = new SpringboardP2pPrivateCampaignApproval($data['#uid'], $data['#nid']);
        $approval->reject();

        $event = new SpringboardP2pEvents();
        $event->userIsRejected(user_load($data['#uid']), node_load($data['#nid']));
      }
    }
  }

}
