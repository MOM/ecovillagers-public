Drupal.behaviors.fundraiserSustainersUpgrade = {
  attach: function(context) { (function($) {
    $('form.webform-client-form').submit();
  })(jQuery);
  }
}
