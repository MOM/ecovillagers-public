<?php

/**
 * @file
 * Base class for sustainer schedules.
 */

class sustainersBaseSchedule {

  /**
   * Constructor, each schedule will need a start, end and interval date object.
   *
   * @param string|DateTime object $start
   *   A date/time object or string to be converted. Enter NULL here to obtain the current time.
   * @param string|DateTime object $end
   *   A date/time object or string to be converted. Enter NULL here to obtain the current time.
   * @param object $donation
   *   An optional donation object, could be used by some schedules.
   */
  public function __construct($start = NULL, $end = NULL, $donation = NULL) {
    // Create the start DateTime object, if a DateTime object has been passed use that.
    if ($start && $start instanceof DateTime) {
      $this->start = $start;
    }
    else {
      $this->start = new DateTime($start);
    }

    // Create the end DateTime object, if a DateTime object has been passed use that.
    if ($end && $end instanceof DateTime) {
      $this->end = $end;
    }
    else {
      $this->end = new DateTime($end);
    }

    // Create an interval object.
    $this->interval = $this->end->diff($this->start);

    // Calculate the amount of segments in the interval.
    $this->intervalAmount = $this->calcIntervalAmount();

    $this->donation = $donation;
  }

  /**
   * Return the start Datetime object.
   */
  public function startDateTime() {
    return $this->start;
  }

  /**
   * Return the end Datetime object.
   */
  public function endDateTime() {
    return $this->end;
  }

  /**
   * Return the interval Datetime object.
   */
  public function intervalDateTime() {
    return $this->interval;
  }

  /**
   * Return the amount of segments in the interval.
   */
  public function intervalAmount() {
    return $this->intervalAmount;
  }

  /**
   * Return the amount of payments for this schedule.
   *
   * This function is called by sustainers when creating future orders.
   */
  public function scheduleAmount() {
    return $this->scheduleAmount;
  }

  /**
   * Return the max amount of sustainers this schedule can create.
   */
  public function scheduleLimit() {
    return variable_get('fundraiser_sustainers_create_limit', 50);
  }

  /**
   * Calculate the amount of payments from the interval.
   */
  public function calcIntervalAmount() {
  }

  /**
   * Return a DateTime object incremented by the passed amount.
   * 
   * @param numeric $increment
   *    Number of payments to increment.
   */
  public function advanceDate($increment) {
  }
}
