=== ABOUT ===

The Webform Goals module lets you set and track goals on your
site webforms.


=== INSTALLATION ===

Once the module has been enabled there are a number of files
that need to be modified to get the module up and running.

See INSTALL.txt for installation instructions.


=== CONFIGURATION ===

Goals are added via the module configuration form (admin/config/content/webform_goals)

Once one or more goals are added, goal templates may be displayed anywhere on the
site by adding the following markup:

<div class="wg-goal" data-gid="GID"></div>

where GID is the numeric goal id. This method will render the template
you have configured for the goal within the div tag.

Custom goal templates can also be constructed on the fly by using Webform Goals' built in
token replacement functionality.
Example:

<div class="wg-goal" data-gid="1">
[webform_goal:progress-bar]
My goal is to reach [webform_goal:target] submissions.
So far we have [webform_goal:progress-raw].
</div>

The goal tokens within the div are replaced with the corresponding values for
the goal selected.


=== TROUBLESHOOTING ===

If goal display is not working either locally or on a 3rd party website you should

* Confirm the webform_goals subfolder in the files directory has been created
  and can be written to.

* Confirm webform_goals.jsonp.php has been copied to the webform_goals subfolder
  in the files directory.

* Confirm any loader scripts in use have been updated with the correct URL for the
jsonp loader.




