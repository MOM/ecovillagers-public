(function ($) {
  // Collapses large table cell content into a hideable block
  Drupal.behaviors.springboardCollapsibleTd = {
    attach: function (context, settings) {

    // Show hide the error messages and close if clicked outside.
      $('.sb-collapsible-td .control').each(function () {
        $(this).click(function (e) {
          $(this).parent('.sb-collapsible-td').toggleClass('collapsed');
          e.stopPropagation();
        });
        // In case clicked inside the opened content.
        $(".sb-collapsible-td").click(function (e) {
          e.stopPropagation();
        });
        // Now close if clicked outside the opened content.
        $(document).click(function () {
          $(".sb-collapsible-td").addClass('collapsed');
        });
      });

    } // attach.function
  } // drupal.behaviors
})(jQuery);

(function ($) {
  // Adds a tooltip for the SF Error Codes to the header of the batch item log.
  Drupal.behaviors.springboardSfErrorCodes = {
    attach: function (context, settings) {
     $('.view-sbv-sf-batch-items th.views-field-error-code').append('<span class="sb-errors-tip collapsed"><a class="sb-errors-control">What\'s This?</a><span class="sb-errors-content"><a href="https://www.salesforce.com/us/developer/docs/api/Content/sforce_api_calls_concepts_core_data_objects.htm#i1421192">Error code definitions.</a></span></span>').once();
     $('.view-sbv-sf-batch-items th.views-field-error-code .sb-errors-control').click(function(){
       $(this).parent('.sb-errors-tip').toggleClass('collapsed');
     });
    } // attach.function
  } // drupal.behaviors
})(jQuery);

(function ($) {
  Drupal.behaviors.springboardBackendNav = {
    attach: function (context, settings) {
      $('.nav.nav-tabs li').mouseenter(function () {
        $(this).find('ul').show();
      });
      $('.nav.nav-tabs li').mouseleave(function () {
        $(this).find('ul').hide();
      });
    } // attach.function
  } // drupal.behaviors
})(jQuery);

(function ($) {
  Drupal.behaviors.springboardMisc = {
    attach: function (context, settings) {

      // Add uniform to selects
//      $("select").uniform();

      // Add uniform to file upload.
      $('input[type=file]').uniform();

      // Limit label width to match its form element
      $('.form-item label').each(function() {
        var id = $(this).attr('for');
        var type = $('#' + id).attr('type');
        if(type != undefined && $('#' + id).is(":visible")) {
          var types = ['radio', 'checkbox'];
          if(!type.indexOf(types)) {
            $(this).width($('#' + id).width());
          }
        }
      });

      // Set ul depths for better theming.
      $('#footer ul, #menu-wrapper ul').each(function () {
        var depth = $(this).parents('ul').length;
        $(this).addClass('ul-depth-' + depth);
      });

      // Set ul > li depths for better theming.
      $('ul.nav li').each(function () {
        var depth = $(this).parents('li').length;
        $(this).addClass('li-depth-' + depth);
      });

      // Set li > a depths for better theming.
      $('ul.nav li a').each(function () {
        var depth = $(this).parents('ul').length;
        $(this).addClass('lia-depth-' + depth);
      });

      // Add numbering to DSR groups.
      $('#edit-start-date .control-group').each(function (i) {
        $(this).addClass("grp-" + i);
      });

      $('#edit-end-date .control-group').each(function (i) {
        $(this).addClass("grp-" + i);
      });

      // Add first  / last classes for better theming.
      $(".content table tr td:visible:first-child").addClass("first");
      $(".content table tr td:visible:last-child").addClass("last");
      $(".content table tr td a:visible:first-child").addClass("first");
      $(".content table tr td a:visible:last-child").addClass("last");
      $(".content table th:visible:first-child").addClass("first");
      $(".content table th:visible:last-child").addClass("last");
      $(".types-wrapper:visible:first-child").addClass("first");
      $(".types-wrapper:visible:last-child").addClass("last");

      // Move the footer home link to the end.
      $('.nav-footer li.home').appendTo('.nav-footer li.options ul');

      // Remove the nav caret from menus.
      $('.nav .caret').remove();

      // Remove Boostrap button class.
      $('input').removeClass('btn');

      // Put focus on username field on login form.
      $("#user-login #edit-name").focus();

      // Wrap in fieldset-legend to match others.
      $('fieldset.webform-submission-info legend').wrapInner('<span class="fieldset-legend"></span>');

      // Add an inner wrappers in order to truncate.

      $('.webform-results-wrapper th').each(function () {
        $(this).wrapInner('<div class="th-wrapper"></div>');
      });

      // Add a body class for SF connection status.
        if ($('.sf-status p').hasClass('sf-connected')){
          $('body').addClass('sf-connected-dashboard');
        }
      else {
          $('body').addClass('sf-not-connected-dashboard');
        }

      // Remove empty pre tags that were rendered by drupal.
      $("pre:empty").remove();

      // for each element that is classed as 'valign-bottom',
      // set its margin-top to the difference between its
      // own height and the height of its parent
      $('.valign-bottom').each(function() {
        $(this).css('margin-top', $(this).parent().height()-$(this).height())
      });

      // Theme the feed icon wrapper.
      $('.feed-icon-wrapper img').each(function (i, ele) {
        var alt = this.alt;
      $(this).after("<span " + "class='img-caption'>" + this.alt + "</span>");
        $(this).parent('a').addClass('views-data-export');
        $(this).remove();
      });

      // Add a class to the views forms if they fields have labels.
      $('.view-filters form').each(function () {
        if ($(this).find('label').length > 0) {
          $(this).addClass('with-labels');
        }
      });

      // end.
    } // attach.function
  } // drupal.behaviors
})(jQuery);
