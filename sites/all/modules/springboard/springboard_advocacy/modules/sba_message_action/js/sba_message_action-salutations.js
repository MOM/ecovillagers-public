/**
 * @file
 * Dual salutations handling for user-facing message action webforms.
 */
(function ($) {

    $(document).ready(function () {
        // Use a hidden input to provide the sba_salutation_alternate value.
        $('*[name="submitted[sba_salutation_alternate]"]').attr('name', 'selectable_sba_salutation_alternate');
        $('#webform-component-sbp-salutation').append('<input type="hidden" name="submitted[sba_salutation_alternate]" value="" />');

        // Set the Alternate Salutation value and visibility now, and whenever either salutation changes.
        $('*[name="submitted[sbp_salutation]"]').change(setAlternateSalutationState);
        $('*[name="selectable_sba_salutation_alternate"]').change(setAlternateSalutationState);
        setAlternateSalutationState();
    });

    var setAlternateSalutationState = function() {
        var makeAlternateSalutationVisible = false;
        var preferredValue = $('*[name="submitted[sbp_salutation]"]').val();
        if (preferredValue == "") {
            // Preferred salutation isn't selected, so hold off on the Alternate Salutation select.
            $('input[name="submitted[sba_salutation_alternate]"]').val("");
        }
        else if ($('*[name=selectable_sba_salutation_alternate] option[value="' + preferredValue + '"]').length > 0) {
            // Preferred salutation matches an alternate option, so simply use that.
            $('*[name="submitted[sba_salutation_alternate]"]').val(preferredValue);
        }
        else {
            // Preferred salutation doesn't match an alternate option, so display the Alternate Salutation select.
            makeAlternateSalutationVisible = true;
            $('*[name="submitted[sba_salutation_alternate]"]').val(
                $('*[name="selectable_sba_salutation_alternate"]').val()
            );
        }
        if (makeAlternateSalutationVisible) {
            $('#webform-component-sba-salutation-alternate').show();
        } else {
            $('#webform-component-sba-salutation-alternate').hide();
        }
    }

})(jQuery);