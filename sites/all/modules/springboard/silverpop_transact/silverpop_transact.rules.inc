<?php
/**
 * @file
 * Provides integration with the rules module.
 */

/**
 * Implements hook_rules_action_info().
 */
function silverpop_transact_rules_action_info() {
  return array(
    'silverpop_transact_rules_action' => array(
      'label' => t('Create Silverpop Transact mailing'),
      'group' => t('Silverpop Transact'),
      'parameter' => array(
        'recipient_email' => array(
          'type' => 'text',
          'label' => t('Recipient Email'),
          'description' => t('The recipient email.'),
        ),
        'campaign_id' => array(
          'type' => 'text',
          'label' => t('The Silverpop Campaign ID'),
          'description' => t('Enter the numeric ID for the Silverpop Automated Messages group.'),
        ),
        'personalization' => array(
          'type' => 'text',
          'label' => t('Personalization Tokens'),
          'description' => t('Enter a list of key|value pairs for values to be replaced in the Silverpop Transact template.'),
        ),
        'save_columns' => array(
          'type' => 'boolean',
          'label' => t('Save Columns'),
          'description' => t('Save personalization tokens to the Engage database.'),
        ),
      ),
    ),
  );
}

/**
 * Rules action callback.
 *
 * Runs $personalization string through
 * silverpop_transact_parse_personalization() in order to turn it into an assoc
 * array before calling silverpop_transact_create_mailing().
 */
function silverpop_transact_rules_action($recipient_email, $campaign_id, $personalization, $save_columns) {
  silverpop_transact_create_mailing($recipient_email, $campaign_id, silverpop_transact_parse_personalization($personalization), $save_columns);
}
