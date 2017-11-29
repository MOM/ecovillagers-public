/**
 * @file
 * JS for Springbaord Data Warehouse Donation Detail page.
 */

Drupal.behaviors.springboardDataWarehouseOonationDetail = {
  attach: function(context) { (function($) {
    // Group similar fields on the DW donation detail display based on global text section label fields:
    var currentDWDetailGroup;
    var currentDWDetailGroupCount = 0;
    $('.view-springboard-dw-donations-report.dw-donation-detail .views-field').each(function () {
      if ($(this).hasClass('section-label')) {
        $(this).before('<div class="dw-detail-section dw-detail-section-num-' + currentDWDetailGroupCount + '"></div>');
        currentDWDetailGroup = $('.dw-detail-section-num-' + currentDWDetailGroupCount);
        currentDWDetailGroupCount++;
      }
      currentDWDetailGroup.append($(this));
    });
  })(jQuery); }
}
