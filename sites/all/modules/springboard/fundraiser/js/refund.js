Drupal.behaviors.enableAmountForPartialRefund = {
  attach: function(context) { (function($) {

  $('input[name=refund_type]:radio', context).bind('click', function() {
    amountBox = $('input[name=amount]:text', context);
    totalAmount = $('input[name=total_paid]:hidden', context).val();
    if (this.value == 'full') {
      amountBox.val(totalAmount);
      amountBox.attr('disabled','disabled');
    }
    else {
      amountBox.removeAttr('disabled');
      amountBox.val('');
    }
  });

  })(jQuery); }
}
