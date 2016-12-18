/**
 * @file
 * Misc JQuery scripts in this file
 */
(function ($) {
  // Add drupal 7 code.
  Drupal.behaviors.misc_p2pLanding = {
    attach: function (context, settings) {
      // End drupal calls.

      // Instantiate Flexslider.
      if ($().flexslider) {
        $(window).load(function () {
          $('.flexslider').once(function () {
            $(this).flexslider({prevText: "", nextText: "", controlNav: false, pauseOnHover: true, slideshowSpeed: 6000});
          });
        });
      }

      // Responsive equal heights function for boxes in a grid.
      equalheight = function (container) {
        var currentTallest = 0,
          currentRowStart = 0,
          rowDivs = new Array(),
          $el,
          topPosition = 0;
        $(container).each(function () {

          $el = $(this);
          $($el).height('auto')
          topPostion = $el.position().top;

          if (currentRowStart != topPostion) {
            for (currentDiv = 0; currentDiv < rowDivs.length; currentDiv++) {
              rowDivs[currentDiv].height(currentTallest);
            }
            rowDivs.length = 0; // empty the array
            currentRowStart = topPostion;
            currentTallest = $el.height();
            rowDivs.push($el);
          } else {
            rowDivs.push($el);
            currentTallest = (currentTallest < $el.height()) ? ($el.height()) : (currentTallest);
          }
          for (currentDiv = 0; currentDiv < rowDivs.length; currentDiv++) {
            rowDivs[currentDiv].height(currentTallest);
          }
        });
      }

      // Now set equal height on the grids for various conditons.

      $(window).load(function () {
        equalheight('.campaign-landing-view ul.campaign-landing-grid li');
        equalheight('.campaign-landing-view .p2p-thumb-title');
        equalheight('.campaign-landing-featured-view ul.campaign-landing-grid li');
        equalheight('.campaign-landing-featured-view .p2p-thumb-title');
      });

      $(window).resize(function () {
        equalheight('.campaign-landing-view ul.campaign-landing-grid li');
        equalheight('.campaign-landing-view .p2p-thumb-title');
        equalheight('.campaign-landing-featured-view ul.campaign-landing-grid li');
        equalheight('.campaign-landing-featured-view .p2p-thumb-title');
      });

      // account for ajax pager.
      $('ul.pager').ajaxComplete(function() {
        equalheight('.campaign-landing-view ul.campaign-landing-grid li');
        equalheight('.campaign-landing-view .p2p-thumb-title');
        equalheight('.campaign-landing-featured-view ul.campaign-landing-grid li');
        equalheight('.campaign-landing-featured-view .p2p-thumb-title');
      });

      // end jquery.
    }};
})
(jQuery);
