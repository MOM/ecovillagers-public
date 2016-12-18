<?php
/**
 * Implements hook_default_rules_configuration().
 */

function springboard_health_default_rules_configuration() {
  $items = array();
  $items['springboard_health_row_count_alert'] = entity_import('rules_config', '{
      "springboard_health_row_count_alert" : {
      "LABEL" : "Springboard Health Row Count Alert",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : true,
      "TAGS" : [ "springboard"],
      "REQUIRES" : [ "rules"],
      "ON" : [ "springboard_health_row_count_exceeded" ],
      "DO" : [
        { "mail" : {
            "to" : "[site:mail]",
            "subject" : "Table Row count exception detected on [site:name]",
            "message" : "Row count limit has been exceeded on [site:name].\r\n\r\nInformation as follows:\r\n\r\nLocation: [site:url]\r\nDB table: [sbh-table:value]\r\nCurrent row count: [sbh-current-size:value]\r\nNotification limit: [sbh-limit:value]\r\n",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  return $items;
}
