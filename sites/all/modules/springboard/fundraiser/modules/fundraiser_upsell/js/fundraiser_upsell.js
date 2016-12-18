(function ($) {

    Drupal.theme.prototype.fundraiserUpsellModal = function () {
        var html = ''
        html += '  <div id="ctools-modal">';
        html += '    <div class="ctools-modal-content ' + Drupal.settings['fundraiser-upsell'].modalClass + '">'; // panels-modal-content
        html += '      <div class="modal-header">';
        html += '        <span id="modal-title" class="modal-title">&nbsp;</span>';
        html += '      </div>';
        html += '      <div id="modal-content" class="modal-content">';
        html += '      </div>';
        html += '    </div>';
        html += '  </div>';

        return html;
    };

    $('document').ready(function() {
       $('.ctools-modal-fundraiser-upsell').click();
    });

})(jQuery);


(function ($) {
    Drupal.behaviors.fundraiser_upsell = {
        attach: function (context, settings) {
            $('.ctools-close-modal.rejection', context).click(function() {

                if (typeof $.cookie !== 'undefined') {
                    // Get the days for the rejection cookie
                    var rejectionDays = Drupal.settings['fundraiser-upsell'].rejectionDays;
                    var exdate=new Date();
                    exdate.setDate(exdate.getDate() + rejectionDays);

                    var name = 'fundraiser_upsell_rejection';
                    var value = 1;
                    var path = '/';

                    if (typeof Drupal.settings.springboard.cookie_path !== 'undefined') {
                        path = Drupal.settings.springboard.cookie_path;
                    }

                    $.cookie(name, value, { path: path,  expires: exdate});
                }

            });

            $('.ctools-modal-content form', context).on('submit', function() {
               $('.ctools-close-modal', context).hide();
            });
        }
    }

})(jQuery);
