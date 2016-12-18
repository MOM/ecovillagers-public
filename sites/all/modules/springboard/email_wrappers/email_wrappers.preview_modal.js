(function ($) {
  Drupal.behaviors.email_wrappers = {
    attach: function (context, settings) {
      // since the form id changes from one email form to the next, we have to jump some hoops
      // to get the form action.
      $parent_form = $('#email-wrappers-preview').closest("form").get(0);
      $current_action = $parent_form.getAttribute("action");

      if ($current_action != settings.basePath + 'email_wrappers/preview_modal/js/preview') {
        $old_action = $parent_form.getAttribute('action');
      }


      // Add onmouseover and onmouseout functions to swap form action
      $('#email-wrappers-preview').mouseenter(function(){
        $parent_form.setAttribute('action', settings.basePath + 'email_wrappers/preview_modal/js/preview');
      });

      $('#email-wrappers-preview').mouseleave(function(){
        $parent_form.setAttribute('action', $old_action);
        $current_action = $parent_form.getAttribute('action');
      });

      // Swap the original form action back on before submitting
      $('#edit-submit').mouseover(function() {
        // This shouldn't be necessary.
        $parent_form.setAttribute('action', $old_action);

      });
    }
  };
})(jQuery);
