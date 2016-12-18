/**
 * @file
 * Misc JQuery scripts in this file
 */
(function ($) {
  // Add drupal 7 code.
  Drupal.behaviors.misc_p2pPersonal = {
    attach: function (context, settings) {
      // End drupal calls.

      // Fitvids for responsive video.
      $(document).ready(function() {
        $(".embedded-video").fitVids();
      });

      // Remove the panel seperator.
      $(".panel-separator").remove();

      // Get rid of label colons.
      $('.field-label').each(function() {
        var text = $(this).html();
        $(this).html( text.replace(':', '') );
      });

      // personal campaign slideshow.
      $('#slide-show').bjqs({
        height : 400,
        animspeed : 5800,
        responsive  : true,
        nexttext : '',
        prevtext : '',
        usecaptions : true,
        showmarkers : false
      });

      // Add a class to the panel if its adjacent one is empty.
      if ($('.panel-middle-top-right').length === 0){
        $('.panel-middle-top-left').addClass('no-middle-top-right');
      }

      // Remove the comment title if there are no comments.
      // @TODO - this should be done with php in personal_campaign_comments.inc
      if ($('ul.comment-wrapper').is(':empty')) {
        $('#p2p-comment-pane h2.pane-title').remove();
      }

      // end jquery.
    }};
})
(jQuery);
