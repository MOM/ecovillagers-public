(function ($) {
  Drupal.behaviors.SBCustomExport = {
    attach: function (context, settings) {
      $(document).ready(function() {
        // Re-position the download link and add ajax callback when it is clicked; hide on no results:
        var donationsReportTable = $('table.views-table');
        var downloadButton = $('a.views-data-export');
        //var downloadButton = $('.view-content .feed-icon a');
        //$('#sb-db-items-per-page').before('<span id="sbv-export-download-msg"></span>');
        downloadButton.click(function (e) {
          e.preventDefault();
          $('#sb-db-items-per-page').hide();
          // Display email prompt after the download button:
          $(this).before('<div id="sb-export-wrapper">' +
            '<label>Enter your email address:</label><input type="email" id="sb-export-email" size="28" />' +
            '<input type="button" value="Queue Export" id="sb-export-queue" />' +
            '<input type="button" value="Cancel" id="sb-export-cancel" />' +
            '<div id="sb-export-descr">We will send a link to your file once the export is complete.</div><br />' +
            '</div>');
          downloadButton.hide();
          $('#sb-export-cancel').click(function () {
            $('#sb-export-wrapper').remove();
            $('#sb-db-items-per-page').show();
            downloadButton.show();
          });
          $('#sb-export-queue').click(function () {
            var validEmailPattern = /^([a-z\d!#$%&'*+\-\/=?^_`{|}~\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]+(\.[a-z\d!#$%&'*+\-\/=?^_`{|}~\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]+)*|"((([ \t]*\r\n)?[ \t]+)?([\x01-\x08\x0b\x0c\x0e-\x1f\x7f\x21\x23-\x5b\x5d-\x7e\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]|\\[\x01-\x09\x0b\x0c\x0d-\x7f\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]))*(([ \t]*\r\n)?[ \t]+)?")@(([a-z\d\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]|[a-z\d\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF][a-z\d\-._~\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]*[a-z\d\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])\.)+([a-z\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]|[a-z\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF][a-z\d\-._~\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]*[a-z\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])\.?$/i;
            if (!validEmailPattern.test($('#sb-export-email').val())) {
              alert('Please enter a valid email address.');
              return false;
            }
            $('#sb-export-descr').text('Working...');
            // Gather data:
            $.ajax({
              type: 'POST',
              url: '/springboard-export-queue-ajax',
              dataType: 'json',
              data: {
                'recipient_email' : $('#sb-export-email').val(),
                'export_data' : Drupal.settings.sBCustomViewsFileExportData
              },
              context: document.body,
              success: function(data) {
                if (data.status == 'success') {
                  alert('Your export is in the queue!' + "\n\n" + 'We will email you a link to the file when it is ready for download.');
                }
                else {
                  alert('There was an error; this export request failed.');
                }
                $('#sb-export-wrapper').remove();
                $('#sb-db-items-per-page').show();
                downloadButton.show();
              }
            });
          });
        });
        //donationsReportTable.before(downloadButton);
        if ($('.view-empty').length) {
          downloadButton.hide();
        }
      });
    }
  };
})(jQuery);
