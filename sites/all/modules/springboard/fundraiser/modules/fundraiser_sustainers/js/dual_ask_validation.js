(function($) {
  Drupal.behaviors.dualAskAmounts = {
    attach: function (context, settings) {
      $(window).ready(function(){
        // Other Amount
        if ($('input[name$="recurring_other_amount]"]')[0]) {
          $('input[name$="recurring_other_amount]"]').rules("add", {
            required: {
              depends: function(element) {
                if ($('input[type="radio"][name$="[recurring_amount]"][value="other"]:visible').is(":checked"))
                  return true;
                else
                  return false;
              }
            },
            amount: true,
            min: parseFloat(Drupal.settings.fundraiserWebform.recurring_minimum_donation_amount),
            messages: {
              required: "This field is required",
              amount: "Enter a valid amount",
              min: "The amount entered is less than the minimum donation amount."
            }
          });
        }
      }); // window.ready
    } // attach.function
  } // drupal.behaviors
})(jQuery);
