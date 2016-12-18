(function($) {
  Drupal.behaviors.offlineCheck = {
    attach: function(context) {
      $('label[for$="offline-check-message"]').children('span.form-required').remove();
      $('label[for$="offline-check-check-number"]').children('span.form-required').remove();
      $(document).bind('state:required', function(e) {
        if (e.target.id.indexOf('offline-check') != -1) {
          $('label[for$="offline-check-message"]').children('span.form-required').remove();
          $('label[for$="offline-check-check-number"]').children('span.form-required').remove();
        }
      });
    }
  };
})(jQuery);