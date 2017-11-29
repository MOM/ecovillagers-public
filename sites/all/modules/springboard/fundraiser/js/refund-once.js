(function($) {
  Drupal.behaviors.fundraiserRefundOnce = {
    attach: function (context, settings) {
      $('#edit-issue-refund').once(function() {
        $('#edit-issue-refund').click(function() {
          var  button = $(this);
          button.css('display', 'none');
          button.after('<div><p>Thank you, the refund is processing.</p><div>');
        });
      });
    }
  }
})(jQuery);