<?php
/**
 * @file
 * A class for Sustainers historical reports. Contains past snapshots.
 */

/**
 * Class FundraiserSustainersHistoricalReport.
 */
class FundraiserSustainersHistoricalReport extends FundraiserSustainersSnapshotReport {

  public function __construct(DateTime $begin, DateTime $end) {
    // @todo Throw an Exception if either date is in the future.
    // @todo Throw an Exception if begin is today.
    // end is allowed to be today.
    parent::__construct($begin, $end);

    // Reverse the array for historical reports so the newest snapshots
    // are first.
    $this->snapshots = array_reverse($this->snapshots);
  }
}
