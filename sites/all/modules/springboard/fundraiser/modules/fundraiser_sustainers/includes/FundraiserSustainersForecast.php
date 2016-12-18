<?php
/**
 * @file
 * Sustainers Forecast report. Contains future snapshot data.
 */

/**
 * Class FundraiserSustainersForecast.
 */
class FundraiserSustainersForecast extends FundraiserSustainersSnapshotReport {

  public function __construct(DateTime $begin, DateTime $end) {
    // @todo Throw an Exception if either date is in the past.
    // @todo Throw an Exception if end is today.
    // begin is allowed to be today.
    parent::__construct($begin, $end);
  }
}
