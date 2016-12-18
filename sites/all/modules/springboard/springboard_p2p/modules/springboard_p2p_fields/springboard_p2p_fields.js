(function($) {
    Drupal.behaviors.springboardP2pFields = {
        attach: function(context) {
            $('.springboard_p2p_goal_type', context).on('change', function(e) {
                var $this = $(this);
                var $value = $this.closest('tr').find('.springboard_p2p_goal_value');
                var $prefix = $value.find('.field-prefix');
                var $suffix = $value.find('.field-suffix');

                switch ($this.val()) {
                    case 'submissions':
                        $prefix.text('');
                        $suffix.text(' submissions');
                        break;
                    case 'amount':
                        $prefix.text('$ ');
                        $suffix.text('');
                        break;
                    default:
                        $prefix.text('');
                        $suffix.text('');
                        break;
                }
            });
        }
    };
})(jQuery);
