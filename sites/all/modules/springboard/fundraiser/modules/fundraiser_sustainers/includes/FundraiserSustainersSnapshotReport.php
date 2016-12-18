<?php
/**
 * @file
 * An abstract class for Sustainer Log reports.
 */

/**
 * Class FundraiserSustainersSnapshotReport.
 *
 * Common functionality between historical reports and forecast reports.
 */
abstract class FundraiserSustainersSnapshotReport {

  /**
   * The start date for the items in the report.
   *
   * @var DateTime
   */
  protected $begin;

  /**
   * The end date for the items in the report.
   *
   * @var DateTime
   */
  protected $end;

  /**
   * An array of the daily snapshots that are included in this report.
   *
   * @var FundraiserSustainersDailySnapshot[]
   */
  protected $snapshots;

  /**
   * Constructor. Creates the daily snapshots needed.
   *
   * @param DateTime $begin
   *   Beginning of the report range.
   * @param DateTime $end
   *   End of the report range.
   */
  public function __construct(DateTime $begin, DateTime $end) {
    // @todo Throw an Exception if begin is after end.
    // @todo Throw an Exception if the range is too big, beyond some threshold.
    $this->begin = $begin;
    $this->end = $end;

    $this->loadSnapshots();
  }

  /**
   * Get the beginning of the date range.
   *
   * @return DateTime
   *   Beginning date.
   */
  public function getBegin() {
    return $this->begin;
  }

  /**
   * Get the end of the date range.
   *
   * @return DateTime
   *   End date.
   */
  public function getEnd() {
    return $this->end;
  }

  /**
   * Get the array of daily snapshots.
   *
   * @return FundraiserSustainersDailySnapshot[]
   *   The snapshots in the report.
   */
  public function getSnapshots() {
    return $this->snapshots;
  }

  /**
   * Creates the array of daily snapshots in the report.
   */
  protected function loadSnapshots() {
    $interval = DateInterval::createFromDateString('1 day');
    $period = new DatePeriod($this->begin, $interval, $this->end);

    foreach ($period as $date) {
      $this->snapshots[$date->format("Y-m-d")] = new FundraiserSustainersDailySnapshot($date);
    }
  }

}
