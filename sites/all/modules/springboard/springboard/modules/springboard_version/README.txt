
CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Installation
 * Version data
 * Hooks

INTRODUCTION
------------

Springboard version provides insight into the expected versions of Springboard
modules for any given Springboard installation. As Springboard advances, if
minimum requirements for versions of modules change this system will alert you.

INSTALLATION
------------

1. Copy this directory to your sites/SITENAME/modules directory.

2. Enable the module.

VERSION DATA
------------------------
Version data is stored in springboard_version.data in the same format as used
for .info files elsewhere in Drupal. Please track the minimum required version
of a module for each version of Springboard.

For example, for Springboard 3.2 the minimum version of Webform may be 3.18, if
so then the entry for webform in the data file will be:

webform = 6.x-3.18

We track these versions in a central Springboard file to allow us to note
compatibility requirements for non-Springboard modules. As a Springboard module
is updated, especially if the update would make it incompatible with previous
versions of Springboard, be sure to note the updated file in this system.

HOOKS
-----
Springboard version provides a hook to allow Springboard modules to override
or add to the information listed in the data file as needed. This hook is:

hook_springboard_version_info_alter(&$modules) {}

$modules is an array of minimum springboard versions, keyed by module name.
