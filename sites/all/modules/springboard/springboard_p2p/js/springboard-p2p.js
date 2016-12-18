/**
 * @file
 * Misc JQuery P2P scripts in this file.
 */
(function ($) {
  // Add drupal 7 code.
  Drupal.behaviors.p2pJS = {
    attach: function (context, settings) {
// End drupal calls.

      // Add a class to the parent for better theming.
      $('#edit-mail').parent('.control-group').addClass('email-wrapper');
      $('#edit-mail').parent('.form-item').addClass('email-wrapper');

    // Get rid of inline styles.
      $('.panel-display p').removeAttr("style");

      // Add uniform to selects. Use once because of ajax interfering.
      $('select').once('p2puniform', function () {
        $(this).uniform();
      });

      // Add uniform to file upload.
      $('input[type=file]').uniform();

      // Remove the panel seperator.
      $(".panel-separator").remove();

      // end jquery.
    }};
})
(jQuery);