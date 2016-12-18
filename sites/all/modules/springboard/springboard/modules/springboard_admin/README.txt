Overview
------------------------------------------------------------------------------
The Springboard Admin module, along with the Springboard Backend theme, creates
a contorlled user experience, separate from the Drupal administration, for users
of the Springboard platform. Following is a summary of the main features of the
Springboard UX and guidelines for editing and expanding each.

Springboard Custom Theme
------------------------------------------------------------------------------


Springboard Dashboard
------------------------------------------------------------------------------


Springboard Admin Menu
------------------------------------------------------------------------------


Springboard Path Aliases
------------------------------------------------------------------------------
Springboard incorporates a number of custom and contributed modules to provide
its features. Path aliases to various modules configuration and related pages
are utilized to create the appearence of a contained platform separate from 
Drupal. 

Adding a new page to the Springboard UX (utilizing a path alias) requires 3 
steps:

1. Create new alias in hook_inbound_path_alter (springboard_admin.module)
   - The path alias should begin with 'springboard/'
   - Example:
     if (preg_match([regex for alias], $path, $matches)) {
       $path = [actual path];
     }
2. Add redirect in hook_init (springboard_admin.module)
   - If user reaches a page via the Drupal admin path, redirect them to the 
     Springboard alias.
   - Be aware of the potential for infinite redirect loops.
   - Example:
     if (preg_match([regex for Drupal path], $path, $matches)) {
      drupal_goto([Springboard path], array('query' => $query, 'alias' => TRUE));
     }
3. Add a link to springboard_admin_menu (springboard_admin.menu.inc)

Springboard Custom Pages
------------------------------------------------------------------------------
