(function ($) {
    Drupal.behaviors.quickSign = {
        attach: function (context, settings) {
            var editSubmit = $('#webform-component-sba-quicksign').find('#edit-submitted-sba-quicksign-children-submit');
            editSubmit.once(function() {
                editSubmit.click(function() {
                    editSubmit.hide();
                    editSubmit.after('<div class="webform-user-wrapper">' +
                      '<p class="webform-user-thank-you">Thank you, your submission is processing.</p>' +
                      '<div class="webform-user-spinner"></div>' +
                      '</div>');
                });
            });
        } // attach.function
    } // drupal.behaviors
})(jQuery);