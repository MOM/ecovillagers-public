(function ($) {
    $(document).ready(function(){
        var message_wrapper = $('#edit-submission').find('.text-format-wrapper');
        message_wrapper.append($('#confirmation-div'));
        message_wrapper.append($('#edit-help'));
        message_wrapper.wrap('<fieldset class="webform-ui-fieldset message-fieldset collapsible collapsed"><div class="fieldset-wrapper"></div></fieldset>');
        var message_fieldset = $('.webform-ui-fieldset');
        message_fieldset.prepend('<a href="#" class="fieldset-title webform-ui-fieldset-title"></span>Confirmation messages</a></legend>');

        var submission_wrapper = $('#edit-total-submit-limit');
        submission_wrapper.wrap('<fieldset class="webform-ui-fieldset submission-fieldset collapsible collapsed"><div class="fieldset-wrapper"></div></fieldset>');
        $('.submission-fieldset .fieldset-wrapper').append($('#edit-submit-limit'));
        var sub_fieldset = $('.submission-fieldset');
        sub_fieldset.prepend('<a href="#" class="fieldset-title webform-ui-fieldset-title"></span>Submission limits</a></legend>');

        var redirection_wrapper = $('#edit-redirection');
        redirection_wrapper.wrap('<fieldset class="webform-ui-fieldset redirection-fieldset collapsible collapsed"><div class="fieldset-wrapper"></div></fieldset>');
        var redir_fieldset = $('.redirection-fieldset');
        redir_fieldset.prepend('<a href="#" class="fieldset-title webform-ui-fieldset-title"></span>Redirection settings</a></legend>');

        $(".webform-ui-fieldset-title").click(function () {
            fieldset = $(this).parent();
            wrapper = $(this).siblings('.fieldset-wrapper');
            if(fieldset.hasClass('collapsed')) {
                wrapper.slideDown({
                    duration: '400',
                    easing: 'linear',
                    complete: function () {
                        Drupal.collapseScrollIntoView(wrapper);
                        wrapper.animating = false;
                    },
                    step: function () {
                        fieldset.removeClass('collapsed');
                        Drupal.collapseScrollIntoView(wrapper);
                    }
                });
            }
            else {
                wrapper.slideUp('fast', function () {
                    fieldset.addClass('collapsed');
                    fieldset.animating = false;
                });
            }
            return false;
        });
    });
})(jQuery);