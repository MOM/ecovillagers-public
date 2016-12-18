<?php
/**
 * @file
 * springboard_p2p_default_rules.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function springboard_p2p_default_rules_default_rules_configuration() {
  $items = array();
  $items['rules_p2p_admin_email_private_campaign_approval'] = entity_import('rules_config', '{ "rules_p2p_admin_email_private_campaign_approval" : {
      "LABEL" : "Send admin email about requesting approval to a private campaign",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Springboard P2P" ],
      "REQUIRES" : [ "rules", "springboard_p2p_rules" ],
      "ON" : [
        "springboard_p2p_user_requests_approval",
        "springboard_p2p_user_register_private_campaign"
      ],
      "DO" : [
        { "mail" : {
            "to" : [ "site:mail" ],
            "subject" : "User approval for private campaign",
            "message" : "A user, [account:sbp-first-name] [account:sbp-last-name], [account:mail] has requested permission to participate in the following campaign: [campaign:title], [campaign:url].\\r\\n\\r\\nTo approve the account please visit the approval queue: [site:url]\\/admin\\/springboard\\/p2p\\/approval\\/user.",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_p2p_password_reset_mail'] = entity_import('rules_config', '{ "rules_p2p_password_reset_mail" : {
      "LABEL" : "Send user a P2P password reset mail",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Springboard P2P" ],
      "REQUIRES" : [ "rules", "springboard_p2p_rules" ],
      "ON" : [ "springboard_p2p_user_requests_password_reset" ],
      "DO" : [
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "Password reset",
            "message" : "Here is your one time password reset URL:  [reset-url:value]",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_p2p_user_email_personal_campaign_creation'] = entity_import('rules_config', '{ "rules_p2p_user_email_personal_campaign_creation" : {
      "LABEL" : "Send user email after creating a personal campaign",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Springboard P2P" ],
      "REQUIRES" : [ "rules", "springboard_p2p_rules" ],
      "ON" : [ "springboard_p2p_user_creates_campaign" ],
      "DO" : [
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "You created a campaign!",
            "message" : "Thanks for creating a personal campaign.\\r\\n\\r\\nView it here:  [personal-campaign:url]\\r\\n\\r\\nView your campaign dashboard:  [dashboard-url:value]\\r\\n",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_p2p_user_email_private_campaign_approval_request'] = entity_import('rules_config', '{ "rules_p2p_user_email_private_campaign_approval_request" : {
      "LABEL" : "Send user email about requesting approval to a private P2P campaign",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Springboard P2P" ],
      "REQUIRES" : [ "rules", "springboard_p2p_rules" ],
      "ON" : [ "springboard_p2p_user_requests_approval" ],
      "DO" : [
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "Thanks for your interest",
            "message" : "Dear [account:sbp-first-name]:\\r\\n\\r\\nThanks for your interest in participating in our campaign. We\\u0027ll be in touch soon. \\r\\n\\r\\nIn the meantime, access your dashboard and check out other campaigns here: [dashboard-url:value]",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_p2p_user_email_private_campaign_approved'] = entity_import('rules_config', '{ "rules_p2p_user_email_private_campaign_approved" : {
      "LABEL" : "Send user email about being approved for a private campaign",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Springboard P2P" ],
      "REQUIRES" : [ "rules", "springboard_p2p_rules" ],
      "ON" : [ "springboard_p2p_user_is_approved" ],
      "DO" : [
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "You have been approved",
            "message" : "Dear [account:sbp-first-name]:\\r\\n\\r\\nYour account has been approved and you can start building your peer to peer campaign. Click here to create you campaign: [create-personal-campaign-url:value]\\r\\n",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_p2p_user_email_private_campaign_rejected'] = entity_import('rules_config', '{ "rules_p2p_user_email_private_campaign_rejected" : {
      "LABEL" : "Send user email about being rejected for a private campaign",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Springboard P2P" ],
      "REQUIRES" : [ "rules", "springboard_p2p_rules" ],
      "ON" : [ "springboard_p2p_user_is_rejected" ],
      "DO" : [
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "Your registration",
            "message" : "Dear [account:sbp_first_name]:\\r\\n\\r\\nWe can\\u0027t accept your registration at this time, but check out [site:url] for other ways you can get involved. ",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_p2p_user_email_registration'] = entity_import('rules_config', '{ "rules_p2p_user_email_registration" : {
      "LABEL" : "Send user email about new P2P registration (no campaign)",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Springboard P2P" ],
      "REQUIRES" : [ "rules", "springboard_p2p_rules" ],
      "ON" : [ "springboard_p2p_user_register_no_campaign" ],
      "DO" : [
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "Thanks for registering",
            "message" : "Dear [account:sbp-first-name]:\\r\\n\\r\\nThanks for registering. You can go here to create you campaign:  [dashboard-url:value]\\r\\n",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_p2p_user_email_registration_private_campaign'] = entity_import('rules_config', '{ "rules_p2p_user_email_registration_private_campaign" : {
      "LABEL" : "Send user email about new P2P registration (private campaign)",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Springboard P2P" ],
      "REQUIRES" : [ "rules", "springboard_p2p_rules" ],
      "ON" : [ "springboard_p2p_user_register_private_campaign" ],
      "DO" : [
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "Thanks for registering",
            "message" : "Dear [account:sbp-first-name]:\\r\\n\\r\\nThanks for registering. This campaign requires approval. We will be in touch shortly with next steps.\\r\\n\\r\\nIn the meantime, you can check out our other campaigns here: \\r\\n",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_p2p_user_email_registration_public_campaign'] = entity_import('rules_config', '{ "rules_p2p_user_email_registration_public_campaign" : {
      "LABEL" : "Send user email about new P2P registration (public campaign)",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Springboard P2P" ],
      "REQUIRES" : [ "rules", "springboard_p2p_rules" ],
      "ON" : [ "springboard_p2p_user_register_public_campaign" ],
      "DO" : [
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "Thanks for registering",
            "message" : "Dear [account:sbp-first-name]:\\r\\n\\r\\nThanks for registering. You can create a campaign here.\\r\\n\\r\\n[create-personal-campaign-url:value]\\r\\n\\r\\n\\r\\n",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  return $items;
}
