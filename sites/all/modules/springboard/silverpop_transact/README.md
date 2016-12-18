CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Requirements
 * Installation
 * Configuration
 * Troubleshooting

INTRODUCTION
------------

Silverpop offers a 'Transact' service, in which transactional e-mails (e.g.
donation and advocacy confirmations) can be sent via Silverpop, rather than
through the website. This can be beneficial for both deliverability (the
transactional and bulk e-mails can share the same IP, meaning that they can help
each others’ deliverability). This module provides several methods for sending
transactional email messages to end users via Silverpop.

The default model for delivery is Silverpop's [SMTP model](https://kb.silverpop.com/kb/Engage/Transact/2_Transact_SMTP).
This routes all outgoing emails from Drupal to Silverpop's SMTP servers (eg
transact5.silverpop.com) on port 25.

An alternative is the [XML model](https://kb.silverpop.com/kb/Engage/Transact/1_Transact_XML).
This method sends transactional email data, including personalization data, as
XML to Silverpop. Webform emails are supported, and a Rules Action for
generating a Transact XML document.


REQUIREMENTS
------------

* The SMTP model requires the Drupal SMTP contrib module.
* An account at Silverpop.
* The IP address of the sending host (Drupal) entered in Silverpop's security
settings section.

INSTALLATION
------------

Enable the Silverpop Transact and, optionally, the SMTP module on the
Module admin page.

CONFIGURATION
-------------

### Silverpop Configuration
1. [Silverpop Documentation for Transact XML Administrative Tasks](https://kb.silverpop.com/kb/Engage/Transact/1_Transact_XML/002_How_To/02_Administrator_Tasks/1_Set_up_Transact_XML_AdminTasks) or
[Set up and send a mailing using Transact SMTP](https://kb.silverpop.com/kb/Engage/Transact/2_Transact_SMTP/001_How_to/2_Set_up_and_Test_Transact_SMTP)
2. The Silverpop account must have Transact enabled. This is an account upgrade.
3. This module does not implement OAuth security. You should restrict access to the API to specified IP addresses via the Silverpop UI. Settings > Security Settings > [Access Restrictions](https://kb.silverpop.com/kb/Engage/004_Organization_Administration/01_How_to/1_Configure_Security_Settings/Configure_Access_Restrictions)
4. Create contact list if not already set up.

### Springboard Configuration:

#### SMTP Model (Default)
1. Go to the Silverpop Transact admin page at
/admin/config/services/silverpop/transact.
2. Select the API host for your Silverpop Account. For example, if you log into
Silver pop at engage5.silverpop.com, your API host is 5.
3. If using the SMTP model for sending messages, go to the SMTP module admin
page at admin/config/system/smtp and confirm the SMTP Server field is set to
transact5.silverpop.com (where "5" reflects your API host). This should be done
automatically for you.
4. Add/edit a confirmation email configuration on a donation web form. eg
http://springboard.dev/springboard/node/2/form-components/confirmation-emails/1
and enter a value for the "Silverpop SMTP X-Header" value field. It can be found
in the summary information of a Transactional Message Group in the Silverpop
admin. This value is added to an X Header on outgoing messages and is matched
to a Message Group in Silverpop.

#### XML Model
1. Enter your Silverpop login credentials Silverpop Transact admin page at
/admin/config/services/silverpop/transact.
2. Add/edit a confirmation email configuration on a donation web form. eg
http://springboard.dev/springboard/node/2/form-components/confirmation-emails/1
and enter a value for the "Silverpop Group ID" field.
3. Webform component submission data is included in the XML sent to silverpop
and can be used as replacement tokens for personalization in Silverpop email
templates. The webform Field Key is used as the Silverpop key. eg first_name,
mail, zip, etc
4. @TODO include Springboard donation tokens in XML so they can be used as
personalization tokens in Silverpop email templates.
5. @TODO info about using the rule defined in this module "Create Silverpop
Transact mailing"


TROUBLESHOOTING
---------------
* Some ISP's block port 25, which prevents messages from being delivered to
Silverpop when using the SMTP model. To rule this out, type
`telnet transact5.silverpop.com 25` from the command line. If the port is open,
you should see something like this:

```shell
$ telnet transact5.silverpop.com 25
Trying 74.112.69.28...
Connected to transact5.ibmmarketingcloud.com.
Escape character is '^]'.
220 Silverpop Mail Relay System - AUTHORIZED USE ONLY
```

* Ensure that your IP address has been entered in the Security Settings admin
area in Silverpop and that is has not CHANGED since last time you used it.

