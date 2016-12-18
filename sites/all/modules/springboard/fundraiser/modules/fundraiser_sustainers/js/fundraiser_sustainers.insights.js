/**
 * @file
 * js for fuindraiser insights.
 */

(function ($, Drupal) {

  /**
   * Misc functions.
   *
   */
  Drupal.behaviors.insightsMisc = {
    attach: function (context) {

      if (typeof equalheight == 'function') {

        // Equal heights / load.
        $(window).load(function () {
          equalheight('.insights-today-box');
        });

        // Equal heights / resize.
        $(window).resize(function () {
          setTimeout(function () {
            equalheight('.insights-today-box');
          }, 500);
        });

        // Equal heights / Ajax. (if needed)
        $('.pager').ajaxComplete(function () {
          setTimeout(function () {
            equalheight('.insights-today-box');
          }, 500);
        });

      } // End if equalheight function.

      // Add a class to the amount col.
      $('.insights-historical-report .subhead_row th:contains("$")').addClass('itamount');

      // End context.
    }
  };


  // End script.
})(jQuery, Drupal);
