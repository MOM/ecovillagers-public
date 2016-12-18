$(document).ready(function() {
  //$('div.batch-item .batch-item-fields').hide();
  $('.dsr-order a.batch-viewer').click(function(e) {
    e.preventDefault();
    $(this).parent().parent().parent().parent().find('.dsr-batches').slideToggle('fast');
  });
});
