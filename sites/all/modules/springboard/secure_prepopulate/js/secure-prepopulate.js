(function($, Drupal)
{

/**
 * Drupal behavior.
 */
Drupal.behaviors.secureAutofill = {
  attach:function(context, settings)
  {
    $('body').once(function() {
      // Check for js cookie first, if it's in place then use it rather than GS.
      // Cookie is based on nid.
      var nid = getCurrentNodeId();
      var showWelcome = false;
      var global = settings.secure_prepopulate.secure_prepopulate_global_gift_strings;
      var globalExpireUTC = settings.secure_prepopulate.secure_prepopulate_dynamic_gift_strings_cookie_lifetime;
      var globalExpire = new Date();
      globalExpire.setTime(globalExpireUTC);
      var globalOmit = settings.secure_prepopulate.secure_prepopulate_gs_omit;
      var noSave = getParameterByName('nosave');

      if (noSave) {
        globalOmit = 1;
      }

      var gs = gsParam = getParameterByName('gs');

      if (gs != null) {
        // Set null value and get from php.
        var gsHash = null;
      }
      else {
        // First check if there's a gs for this nid.
        if (nid) {
          var gsCookie = $.cookie("gs-" + nid);
        }
        // Then check for the global gs.
        if (global && globalOmit != 1 && $.cookie("gs-global")) {
          var gsCookie = $.cookie("gs-global");
        }

        if (gsCookie) {
          var gs = gsCookie;
          // Get per-user hash.
          if (!global || globalOmit != 0) {
            var gsHash = $.cookie("gs-" + nid + '-hash');
          }
          else {
            var gsHash = $.cookie('gs-global-hash');
          }
        }
      }

      // Decrypt whichever value we chose to use above.
      if (gs != null && typeof(gsHash) !== 'undefined') {
        // Post GS to 'get_amounts' callback, assemble request params and respond.
        $.post( "/js/secure_prepopulate/get_amounts", {
          js_callback: "get_amounts",
          js_module: "secure_prepopulate",
          gs: gs,
          user_hash: gsHash
        }).done(function(data) {
          // If response code is successful, take action.
          if (data && data.response && data.response.code == 200 && data.content) {
            // Parse amounts and defaults into their appropriate fields.
            if (typeof(data.content.amounts) !== 'undefined') {
              // If this is a designations form, special handling of amounts.
              if ($('#webform-component-designations').length) {
                // Iterate through each designation group, unless overridden.
                $("div.designation-group-wrapper:not(.overridden)").each(function(){
                  // Replace amounts for each designation.

                  // Take the last amount form item, alter its label and value, and insert before the 'other' form item.
                  var lastAmount = $('[id^="default-amounts-"] .form-item', this).last().clone(true);
                  // Uncheck last amount.
                  $(lastAmount).children('input').attr('checked', false);

                  // Now remove all recurring regular options from the form.
                  $('[id^="default-amounts-"] .form-item', this).remove();

                  // Next, iterate and process amounts.
                  var amounts = data.content.amounts.split("|");
                  for (var i = 0, len = amounts.length; i < len; i++) {
                    // Set amount value.
                    $(lastAmount).children('input').val(amounts[i]);
                    // Set amount label, use appropriate currency.
                    if (Drupal.settings.fundraiser.currency.symbol) {
                      var symbol = Drupal.settings.fundraiser.currency.symbol;
                    }
                    else {
                      var symbol = "$";
                    }
                    $(lastAmount).children('label').text(symbol + amounts[i]);
                    // Set element ID and corresponding label.
                    $('input', lastAmount).attr('id', 'edit-submitted-designations-designation-box-1-default-amounts-1-' + amounts[i]);
                    $('label', lastAmount).attr('for', 'edit-submitted-designations-designation-box-1-default-amounts-1-' + amounts[i]);
                    // Insert after last amount.
                    $('[id^="default-amounts-"]', this).append(lastAmount);
                    // Show the new amount.
                    $(lastAmount).show();
                    // Reset last amount.
                    var lastAmount = $('[id^="default-amounts-"] .form-item', this).last().clone(true);
                    // Uncheck last amount.
                    $(lastAmount).children('input').attr('checked', false);
                  }

                });
              } else if (($('input[name*=recurs_monthly]').attr("type") != "hidden") || ($('input[name*=recurs_monthly]').attr("type") == "hidden" && $('input[name*=recurs_monthly]').val() != "recurs")) {
                // Find and replace amount.
                // If this is a user choice form with or without dual ask, set amounts.
                // If this is a one-time-only form, set amounts. Don't set amounts for recurring-only forms.
                var amounts = data.content.amounts.split("|");
                setAmounts(amounts);
                // End handling for non-designation amounts.
              }
            // End handling for amounts.
            }

            // Set 'default' amount.
            if (typeof(data.content.default) !== 'undefined') {
              // If this is a designations form, special handling of amounts.
              if ($('#webform-component-designations').length) {
                // Replace the designation default amount for each designations item.
                // Iterate through each designation group, unless overridden.
                $("div.designation-group-wrapper:not(.overridden)").each(function(){
                  // Get the default amount as returned and attempt to set it for each designation.
                  var amounts = $('[id^="default-amounts-"] .form-item input:visible', this);
                  // Iterate through amounts, set value if possible.
                  for (var i = 0, len = amounts.length; i < len; i++) {
                    if (amounts[i].value == data.content.default) {
                      // Uncheck all other values first.
                      $('[id^="default-amounts-"] .form-item input', this).attr('checked', false);
                      // Now set ours.
                      $(amounts[i]).attr('checked', 'checked');
                    }
                  }
                });
              }
              else if (($('input[name*=recurs_monthly]').attr("type") != "hidden") || ($('input[name*=recurs_monthly]').attr("type") == "hidden" && $('input[name*=recurs_monthly]').val() != "recurs")) {
                // Find and replace amount.
                // If this is a user choice form with or without dual ask, set default.
                // If this is a one-time-only form, set default. Don't set default for recurring-only forms.
                setRegularDefault(data.content.default);
                // End handling for non-designation default.
              }
            }

            // Set recurring ask amounts.
            if (typeof(data.content.recurring_amounts) !== 'undefined') {
              // If this is a designations form, special handling of amounts.
              if ($('#webform-component-designations').length) {
                // Iterate through each designation group, unless overridden.
                $("div.designation-group-wrapper:not(.overridden)").each(function(){
                  // Replace amounts for each designation.

                  // Take the last amount form item, alter its label and value, and insert before the 'other' form item.
                  var lastAmount = $('[id^="recurring-amounts-"] .form-item', this).last().clone(true);
                  // Uncheck last amount.
                  $(lastAmount).children('input').attr('checked', false);

                  // Now remove all recurring regular options from the form.
                  $('[id^="recurring-amounts-"] .form-item', this).remove();

                  // Next, iterate and process amounts.
                  var recurring_amounts = data.content.recurring_amounts.split("|");
                  for (var i = 0, len = recurring_amounts.length; i < len; i++) {
                    // Set amount value.
                    $(lastAmount).children('input').val(recurring_amounts[i]);
                    // Set amount label, use appropriate currency.
                    if (Drupal.settings.fundraiser.currency.symbol) {
                      var symbol = Drupal.settings.fundraiser.currency.symbol;
                    }
                    else {
                      var symbol = "$";
                    }
                    $(lastAmount).children('label').text(symbol + recurring_amounts[i]);
                    // Set element ID and corresponding label.
                    $('input', lastAmount).attr('id', 'edit-submitted-designations-designation-box-1-recurring-amounts-1-' + recurring_amounts[i]);
                    $('label', lastAmount).attr('for', 'edit-submitted-designations-designation-box-1-recurring-amounts-1-' + recurring_amounts[i]);
                    // Insert after last amount.
                    $('[id^="recurring-amounts-"]', this).append(lastAmount);
                    // Show the new amount.
                    $(lastAmount).show();
                    // Reset last amount.
                    var lastAmount = $('[id^="recurring-amounts-"] .form-item', this).last().clone(true);
                    // Uncheck last amount.
                    $(lastAmount).children('input').attr('checked', false);
                  }

                });
              }
              else {
                // Begin handling of non-designation recurring amounts.
                // Get amounts from return.
                var amounts = data.content.recurring_amounts.split("|");
                // If this is a one-time-only form, take no action.
                // If this is a user choice form without dual ask, take no action.
                // If this is a user choice form with dual ask, set the recurring amounts.
                if ($('input[name*=recurs_monthly]').attr("type") != "hidden" && $("div[id^=edit-submitted-][id$=recurring-amount] input:first").val() != '') {
                  setRecurringAmounts(amounts);
                } else if ($('input[name*=recurs_monthly]').attr("type") == "hidden" && $('input[name*=recurs_monthly]').val() == "recurs") {
                  // If this is a recurring-only form, set the regular amounts.
                  setAmounts(amounts);
                }
                // End handling for non-designation recurring amounts.
              }
            }

            // Set recurring default.
            if (typeof(data.content.recurring_default) !== 'undefined') {
              // If this is a designations form, special handling of amounts.
              if ($('#webform-component-designations').length) {
                // Replace the designation recurring default amount for each designations item.
                // Iterate through each designation group, unless overridden.
                $("div.designation-group-wrapper:not(.overridden)").each(function(){
                  // Get the recurring amount as returned and attempt to set it.
                  var recurring_amounts = $('[id^="recurring-amounts-"] .form-item input', this);
                  // Iterate through amounts, set value if possible.
                  for (var i = 0, len = recurring_amounts.length; i < len; i++) {
                    if (recurring_amounts[i].value == data.content.recurring_default) {
                      // Uncheck all other values first.
                      $('[id^="recurring-amounts-"] .form-item input', this).attr('checked', false);
                      // Now set ours.
                      $(recurring_amounts[i]).attr('checked', 'checked');
                    }
                  }
                });
              }
              else {
                // If this is a one-time-only form, take no action.
                // If this is a user choice form without dual ask, take no action.
                // If this is a user choice form with dual ask, set the recurring default amount.
                if ($('input[name*=recurs_monthly]').attr("type") != "hidden" && $("div[id^=edit-submitted-][id$=recurring-amount] .form-type-radio:first input").val() != '') {
                  setRecurringDefault(data.content.recurring_default);
                } else if ($('input[name*=recurs_monthly]').attr("type") == "hidden" && $('input[name*=recurs_monthly]').val() == "recurs") {
                  // If this is a recurring-only form, set the regular default amount.
                  setRegularDefault(data.content.recurring_default);
                }
              }
            }

            // Try to read "last submitted value cookie," if it's present and there are errors, set that value as default.
            if ($('div.error').length > 0) {
              selectedCookie = $.cookie('gs-' + nid + '-selected');
              if (selectedCookie && ($.isNumeric(selectedCookie) || selectedCookie === "other")) {
                setRegularDefault(selectedCookie);
                setRecurringDefault(selectedCookie);
              }
            }

            if (nid && gs && gsParam) {
                // Set GS cookie if it wasn't before.
                // This cookie will expire at end of session.
                $.cookie("gs-" + nid, gs, {path: '/'});
                // Set the per-user hash.
                if (data.content.userhash) {
                  $.cookie("gs-" + nid + "-hash", data.content.userhash, {path: '/'});
                }
               if (global && !noSave) {
                $.cookie("gs-global", gs, {expires: globalExpire, path: '/'});
                // Set the per-user hash.
                if (data.content.userhash) {
                  $.cookie("gs-global-hash", data.content.userhash, {expires: globalExpire, path: '/'});
                }
              }
            }
            else if(gs && gsParam && global && !noSave) {
              $.cookie("gs-global", gs, {expires: globalExpire, path: '/'});
              // Set the per-user hash.
              if (data.content.userhash) {
                $.cookie("gs-global-hash", data.content.userhash, {expires: globalExpire, path: '/'});
              }
            }

            // After adding the new amount form items re-run behaviors.
            Drupal.attachBehaviors();
          // End data check.
          }

        // End response handler.
        });
      // End
      }

      // Handle secure prepopulate querystring.
      // Check for js cookie first, if it's in place then use it rather than af.
      // Cookie is based on nid.
      if (nid) {
        var afCookie = $.cookie("af-" + nid);
      }
      if (!afCookie) {
        // Get af from URL if it wasn't in our cookie.
        var af = getParameterByName('af');
        if (af) {
          // Set to null so this hash can be set server-side.
          var afHash = null;
        }
      }
      else {
        var af = afCookie;
        // Get per-user hash.
        var afHash = $.cookie("af-" + nid + '-hash');
      }

      // Decrypt whichever value we chose to use above.
      if (typeof(af) !== 'undefined' && typeof(afHash) !== 'undefined') {
        // Post af to 'get_amounts' callback, assemble request params and respond.
        $.post( "/js/secure_prepopulate/get_values", {
          js_callback: "get_values",
          js_module: "secure_prepopulate",
          af: af,
          user_hash: afHash
        }).done(function(data) {
          // If response code is successful, take action.
          if (data && data.response && data.response.code == 200 && data.content) {
            // Set secure_prepop_autofilled field.
            $('input[name*=secure_prepop_autofilled]').val(true);

            // Show welcome message with link to 'not me'
            showWelcome = true;

            // Iterate through returned object and populate appropriate fields.
            for (var key in data.content) {
              if (data.content.hasOwnProperty(key)) {
                // Email is keyed as "email", but appears on donation forms as "mail".
                if (key === "email") {
                  $("input[name*='\[mail\]']").val(data.content[key]);
                }
                else {
                  // Populate input fields matching key with value returned from callback.
                  $("input[name*='\[" + key + "\]']").val(data.content[key]);
                  // Populate selects.
                  $("select[name*='\[" + key + "\]']").each(function(){
                    $('option[value="' + data.content[key] + '"]', this).prop('selected', true);
                  });
                  // Special handling for springboard form keys, which are prefixed with 'sbp_'
                  // Populate input fields matching key with value returned from callback.
                  $("input[name*='\[" + 'sbp_' + key + "\]']").val(data.content[key]);
                  // Populate selects.
                  $("select[name*='\[" + 'sbp_' + key + "\]']").each(function(){
                    $('option[value="' + data.content[key] + '"]', this).prop('selected', true);
                  });
                  // TODO handle select fields, radios, and checkboxes.
                }

                // Set welcome message from drupal.settings.
                if (key === "first_name" && showWelcome === true && nid) {
                  var firstName = data.content[key];
                  var markup = Drupal.settings.secure_prepopulate.secure_prepopulate_not_me;
                  // Replace FIRSTNAME with first name.
                  markup = markup.replace(/FIRSTNAME/g, firstName);
                  $('form.webform-client-form').before(markup);
                  // Special handling for 'not me' link.
                  $('#notme').click(function(event) {
                    event.preventDefault();
                    if (typeof(nid) !== 'undefined') {
                      // Clear af and gs cookies if they're set.
                      if (typeof($.cookie('af-' + nid) !== 'undefined')) {
                        $.cookie('af-' + nid, null, { path: '/' });
                      }
                      // Unset user hash.
                      if (typeof($.cookie('af-' + nid + '-hash') !== 'undefined')) {
                        $.cookie('af-' + nid + '-hash', null, { path: '/' });
                      }
                      // Unset gift string hash.
                      if (typeof($.cookie('gs-' + nid) !== 'undefined')) {
                        $.cookie('gs-' + nid, null, { path: '/' });
                      }
                      // Unset gift string hash.
                      if (typeof($.cookie('gs-global') !== 'undefined')) {
                        $.cookie('gs-global', null, { path: '/' });
                      }
                      // Unset user hash.
                      if (typeof($.cookie('gs-' + nid + '-hash') !== 'undefined')) {
                        $.cookie('gs-' + nid + '-hash', null, { path: '/' });
                      }
                      if (typeof($.cookie('gs-' + nid + '-selected') !== 'undefined')) {
                        $.cookie('gs-' + nid + '-selected', null, { path: '/' });
                      }
                      if (typeof($.cookie('gs-global-hash') !== 'undefined')) {
                        $.cookie('gs-' + nid + '-hash', null, { path: '/' });
                      }
                      // Remove querystring from url.
                      window.location = window.location.pathname;
                    }
                  });
                }
              }
            }

            if (nid && !afCookie && af && !afHash) {
              // Set af cookie if it wasn't before.
              // This cookie will expire at end of session.
              $.cookie("af-" + nid, af, { path: '/' });
              // Set the per-user hash.
              if (data.content.userhash) {
                $.cookie("af-" + nid + "-hash", data.content.userhash, { path: '/' });
              }
            }

          // End data check.
          }
        // End response handler.
        });
      }
    });

      // Helper function to override amounts component.
      function setAmounts(amounts) {
        // Find and replace amount.
        // Take last form item, alter its label and value, and insert before the 'other' form item.
        var lastAmount = $('div[id^=edit-submitted-][id$=amount]:not([id$=recurring-amount]) .form-type-radio').last().clone(true);
        // Uncheck last amount.
        $(lastAmount).children('input').attr('checked', false);

        // Remove all regular options from the form.
        $('div[id^=edit-submitted-][id$=amount]:not([id$=recurring-amount]) .form-type-radio').remove();

        // If the last amount's value is 'other', add it back to the end of the form item.
        if ($('input', lastAmount).val() == 'other') {
          var otherAmount = $(lastAmount).clone(true);
        }

        for (var i = 0, len = amounts.length; i < len; i++) {
          // Set amount value.
          $(lastAmount).children('input').val(amounts[i]);
          // Set amount label, use appropriate currency.
          if (typeof(Drupal.settings.fundraiser) !== "undefined" && typeof(Drupal.settings.fundraiser.currency) !== "undefined" && typeof(Drupal.settings.fundraiser.currency.symbol) !== "undefined") {
            var symbol = Drupal.settings.fundraiser.currency.symbol;
          }
          else {
            var symbol = "$";
          }
          $(lastAmount).children('label').text(symbol + amounts[i]);

          // Set element ID.
          var oldId = $('input', lastAmount).attr('id').split('-');
          oldId.splice(-1,1);
          oldId = oldId.join('-');
          var newId = oldId  + '-' + i;
          $('input', lastAmount).attr('id', newId);

          var oldLabel = $('label', lastAmount).attr('for').split('-');
          oldLabel.splice(-1,1);
          oldLabel = oldLabel.join('-');
          var newLabel = oldLabel + '-' + i;
          $('label', lastAmount).attr('for', newLabel);

          // Insert after last amount.
          $('div[id^=edit-submitted-][id$=amount]:not([id$=recurring-amount])').append(lastAmount);
          // Show the new amount.
          $(lastAmount).show();
          // Reset last amount.
          var lastAmount = $('div[id^=edit-submitted-][id$=amount]:not([id$=recurring-amount]) .form-item').last().clone(true);
          // Uncheck last amount.
          $(lastAmount).children('input').attr('checked', false);
        }

        // If we have an other amount, append it now.
        if (typeof(otherAmount) !== "undefined") {
          // Set element ID.
          var oldId = $('input', otherAmount).attr('id').split('-');
          oldId.splice(-1,1);
          oldId = oldId.join('-');
          var newId = oldId + '-' + amounts.length;
          $('input', otherAmount).attr('id', newId);

          var oldLabel = $('label', otherAmount).attr('for').split('-');
          oldLabel.splice(-1,1);
          oldLabel = oldLabel.join('-');
          var newLabel = oldLabel  + '-' + amounts.length;
          $('label', otherAmount).attr('for', newLabel);

          $('div[id^=edit-submitted-][id$=amount]:not([id$=recurring-amount])').append(otherAmount);
        }
      }

      // Helper function to override recurring amounts.
      function setRecurringAmounts(recurring_amounts) {
        // Find and replace amount.
        // Take last form item, alter its label and value, and insert before the 'other' form item.
        var lastAmount = $('div[id^=edit-submitted-][id$=recurring-amount] .form-type-radio').last().clone(true);
        // Uncheck last amount.
        $(lastAmount).children('input').attr('checked', false);

        if (lastAmount.length > 0) {
          // Remove all recurring options from the form.
          $('div[id^=edit-submitted-][id$=recurring-amount] .form-type-radio').remove();

          // If the last amount's value is 'other', add it back to the end of the form item.
          if ($('input', lastAmount).val() == 'other') {
            var otherAmount = $(lastAmount).clone(true);
          }

          // Next, iterate and process amounts.
          for (var i = 0, len = recurring_amounts.length; i < len; i++) {
            // Set amount value.
            $(lastAmount).children('input').val(recurring_amounts[i]);
            // Set amount label, use appropriate currency.
            if (typeof(Drupal.settings.fundraiser) !== "undefined" && typeof(Drupal.settings.fundraiser.currency) !== "undefined" && typeof(Drupal.settings.fundraiser.currency.symbol) !== "undefined") {
              var symbol = Drupal.settings.fundraiser.currency.symbol;
            }
            else {
              var symbol = "$";
            }
            $(lastAmount).children('label').text(symbol + recurring_amounts[i]);

            // Set element ID.
            var oldId = $('input', lastAmount).attr('id').split('-');
            oldId.splice(-1,1);
            oldId = oldId.join('-') + '-' + i;
            var newId = oldId + i;
            $('input', lastAmount).attr('id', newId);

            var oldLabel = $('label', lastAmount).attr('for').split('-');
            oldLabel.splice(-1,1);
            oldLabel = oldLabel.join('-') + '-' + i;
            var newLabel = oldLabel + i;
            $('label', lastAmount).attr('for', newLabel);

            // Insert after last amount.
            $('div[id^=edit-submitted-][id$=recurring-amount]').append(lastAmount);
            // Show the new amount.
            $(lastAmount).show();
            // Reset last amount.
            var lastAmount = $('div[id^=edit-submitted-][id$=recurring-amount] .form-item').last().clone(true);
            // Uncheck last amount.
            $(lastAmount).children('input').attr('checked', false);
          }

          // If we have an other amount, append it now.
          if (typeof(otherAmount) !== "undefined") {
            // Set element ID.
            var oldId = $('input', otherAmount).attr('id').split('-');
            oldId.splice(-1,1);
            oldId = oldId.join('-');
            var newId = oldId + '-' + recurring_amounts.length;
            $('input', otherAmount).attr('id', newId);

            var oldLabel = $('label', otherAmount).attr('for').split('-');
            oldLabel.splice(-1,1);
            oldLabel = oldLabel.join('-');
            var newLabel = oldLabel  + '-' + recurring_amounts.length;
            $('label', otherAmount).attr('for', newLabel);

            $('div[id^=edit-submitted-][id$=recurring-amount]').append(otherAmount);
          }
        }

      }

      // Helper function to set regular default.
      function setRegularDefault(regular_default) {
        // Get the default amount as returned and attempt to set it.
        var amounts = $('div[id^=edit-submitted-][id$=-amount]:not([id$=recurring-amount]) .form-item input');
        // Iterate through amounts, set value if possible.
        for (var i = 0, len = amounts.length; i < len; i++) {
          if (amounts[i].value == regular_default) {
            // Uncheck all other values first.
            $('div[id^=edit-submitted-][id$=-amount]:not([id$=recurring-amount]) .form-item input').attr('checked', false);
            // Now set ours.
            $(amounts[i]).attr('checked', 'checked');
          }
        }
      }

      // Helper function to set recurring default.
      function setRecurringDefault(recurring_default) {
        // Get the recurring_default amount as returned and attempt to set it.
        var amounts = $('div[id^=edit-submitted-][id$=recurring-amount]:not([id$=donation-amount]) .form-item input');
        // Iterate through amounts, set value if possible.
        for (var i = 0, len = amounts.length; i < len; i++) {
          if (amounts[i].value == recurring_default) {
            // Uncheck all other values first.
            $('div[id^=edit-submitted-][id$=recurring-amount]:not([id$=donation-amount]) .form-item input').attr('checked', false);
            // Now set ours.
            $(amounts[i]).attr('checked', 'checked');
          }
        }
      }

      // Helper function to get url params.
      function getParameterByName(name, url) {
        if (!url) {
          url = window.location.href;
        }
        name = name.replace(/[\[\]]/g, "\\$&");
        var regex = new RegExp("[?&]" + name + "(=([^&#]*)|&|#|$)"),
            results = regex.exec(url);
        if (!results) return null;
        if (!results[2]) return '';
        return results[2].replace(/\+/g, " ");
      }


      // Helper function to get node id.
      function getCurrentNodeId() {
        var $body = $('body.page-node');
        if ( ! $body.length )
          return false;
        var bodyClasses = $body.attr('class').split(/\s+/);
        for ( i in bodyClasses ) {
          var c = bodyClasses[i];
          if ( c.length > 10 && c.substring(0, 10) === "page-node-" )
            return parseInt(c.substring(10), 10);
        }
        return false;
      }

    }
}

}(jQuery, Drupal));
