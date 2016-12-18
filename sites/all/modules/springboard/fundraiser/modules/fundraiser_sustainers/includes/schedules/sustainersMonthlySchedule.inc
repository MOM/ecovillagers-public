<?php

/**
 * @file
 * Contains class for generating a monthly payment schedule.
 */

class sustainersMonthlySchedule extends sustainersBaseSchedule {

  /**
   * Return the amount of payments for this schedule.
   */
  public function scheduleAmount() {
    // Return the interval amount since no adjustments required.
    return $this->intervalAmount;
  }

  /**
   * Calculate the amount of months from the interval DateTime object.
   */
  public function calcIntervalAmount() {
    return ($this->interval->format('%y') * 12) + $this->interval->format('%m');
  }

  /**
   * Return a DateTime object incremented by the passed amount.
   */
  public function advanceDate($increment) {
    $next = clone $this->start;

    // Get the start date string.
    $date = $this->start->format('Y-n-j');

    // Create an array of the individual date values.
    list($y, $m, $d) = explode('-', $date);

    // Add the number of months to the current count, loop through to add to the years.
    $m += $increment;
    while ($m > 12) {
      $m -= 12;
      $y++;
    }

    // If this current month doesn't have enough days as the start month, move the day value to the month's last day.
    $last_day = date('t', strtotime("$y-$m-1"));
    if ($d > $last_day) {
      $d = $last_day;
    }

    $next->setDate($y, $m, $d);
    return $next;
  }
}
