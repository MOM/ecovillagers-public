<?php
/**
 * @file
 * A rule config for sending an email when a sustainer check fails.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function fundraiser_sustainers_default_rules_configuration() {
  $items = array();
  $items['rules_sustainers_check_failure'] = entity_import('rules_config', '{
      "rules_sustainers_check_failure" : {
      "LABEL" : "Sustainers failed health checks.",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : true,
      "TAGS" : [ "fundraiser", "sustainers" ],
      "REQUIRES" : [ "rules", "fundraiser", "fundraiser_sustainers" ],
      "ON" : [ "fundraiser_sustainer_health_check_failure" ],
      "DO" : [
        { "mail" : {
            "to" : "[site:mail]",
            "subject" : "Fundraiser sustainers health check failure on [site:name]",
            "message" : "A sustainer has failed a health check. Please review the below information.\r\n\r\n[message:value]\r\n\r\nIf you have questions, please contact your account team or support@jacksonriver.com.\r\n\r\n",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  return $items;
}
