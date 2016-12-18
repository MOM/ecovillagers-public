<?php
/**
 * @file
 * A class for managing private campaign approvals.
 */

class SpringboardP2pPrivateCampaignApproval {

  protected $record = array();

  /**
   * Sets up the data for the approval.
   *
   * @param int $uid
   *   The requesting user's uid.
   * @param int $nid
   *   The campaign nid for which access is being requested.
   */
  public function __construct($uid, $nid) {
    $this->record = array(
      'uid' => $uid,
      'nid' => $nid,
      'status' => NULL,
    );

    $this->loadStatus();

    return $this;
  }

  /**
   * User is approved to create personal campaigns for a campaign.
   *
   * @return bool
   *   TRUE if the user is approved to create personal campaigns in
   *   the campaign.
   */
  public function isAuthorized() {
    return $this->record['status'] == 'approved';
  }

  /**
   * Save status as requested.
   */
  public function request() {
    $this->write('requested');
  }

  /**
   * Save status as approved.
   */
  public function approve() {
    $this->write('approved');
  }

  /**
   * Save status as rejected.
   */
  public function reject() {
    $this->write('rejected');
  }

  /**
   * Delete all approval records for a user account.
   *
   * @param int $uid
   *   The user id.
   */
  static public function deleteAll($uid) {
    db_delete('springboard_p2p_private_campaign_approval')
      ->condition('uid', $uid)
      ->execute();
  }

  /**
   * Loads the status from the DB if the row exists.
   */
  protected function loadStatus() {
    $replacements = array(
      ':uid' => $this->record['uid'],
      ':nid' => $this->record['nid'],
    );
    $result = db_query('SELECT status FROM {springboard_p2p_private_campaign_approval} WHERE uid = :uid AND nid = :nid', $replacements);
    $status = $result->fetchField();
    if (is_string($status)) {
      $this->record['status'] = $status;
    }
  }

  /**
   * Delete the record from the table.
   */
  protected function delete() {
    db_delete('springboard_p2p_private_campaign_approval')
      ->condition('nid', $this->record['nid'])
      ->condition('uid', $this->record['uid'])
      ->execute();
  }

  /**
   * Delete existing records for this uid, nid combination, and save a new one.
   *
   * @param string $status
   *   'requested', 'accepted', or 'rejected'
   */
  protected function write($status) {
    $this->record['status'] = $status;
    $this->record['created'] = time();
    $this->delete();
    drupal_write_record('springboard_p2p_private_campaign_approval', $this->record);
  }
}
