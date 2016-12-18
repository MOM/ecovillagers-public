<?php
/**
 * @file
 * Class for the Account Updater functionality of Litle.
 */

class CommerceLitleAccountUpdater {

  protected $methodInstance;

  /**
   * Save the method instance for later.
   *
   * @param array $method_instance
   *   The payment gateway's method instance data.
   *   Sometimes also called gateway_details.
   *   Needs to contain at least the settings for the payment method.
   */
  public function __construct(array $method_instance) {
    $this->methodInstance = $method_instance;
  }

  /**
   * Checks the payment method instance settings to see if we should extend it.
   *
   * @return bool
   *   TRUE if the sustainer series should be extended by one.
   */
  public function shouldExtendSustainers() {
    return
      isset($this->methodInstance['base'])
      && $this->methodInstance['base'] == 'commerce_litle_cc'
      && isset($this->methodInstance['settings']['accountupdater_extend_sustainers'])
      && $this->methodInstance['settings']['accountupdater_extend_sustainers'];
  }

  /**
   * Add a month to the given end date.
   *
   * @param int $year
   *   The year.
   * @param int $month
   *   The month.
   *
   * @return array
   *   An array with year and month keys.
   */
  public function getNewEndDate($year, $month) {
    $exp_datetime = new DateTime($year . '-' . $month);
    $exp_datetime->add(new DateInterval('P1M'));

    return array(
      'month' => $exp_datetime->format('n'),
      'year' => $exp_datetime->format('Y'),
    );
  }

  /**
   * Take the response XML from Litle and does the account updater stuff.
   *
   * @param DOMDocument $response
   *   The XML response document.
   * @param object $order
   *   The order object that has just been charged.
   *   This will be used as the template to create additional donations
   *   if needed.
   *
   * @return bool
   *   TRUE if an account update was detected and attempted.
   *   FALSE if nothing changed or we don't have enough info
   *   to perform the update.
   */
  public function processResponseXML(DOMDocument $response, $order) {
    $list = $response->getElementsByTagName('accountUpdater');

    if ($list->length == 0) {
      // No Account Updater tags.
      return FALSE;
    }

    $data = $this->getDataFromXML($list->item(0));

    // Do some error checking.
    if (!isset($data['originalCardTokenInfo']) || !isset($data['newCardTokenInfo'])) {
      return FALSE;
    }

    $changed = $this->cardHasChanged($data['originalCardTokenInfo'], $data['newCardTokenInfo']);

    if ($changed) {
      // Load the card on file card.
      $old_exp_date = $this->convertExpDateString($data['originalCardTokenInfo']['expDate']);
      $card = $this->findMatchingCardonfile($data['originalCardTokenInfo']['litleToken'], $old_exp_date, $order->uid);

      if (!$card) {
        // No card with a matching remote id or exp date or uid.
        // Do nothing even though we have new data.
        return FALSE;
      }

      // Save the new token info to the card on file.
      // A new token implies a new last 4 digits of the card number.
      $new_token = $data['newCardTokenInfo']['litleToken'];
      $new_number = substr($new_token, -4);
      $new_type = _commerce_litle_litle_card_type_to_cc($data['newCardTokenInfo']['type']);

      $card->remote_id = $new_token;
      // The long form of the card_type.
      $card->card_type = $new_type;
      // The card_number, which is the last 4 of the token for credit cards.
      $card->card_number = $new_number;

      // Convert the date format Litle uses to the one we use, and save it.
      $new_exp_date = $this->convertExpDateString($data['newCardTokenInfo']['expDate']);
      $card->card_exp_month = $new_exp_date['month'];
      $card->card_exp_year = $new_exp_date['year'];

      $card->changed = REQUEST_TIME;

      // Update billing info on existing future donations.
      // and create recurring donations through the new expiration date.
      $donation = fundraiser_donation_get_donation($order->order_id);
      if (isset($donation->recurring->master_did)) {
        $master_donation = fundraiser_donation_get_donation($donation->recurring->master_did);
        $submission_fields = $this->formatSubmissionFields($new_number, $new_type, $new_exp_date);

        // Only save the card on file if we are able to update the billing info
        // as well.
        commerce_cardonfile_save($card);
        $this->updateBillingInfo($master_donation, $submission_fields, $donation);

        return TRUE;
      }
    }

    return FALSE;
  }

  /**
   * Converts the date format from Litle to an array that Springboard likes.
   *
   * @param string $date_string
   *   The expiration date string from Litle.
   *   For example, 1114 for November 2014.
   *
   * @return array
   *   An array with month and year keys.
   */
  public function convertExpDateString($date_string) {
    $two_digit_year = (int) substr($date_string, -2);
    // Split the expDate into month and week.
    $exp_date = array(
      'month' => substr($date_string, 0, 2),
      'year' => 2000 + $two_digit_year,
    );

    return $exp_date;
  }

