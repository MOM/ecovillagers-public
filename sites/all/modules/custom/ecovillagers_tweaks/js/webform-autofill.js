(function($) {
    Drupal.behaviors.springboard_cookie = {
        attach: function (context, settings) {
            $.ajax({
                url: '/springboard_cookie/js/regurgitate',
                success: function (data, status) {
                    function autofill(name, value) {
                        var jqElement = $('form.webform-client-form').find('*[name*="' + name + '"]');
                        if (jqElement.prop('tagName') == 'SELECT') {
                            jqElement.find('option[value=' + value + ']').attr('selected', true);
                        } else if (jqElement.prop('tagName') == 'INPUT') {
                            if (jqElement.val() == '') {
                                jqElement.val(value);
                            }
                        }
                    }
                    autofill('[mail]', data.email);
                    if (data.profile != null) for (var key in data.profile) {
                        autofill('[' + key + ']', data.profile[key]);
                        autofill('[sbp_' + key + ']', data.profile[key]);
                    }
                }
            });
        }
    };
})(jQuery);