###############
#### README FOR WEBFORM_CONFIRMATION_ALIAS MODULE
###############

This module sets automatic aliases for webforms that use the traditional <confirmation> setting, i.e. http://example.com/node/[nid]/done?sid=[sid]. Instead of using such a raw system path, this module appends a configurable string to the webform’s existing alias. Example:

In this example, let’s imagine that the string appended is “thank-you”.

WEBFORM ALIAS		SYSTEM CONFIRMATION PATH	ALIASED CONFIRMATION PATH
secure/donate		node/[nid]/done			secure/donate/thank-you
donate/campaign1	node/[nid]/done			donate/campaign1/thank-you

…etc.



#### INSTALLATION

Install module from admin/modules page as usual.



#### USAGE

Once the module has been installed, visit Admin > Configuration > Content Authoring > Webform Settings > Confirmation Page Aliases (http://example.com/admin/config/content/webform/webform-confirmation-alias). Using this page, set the text you would like to use, site-wide, as the text to append to the confirmation alias as described above.

If you already have webforms on your website and would like confirmation aliases for each of them, check the “Update confirmation aliases for all existing forms?” box when saving your confirmation alias settings, or use the “Bulk Generate” button at any time. This functionality will create or update confirmation aliases for all existing webforms.

PLEASE NOTE: in order for a webform to make use of this module’s aliases, you must leave its “Redirection location” field at the default setting, “Confirmation page”. If you select “Custom URL” or “No redirect”, this module will not create aliases for its confirmation pages.