/**
 * Store and parse market source data in cookies.
 */
Drupal.behaviors.marketSourceInit = {
  attach: function(context) { (function($) {

  $('body:not(.marketsource-processed)', context).each(function(i) {
    if (typeof Drupal.settings.market_source === 'undefined' ||
      typeof Drupal.settings.market_source.qs_keys === 'undefined') {
        return;
    }

    var qs_keys = Drupal.settings.market_source.qs_keys;

    // Create an element to parse the URI.
    var uri = document.createElement('a');
    uri.href = location.href;

    /**
     * Parse the raw querystring into an object.
     */
    var urlParams = {};
    (function () {
      var parsed,
          regex = /([^&=]+)=?([^&]*)/g,
          decode = function (value) {
            // Regex for replacing addition symbol with a space
            return decodeURIComponent(value.replace(/\+/g, " "));
          },
          querystring = uri.search.substring(1);
      while (parsed = regex.exec(querystring)) {
        var keyname = new String(decode(parsed[1]));
        urlParams[keyname.toLowerCase()] = decode(parsed[2]);
      }
    })();

    /**
     * Sets a cookie.
     */
    var setCookie = function (name, value, noOverwrite) {
      if (noOverwrite) {
        // make sure this cookie doesn't exist already
        var cookie = getCookie(name);
        if (cookie != false && cookie != null && cookie != '') {
          return;
        }
      }
      if (typeof $.cookie !== 'undefined') {
        name = 'market_source__' + name;
        if (typeof Drupal.settings.market_source.cookie_domain !== 'undefined') {
          $.cookie(name, value, { path: Drupal.settings.market_source.cookie_path, domain: Drupal.settings.market_source.cookie_domain });
        }
        else {
          $.cookie(name, value, { path: Drupal.settings.market_source.cookie_path });
        }
      }
    };

    /**
     * Reads data from a cookie.
     */
    var getCookie = function (name) {
      var retval = false;
      if (typeof $.cookie !== 'undefined') {
        name = 'market_source__' + name;
        retval = $.cookie(name);
      }
      return retval;
    };

    /**
     * Check the querystring keys for existing cookie values.
     */
    var applyParams = function (params) {
      for (var key in qs_keys) {
        // Check the querystring for this key.
        if (typeof params[key] !== 'undefined') {
          qs_keys[key]['value'] = params[key];
          if (qs_keys[key]['persistence'] != 'direct') {
            // Save this value as a cookie.
            setCookie(key, params[key], qs_keys[key]['persistence'] == 'on');
          }
        }
        if (qs_keys[key]['persistence'] != 'direct') {
          // Is there already a cookie set?
          var cookie = getCookie(key);
          if (cookie != false && cookie != null && cookie != '') {
            // Store the cookie's value in our qs_keys.
            qs_keys[key]['value'] = cookie;
          }
        }
      }
    };

    /**
     * Handle referrers as a special case.
     */
    var applyReferrer = function (preset) {
      var referrer
      if (typeof preset !== 'undefined' && typeof preset['referrer'] !== 'undefined') {
        referrer = preset['referrer'];
      }
      else {
        var referrer = document.referrer;
      }

      if (referrer == '') {
        referrer = '(none)';
      }
      var cookie;
      if (typeof qs_keys['initial_referrer']['value'] !== 'undefined') {
        cookie = getCookie('initial_referrer');
        if (cookie == false || cookie == null || cookie == '') {
          // Store the referrer value in our qs_keys.
          qs_keys['initial_referrer']['value'] = referrer;
          // Set initial_referrer cookie.
          setCookie('initial_referrer', qs_keys['initial_referrer']['value']);
        } else {
          qs_keys['initial_referrer']['value'] = cookie;
        }
      }
      if (typeof qs_keys['referrer']['value'] !== 'undefined') {
        if (referrer == '(none)') {
          // browser isn't providing a referrer, so check for one from before
          cookie = getCookie('referrer');
          if (cookie != false && cookie != null && cookie != '') {
            qs_keys['referrer']['value'] = cookie;
          }
        } else {
          // Store the referrer value in our qs_keys.
          qs_keys['referrer']['value'] = referrer;
          // Set the referrer cookie.
          setCookie('referrer', qs_keys['referrer']['value']);
        }
      }
    };

    /**
     * Populate the market source fields in this page's webforms.
     */
    var marketSourceFormPopulate = function() {
      if (typeof Drupal.settings.market_source.form_keys === 'undefined') {
        return;
      }

      // Set a maximum length for each key's value.
      var maxlength = 255;
      if (typeof Drupal.settings.market_source.maxlength !== 'undefined') {
        maxlength = Drupal.settings.market_source.maxlength;
      }

      // add search engine, search string, and user agent fields to qs_keys
      var qs_keys = Drupal.settings.market_source.qs_keys;
      if (typeof qs_keys['initial_referrer'] !== 'undefined' && typeof qs_keys['search_engine'] !== 'undefined'
        && qs_keys['search_engine']['value'] == null
      ) {
        if (/http(s?)\:\/\/www\.google\./.test(qs_keys['initial_referrer']['value'])) {
          qs_keys['search_engine']['value'] = 'Google';
        }
        else if (/http(s?)\:\/\/search\.msn/.test(qs_keys['initial_referrer']['value'])) {
          qs_keys['search_engine']['value'] = 'MSN';
        }
        else if (/http(s?)\:\/\/search\.yahoo/.test(qs_keys['initial_referrer']['value'])) {
          qs_keys['search_engine']['value'] = 'Yahoo!';
        }
        else if (/http(s?)\:\/\/www\.bing/.test(qs_keys['initial_referrer']['value'])) {
          qs_keys['search_engine']['value'] = 'Bing';
        }
        else if (/http(s?)\:\/\/msxml\.excite\.com/.test(qs_keys['initial_referrer']['value'])) {
          qs_keys['search_engine']['value'] = 'Excite';
        }
        else if (/http(s?)\:\/\/search\.lycos\.com/.test(qs_keys['initial_referrer']['value'])) {
          qs_keys['search_engine']['value'] = 'Lycos';
        }
        else if (/http(s?)\:\/\/www\.alltheweb\.com/.test(qs_keys['initial_referrer']['value'])) {
          qs_keys['search_engine']['value'] = 'All The Web';
        }
        else if (/http(s?)\:\/\/search\.aol\.com/.test(qs_keys['initial_referrer']['value'])) {
          qs_keys['search_engine']['value'] = 'AOL';
        }
        else if (/http(s?)\:\/\/(www)?\.ask\.co/.test(qs_keys['initial_referrer']['value'])) {
          qs_keys['search_engine']['value'] = 'Ask.com';
        }
        else if (/http(s?)\:\/\/www\.hotbot\.com/.test(qs_keys['initial_referrer']['value'])) {
          qs_keys['search_engine']['value'] = 'HotBot';
        }
        else if (/http(s?)\:\/\/www\.metacrawler\.com/.test(qs_keys['initial_referrer']['value'])) {
          qs_keys['search_engine']['value'] = 'Metacrawler';
        }
        else if (/http(s?)\:\/\/search\.earthlink\.net/.test(qs_keys['initial_referrer']['value'])) {
          qs_keys['search_engine']['value'] = 'Earthlink';
        }
      }
      if (typeof qs_keys['initial_referrer'] !== 'undefined' && typeof qs_keys['search_string'] !== 'undefined'
        && qs_keys['search_string']['value'] == null
      ) {
        // just Bing and Yahoo!. Google hides its search strings behind a redirect these days.
        if (/http(s?)\:\/\/search\.yahoo/.test(qs_keys['initial_referrer']['value'])) {
          var matches = /(\?|\&)p\=([^\&]+)/.exec(qs_keys['initial_referrer']['value']);
          if (matches != null && typeof(matches[2]) !== 'undefined') {
            qs_keys['search_string']['value'] = decodeURIComponent(matches[2].replace(/\+/g, '%20'));
          }
        }
        else if (/http(s?)\:\/\/www\.bing/.test(qs_keys['initial_referrer']['value'])) {
          var matches = /(\?|\&)q\=([^\&]+)/.exec(qs_keys['initial_referrer']['value']);
          if (matches != null && typeof(matches[2]) !== 'undefined') {
            qs_keys['search_string']['value'] = decodeURIComponent(matches[2].replace(/\+/g, '%20'));
          }
        }
      }
      if (typeof qs_keys['user_agent'] !== 'undefined') {
        qs_keys['user_agent']['value'] = navigator.userAgent;
      }

      // Iterate across all webforms on the page.
      for (var form_id in Drupal.settings.market_source.form_keys) {
        // Iterate across all form keys in this webform.
        var form_keys = Drupal.settings.market_source.form_keys[form_id];
        for (var key in form_keys) {
          // Is this key set in qs_keys object?
          if (typeof qs_keys[key]['value'] !== 'undefined') {
            var value = qs_keys[key]['value'];
            if (typeof value === 'string') {
              value = value.substring(0, maxlength);
            }
            // Handle referrers as a special case.
            if (key == 'initial_referrer' || key == 'referrer') {
              if (value == '(none)') {
                value = null;
              }
            }
            // If the value is not null, set the value.
            if (value != null) {
              //var selector = 'form#' + form_id + ' #' + form_keys[key] + ':not(.marketsource-processed)';
              var selector = 'form#' + form_id + ' input[name="' + form_keys[key] + '"]:not(.marketsource-processed)';

              // Set the value.
              $(selector, context)
                .val(qs_keys[key]['value'])
                .addClass('marketsource-processed');
            }
          }
        }
      }
    };

    var crossDomainMethod = function() {
      //Detect browser support for CORS.
      if ('withCredentials' in new XMLHttpRequest()) {
        return 'json';
      }
      // IE-specific "CORS" XDR.
      else if (typeof XDomainRequest !== "undefined") {
        // IE9 doesn't seem to work with cookie values.
        if (navigator.appVersion.indexOf("MSIE 9.") !== -1) {
          return 'jsonp';
        }
        return 'json';
      }
      // Fallback is to use JSONP.
      return 'jsonp';
    };

    // If the remote market source application is configured check that for ms values.
    if (
      Drupal.settings.market_source_remote
      && Drupal.settings.market_source_remote.app_id
      && Drupal.settings.market_source_remote.app_url
    ) {
      // Determine the data type for this request.
      var dataType = crossDomainMethod();

      // Create an array of values to be joined into the app request url.
      var rmsUrl = [
        Drupal.settings.market_source_remote.app_url,
        Drupal.settings.market_source_remote.app_id,
        (dataType === 'jsonp') ? 'get-jsonp' : 'get'
      ];

      // Create an array of values to be joined into the app request url's querystring.
      var rmsParams = [
        (dataType === 'jsonp') ? 'callback=?' : '',
        'host=' + encodeURIComponent(uri['hostname'])
      ];

      $.ajax({
        url: rmsUrl.join('/') + '?' + rmsParams.join('&'),
        type: 'GET',
        dataType: dataType,
        xhrFields: {
          withCredentials: true
        },
        success: function (data) {
          applyParams(data);
          applyParams(urlParams);
          applyReferrer(data);
          marketSourceFormPopulate()
        },
        error: function () { //Add these parameters to display the required response
          applyParams(urlParams);
          applyReferrer();
          marketSourceFormPopulate();
        }
      });
    }
    // Else apply only the url parameters.
    else {
      applyParams(urlParams);
      applyReferrer();
      marketSourceFormPopulate();
    }

  }).addClass('marketsource-processed');

  })(jQuery); }
};
