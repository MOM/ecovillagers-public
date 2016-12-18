<?php
/**
 * @file
 * Provides a factory design pattern for the p2p custom fields.
 */

class SpringboardP2pFieldsFactory {

  /**
   * Get an instance of the field class.
   *
   * @param string $type
   *   The p2p field type.
   *
   * @return object
   *   The field class.
   */
  static public function getField($type) {
    switch ($type) {
      case 'springboard_p2p_fields_campaign_goals':
        return new SpringboardP2pCampaignGoalsField();

      case 'springboard_p2p_fields_personal_campaign_progress':
        return new SpringboardP2pPersonalCampaignProgressField();

    }

    return NULL;
  }

}
