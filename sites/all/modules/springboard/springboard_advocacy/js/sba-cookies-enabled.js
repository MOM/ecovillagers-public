(function ($) {


  Drupal.behaviors.sbaCookies = {
    attach: function (context, settings) {
      $('#block-system-main').first('div.content').once('sbacookies', function () {
        var cookies = checkCookie();
        if (!cookies) {
          $('#block-system-main').first('div.content').prepend('<div class="alert error"><button type="button" class="close" data-dismiss="alert">×</button>Cookies are required. Please enable cookies in your browser preferences.</div>')
        }
      });

    }
  }

  var checkCookie = function() {
    if (navigator.cookieEnabled) {
      return true;
    }
    document.cookie = "sbacookie=1";
    var hasCookie = document.cookie.indexOf("sbacookie=") != -1;
    document.cookie = "sbacookie=1; expires=Thu, 01-Jan-1970 00:00:01 GMT";
    return hasCookie;
  }

})(jQuery);
