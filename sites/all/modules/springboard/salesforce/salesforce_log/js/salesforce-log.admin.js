(function ($) {
  Drupal.behaviors.salesforce_log_expander = {
    attach: function (context, settings) {
      // override default options (also overrides global overrides)
      $('td.expander').expander({
        slicePoint:       80,
        preserveWords:    false,
        expandPrefix:     ' ',
        expandText:       '[...]',
        userCollapseText: '[^]',
        beforeExpand:  function() {
          if($(this).hasClass('views-field-sobject')) {
            $(this).find('pre').css('width','500px');
          }  
        },
        afterCollapse:  function() {
          var pre = $(this).parents('.views-field-sobject').find('pre');
          if(pre.length > 0) {
            pre.css('width', '150px');
          }
        },
      });
    }
  }
})(jQuery);
