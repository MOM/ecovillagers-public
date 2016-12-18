<?php
/**
 * Implements hook_default_rules_configuration().
 */
function fundraiser_default_rules_configuration() {
  $items = array();
  $items['rules_gateway_test_mode_alert'] = entity_import('rules_config', '{
      "rules_gateway_test_mode_alert" : {
      "LABEL" : "Gateway Test Mode Alert",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "TAGS" : [ "fundraiser" ],
      "REQUIRES" : [ "rules", "fundraiser" ],
      "ON" : [ "fundraiser_gateway_test_mode_detected" ],
      "DO" : [
        { "mail" : {
            "to" : "[site:mail]",
            "subject" : "Gateway test mode detected on [site:name]",
            "message" : "A test mode gateway configuration has been detected on a live donation form on [site:name].  A gateway that is in test mode is unable to process donations.  If the gateway is in test mode unintentionally, you can take the gateway out of test mode by clicking here:\r\n\r\n[gateway-edit-link:value]\r\n\r\nIf this gateway should be in test mode you can ignore this notice. If you have questions, please contact your account team or support@jacksonriver.com.\r\n\r\nInformation as follows:\r\n\r\nLocation: [site:url]\r\nGateway ID: [gateway-id:value]\r\nPayment type: [gateway-method-name:value]\r\nCurrent status: [gateway-status:value]\r\n\r\nThis problem is affecting donations made on nodes at the following URLs:\r\n\r\n[gateway-node-id:value]",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  return $items;
}
