(function ($) {

Drupal.behaviors.pageWrappersAdmin = {
  attach: function (context) {
    $('a.remove-row', context).click(function(e) {
      e.preventDefault();
      $(this).closest('tr', context).fadeOut(function() {
        $(this).find('select.page-wrappers-wrapper-select', context).val(0);
        $('#edit-page-wrappers-more', context).click();
      });
    });
  }
};

})(jQuery);
