Drupal.behaviors.fundraiserGateway = {
  attach: function(context) { (function($) {
    $(document).ready(function() {
      $("#edit-submit").click(function(){
        return confirm("Please review your changes carefully. A misconfiguration can cause transactions to fail.\n\nAre you sure you want to proceed?");
      });

      var alreadyChecked = [];
      var recur = $(".offsite-recurring-checkbox");
      recurReset(recur, alreadyChecked);

      recur.change(function () {
        recur.prop('checked', false);
        if (alreadyChecked[this.id]) {
          $(this).prop('checked', false);
          recurReset(recur, alreadyChecked);
        }
        else {
          recurReset(recur, alreadyChecked);
          $(this).prop('checked', true);
          alreadyChecked[this.id] = true;
        }

      });
    });

    function recurReset(recur, alreadyChecked) {
      recur.each(function () {
        alreadyChecked[this.id] = false;
      });
    }

  })(jQuery);}
};
