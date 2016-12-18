/**
 * @file
 * Misc JQuery P2P scripts in this file.
 */
(function ($) {
  // Add drupal 7 code.
  Drupal.behaviors.p2pAddEdit = {
    attach: function (context, settings) {
// End drupal calls.

      // Add a class to the image widget wrapper.
      $('.image-widget.form-managed-file').each(function() {
      $(this).parent('.control-group').addClass('image-widget-wrapper');
      });

      // Hide the tabledrag text.
      $('.pane-node-field-p2p-campaign-images .tabledrag-toggle-weight-wrapper').hide();

      // Remove the panel seperator.
      $(".panel-separator").remove();

      // add the missing required date label.
      $('.admin-date-required .date-padding label').once(function() {
      $(this).append('<span class="form-required" title="This field is required.">*</span>');
      });

      // Add uniform to selects.
      $('select').once('p2p-select', function () {
        $(this).uniform();
      });

      // Add uniform to file upload.
      $('input[type=file]').once('p2-pfile', function () {
        $(this).uniform();
      });

        // Runs on Fundraising goal field
        $('#edit-field-p2p-personal-campaign-goal-und-0-value').blur(function(){
            var value = this.value;

            // If the value has length and includes at least one integer
            if (value.length > 0 && this.value.match(/\d/g)) {
                // if no period period
                if (!value.match(/\./)) {
                    // no decimals: strip all other chars, add decimal and 00
                    value = value.replace(/[^\d]+/g,'') + '.00';
                } else {
                    // Remove all non-integer/period chars
                    value = value.replace(/[^\d\.]+/g,'')
                        // make first decimal unique
                        .replace(/\./i,'-')
                        // replace subsequent decimals
                        .replace(/\./g,'')
                        // set first back to normal
                        .replace('-','.')
                        // match the last two digits, removing others
                        .match(/\d+\.\d{0,2}|\.\d{0,2}/);
                    var newValue = value[0];
                    if (newValue.match(/\.\d{2}/)) {
                    } else if (newValue.match(/\.\d{1}/)) {
                        value += '0';
                    } else {
                        value += '00';
                    }
                }
                this.value = value;
            }
        });

      // end jquery.
    }};
})
  (jQuery);