  /**
   * Extracts the important information from the accountUpdater XML.
   *
   * @param DOMNode $updater_node
   *   The DOM node for accountUpdater
   *
   * @return array
   *   The original and new card token info.
   */
  protected function getDataFromXML(DOMNode $updater_node) {
    $card_info_keys = array('originalCardTokenInfo', 'newCardTokenInfo');
    $card_keys = array('litleToken', 'expDate', 'type');
    $data = array();
    foreach ($updater_node->childNodes as $node) {
      if (in_array($node->nodeName, $card_info_keys)) {
        foreach ($node->childNodes as $thing) {
          if (in_array($thing->nodeName, $card_keys)) {
            $data[$node->nodeName][$thing->nodeName] = $thing->nodeValue;
          }
        }
      }
    }

    return $data;
  }


  /**
   * Get a matching cardonfile for the given token, expiration date, and uid.
   *
   * @param string $remote_id
   *   The Litle token, usually from litleToken.
   * @param array $exp_date
   *   An array with month and year keys.
   * @param int $uid
   *   User ID for the card on file.
   *
   * @return bool|object
   *   The card entity, or FALSE if nothing's found.
   */
  protected function findMatchingCardonfile($remote_id, array $exp_date, $uid) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'commerce_cardonfile')
      ->propertyCondition('remote_id', $remote_id)
      ->propertyCondition('uid', $uid)
      ->propertyCondition('card_exp_year', $exp_date['year'])
      ->propertyCondition('card_exp_month', $exp_date['month']);

    $result = $query->execute();

    if (isset($result['commerce_cardonfile'])) {
      $cards = commerce_cardonfile_load_multiple(array_keys($result['commerce_cardonfile']));
    }
    else {
      return FALSE;
    }

    // Could be an array or FALSE.
    if (!$cards || empty($cards)) {
      return FALSE;
    }

    $card = reset($cards);

    return $card;
  }

  /**
   * Formats an array for $submission_fields.
   *
   * @param int $card_number
   *   Last four digits of the card number.
   * @param string $card_type
   *   The card type.
   * @param array $exp_date
   *   Has month and year keys.
   * @param string $payement_method
   *   The payment method key to use.
   *
   * @return array
   *   An array that can be merged into $donation->donation to update payment.
   */
  protected function formatSubmissionFields($card_number, $card_type, array $exp_date, $payement_method = 'credit') {
    // To be merged into $donation->donation.
    return array(
      'payment_fields' => array(
        $payement_method => array(
          'card_number' => $card_number,
          'card_cvv' => '',
          'card_type' => $card_type,
          'card_expiration_month' => $exp_date['month'],
          'card_expiration_year' => $exp_date['year'],
        ),
      ),
    );
  }

  /**
   * Update the billing info on future sustainers and extend the series.
   *
   * @param object $master_donation
   *   The master donation for the sustainer series.
   * @param array $submission_fields
   *   The fields to merge into $donation->donation so they will get saved.
   * @param object $processed_donation
   *   The donation that was just processed before calling Account updater.
   */
  protected function updateBillingInfo($master_donation, array $submission_fields, $processed_donation) {
    // Use the just-processed donation to create new donations if needed.
    fundraiser_sustainers_update_billing_info_create_new_donations($master_donation, $processed_donation, $submission_fields);

    // Now grab the remaining unprocessed donations and update their
    // billing info.
    // This will update both newly created donations from and above and
    // existing unprocessed donations.
    $donations = _fundraiser_sustainers_get_donations_recurr_remaining($master_donation->did);
    if (!empty($donations)) {
      $this->updatePaymentFieldsOnExistingDonations($donations, $submission_fields);
    }

  }

  /**
   * Changes the payment_fields data on the set of donations.
   *
   * @param array $donations
   *   The donations to update.
   * @param array $submission_fields
   *   The submission fields with the new payment_fields data.
   */
  protected function updatePaymentFieldsOnExistingDonations(array $donations, array $submission_fields) {
    $name = 'Litle Account Updater';
    foreach ($donations as $donation) {
      $donation = fundraiser_donation_get_donation($donation->did);
      // Merge directly into donation data because the payment fields are
      // already clean (last 4 and expiration date) and we don't
      // want to request a new token. We already have it.
      $donation->data = array_merge($donation->data, $submission_fields);
      // Save each donation.
      fundraiser_donation_update($donation);

      // Add a comment.
      $comment = 'The card to be charged was changed on @date by @name.';
      $replacements = array(
        '@date' => format_date(strtotime('now')),
        '@name' => $name,
      );

      fundraiser_donation_comment($donation, $comment, $replacements);
      watchdog('commerce_litle', 'Billing information updated for donation @did.',
        array('@did' => $donation->did));

      // Update salesforce.
      if (module_exists('salesforce_genmap')) {
        $donation = fundraiser_donation_get_donation($donation->did);
        salesforce_genmap_send_object_to_queue('salesforce_donation', 'update',
          $donation->node, $donation->did, $donation, 'donation');
      }
    }
  }

  /**
   * Compare the original tokenized card data with the new data.
   *
   * @param array $original
   *   An array of original data with litleToken and expDate keys.
   * @param array $new
   *   An array of new data with litleToken and expDate keys.
   *
   * @return bool
   *   TRUE if this is a different card.
   */
  protected function cardHasChanged($original, $new) {
    return
      $original['litleToken'] != $new['litleToken']
      || $original['expDate'] != $new['expDate'];
  }
}
