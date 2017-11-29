(function ($) {
  Drupal.behaviors.alterSBVDonationsView = {
    attach: function (context, settings) {
      var donationsReportTable = $('.view-sbv-donations table.views-table, #sb-webform-results-override-wrapper .sb-webform-results-table table.views-table');
      // Remove collabsible fieldset from results tab view:
      $('#views-exposed-form-sbv-donations-page-2').insertBefore('.view-sbv-donations fieldset#webform-ui-exposed-search');
      $('#views-exposed-form-sb-generic-webform-results-page').insertBefore('.view-sb-generic-webform-results fieldset#webform-ui-exposed-search');
      $('#views-exposed-form-sb-action-submissions-results-page-1').insertBefore('.view-sb-action-submissions-results fieldset#webform-ui-exposed-search');
      $('.view-sbv-donations fieldset#webform-ui-exposed-search, .view-sb-generic-webform-results fieldset#webform-ui-exposed-search').remove();
      $('.view-sb-action-submissions-results fieldset#webform-ui-exposed-search').remove();

      // Attach help popup to the right of the submit button:
      var submitButton = $('#views-exposed-form-sbv-donations-page .views-submit-button input');
      submitButton.after('<span id="sb-db-donations-report-help"> <i class="fa fa-question-circle-o fa-lg"></i> </span>');
      $('#sb-db-donations-report-help').click(function (e) {
        e.preventDefault();
        if ($('#sb-db-donations-report-help-popup').length) {
          $('#sb-db-donations-report-help-popup').fadeOut('slow', function () {
            $('#sb-db-donations-report-help-popup').remove();
          });
        }
        else {
          $(this).after('<div id="sb-db-donations-report-help-popup" style="display:none;">' +
            'Use this form to view all donation data in the Drupal database.  ' +
            'Click on the columns to sort results or apply filters to the search and hit Go.  ' +
            'Clicking the download button queues export of a CSV file created based on your current seach filters;  ' +
            'you will receive an email alert when your custom report export is available for download.</div>');
          $('#sb-db-donations-report-help-popup').fadeIn('slow');
          $('#sb-db-donations-report-help-popup').click(function () {
            $('#sb-db-donations-report-help-popup').fadeOut('slow', function () {
              $('#sb-db-donations-report-help-popup').remove();
            });
          });
        }
      });

      // Rework presentation of the items per page element:
      var itemsPerPage = $('#views-exposed-form-sbv-donations-page #edit-items-per-page, #views-exposed-form-sbv-donations-page-2 #edit-items-per-page, ' +
        '.view-sb-generic-webform-results #edit-items-per-page, .view-sb-action-submissions-results #edit-items-per-page');
      itemsPerPage.parent().parent().hide();
      donationsReportTable.before('<div id="sb-db-items-per-page">Showing </div>');
      var optionCount = 0;
      var totalOptions = itemsPerPage.children().length;
      itemsPerPage.children().each(function () {
        var linkElementID = 'db-page-val-' + $(this).val();
        var linkElementValue = $(this).val();
        var pageValue = $(this).val();
        if ($(this).attr('selected') != 'selected') {
          pageLink = '<a href="#" id="' + linkElementID + '">' + linkElementValue + '</a>';
        }
        else {
          pageLink = linkElementValue;
        }
        $('#sb-db-items-per-page').append(pageLink + ' ');
        if ($(this).attr('selected') != 'selected') {
          $('#' + linkElementID).click(function (e) {
            e.preventDefault();
            itemsPerPage.val(linkElementValue);
            $('#views-exposed-form-sbv-donations-page, #views-exposed-form-sbv-donations-page-2, #views-exposed-form-sb-generic-webform-results-page, ' +
              '#views-exposed-form-sb-action-submissions-results-page-1').submit();
          });
        }
        if (optionCount < totalOptions - 1) {
          $('#sb-db-items-per-page').append('| ');
        }
        optionCount++;
      });
      $('#sb-db-items-per-page').append('per page');

      // Alter order status default option label:
      $('#views-exposed-form-sbv-donations-page #edit-status option[value="All"]').text('Any');

      // Alter sustainers donation ID (Recurs) filter:
      $('#views-exposed-form-sbv-donations-page #edit-master-did-op option').each(function() {
        if ($(this).text() == 'Regular expression') {
          $(this).text('Any');
          $(this).parent().prepend(($(this)));
        }
        else if ($(this).text() == 'Is empty (NULL)') {
          $(this).text('No');
        }
        else if ($(this).text() == 'Is not empty (NOT NULL)') {
          $(this).text('Yes');
          $(this).parent().append(($(this)));
        }
        else {
          $(this).remove();
        }
      });

      // Display search info as inline field value; hide if the field is used or the form is submitted:
      var searchFilter = $('#sb-webform-results-override-wrapper .form-item-keyword input, #views-exposed-form-sbv-donations-page .form-item-keyword input');
      /*
      var searchFilterBlurb = 'Search';
      if (searchFilter.val() == '') {
        searchFilter.val(searchFilterBlurb);
      }

      searchFilter.focus(function () {
        if ($(this).val() == searchFilterBlurb) {
          $(this).val('');
        }
      });
      searchFilter.blur(function () {
        if ($(this).val() == '') {
          $(this).val(searchFilterBlurb);
        }
      });
      $('#views-exposed-form-sb-generic-webform-results-page, #views-exposed-form-sbv-donations-page, #views-exposed-form-sbv-donations-page-2').submit(function () {
        if (searchFilter.val() == searchFilterBlurb) {
          searchFilter.val('');
        } else {
          searchFilter.val($.trim(searchFilter.val()));
        }
      }); */
      searchFilter.val($.trim(searchFilter.val()));

      // Turn enter-based form submit until submit button form submit:
      searchFilter.keydown(function (e) {
        if (e.keyCode == 13) { 
          e.preventDefault();
          submitButton.click();
        }
      });

      // Display internal name info as inline field value; hide if the field is used or the form is submitted:
      var internalFilter = $('#views-exposed-form-sbv-donations-page .form-item-field-fundraiser-internal-name-value input');
      var internalFilterBlurb = 'Internal Form Name';
      if (internalFilter.val() == '') {
        internalFilter.val(internalFilterBlurb);
      } 

      internalFilter.focus(function () {
        if ($(this).val() == internalFilterBlurb) {
          $(this).val('');
        }
      });
      internalFilter.blur(function () {
        if ($(this).val() == '') {
          $(this).val(internalFilterBlurb);
        }
      });
      $('#views-exposed-form-sbv-donations-page').submit(function () {
        if (internalFilter.val() == internalFilterBlurb) {
          internalFilter.val('');
        }
      });

      // Display order_id label as field value; hide on change or submit:
      var orderIDFilter = $('#views-exposed-form-sbv-donations-page-2 input#edit-order-id');
      var orderIDBlurb = 'Order ID';
      if (orderIDFilter.val() == '') {
        orderIDFilter.val(orderIDBlurb);
      }
      orderIDFilter.focus(function () {
        if ($(this).val() == orderIDBlurb) {
          $(this).val('');
        }
      });
      orderIDFilter.blur(function () {
        if ($(this).val() == '') {
          $(this).val(orderIDBlurb);
        }
      });
      $('#views-exposed-form-sbv-donations-page-2').submit(function () {
        if (orderIDFilter.val() == orderIDBlurb) {
          orderIDFilter.val('');
        }
      });

      // Display sid label as field value; hide on change or submit:
      var submIDFilter = $('#views-exposed-form-sbv-donations-page-2 input#edit-sid');
      var submIDBlurb = 'Submission ID';
      if (submIDFilter.val() == '') {
        submIDFilter.val(submIDBlurb);
      }
      submIDFilter.focus(function () {
        if ($(this).val() == submIDBlurb) {
          $(this).val('');
        }
      });
      submIDFilter.blur(function () {
        if ($(this).val() == '') {
          $(this).val(submIDBlurb);
        }
      });
      $('#views-exposed-form-sbv-donations-page-2').submit(function () {
        if (submIDFilter.val() == submIDBlurb) {
          submIDFilter.val('');
        }
      });

      // User ID inline label behavior:
      var subID2Filter = $('#views-exposed-form-sbv-donations-page-2 input#edit-uid-raw');
      var subID2Blurb = 'User ID';
      if (subID2Filter.val() == '') {
        subID2Filter.val(subID2Blurb);
      } 
      subID2Filter.focus(function () {
        if ($(this).val() == subID2Blurb) {
          $(this).val('');
        }
      });
      subID2Filter.blur(function () {
        if ($(this).val() == '') {
          $(this).val(subID2Blurb);
        }
      });
      $('#views-exposed-form-sbv-donations-page-2').submit(function () {
        if (subID2Filter.val() == subID2Blurb) {
          subID2Filter.val('');
        }
      });

      // Date picker inline labels:
      var dateFilterMinFilter = $('#sb-webform-results-override-wrapper input#edit-date-filter-min-datepicker-popup-0');
      var dateFilterMinBlurb = 'mm/dd/yyyy';
      if (dateFilterMinFilter.val() == '') {
        dateFilterMinFilter.val(dateFilterMinBlurb);
      }
      dateFilterMinFilter.focus(function () {
        if ($(this).val() == dateFilterMinBlurb) {
          $(this).val('');
        }
      });
      dateFilterMinFilter.blur(function () {
        if ($(this).val() == '') {
          $(this).val(dateFilterMinBlurb);
        }
      });
      $('#views-exposed-form-sb-generic-webform-results-page, #views-exposed-form-sbv-donations-page-2').submit(function () {
        if (dateFilterMinFilter.val() == dateFilterMinBlurb) {
          dateFilterMinFilter.val('');
        }
      });
      dateFilterMinFilter.keydown(function (e) {
        if(e.keyCode == 13){
          e.preventDefault();
        }
      });
      var dateFilterMaxFilter = $('#sb-webform-results-override-wrapper input#edit-date-filter-max-datepicker-popup-0');
      var dateFilterMaxBlurb = 'mm/dd/yyyy';
      if (dateFilterMaxFilter.val() == '') {
        dateFilterMaxFilter.val(dateFilterMaxBlurb);
      } 
      dateFilterMaxFilter.focus(function () { 
        if ($(this).val() == dateFilterMaxBlurb) {
          $(this).val('');
        }
      });
      dateFilterMaxFilter.blur(function () {
        if ($(this).val() == '') {
          $(this).val(dateFilterMaxBlurb);
        }
      });
      $('#views-exposed-form-sb-generic-webform-results-page, #views-exposed-form-sbv-donations-page-2').submit(function () {
        if (dateFilterMaxFilter.val() == dateFilterMaxBlurb) {
          dateFilterMaxFilter.val('');
        }
      });
      dateFilterMaxFilter.keydown(function (e) {
        if(e.keyCode == 13){
          e.preventDefault();
        }
      });

      var dateFilterMinPopupFilter = $('#views-exposed-form-sbv-donations-page input#edit-date-filter-min-datepicker-popup-0');
      var dateFilterMinPopupBlurb = 'mm/dd/yyyy';
      if (dateFilterMinPopupFilter.val() == '') {
        dateFilterMinPopupFilter.val(dateFilterMinPopupBlurb);
      }
      dateFilterMinPopupFilter.focus(function () {
        if ($(this).val() == dateFilterMinPopupBlurb) {
          $(this).val('');
        }
      });
      dateFilterMinPopupFilter.blur(function () {
        if ($(this).val() == '') {
          $(this).val(dateFilterMinPopupBlurb);
        }
      });
      $('#views-exposed-form-sbv-donations-page').submit(function () {
        if (dateFilterMinPopupFilter.val() == dateFilterMinPopupBlurb) {
          dateFilterMinPopupFilter.val('');
        }
      });
      var dateFilterMaxPopupFilter = $('#views-exposed-form-sbv-donations-page input#edit-date-filter-max-datepicker-popup-0');
      var dateFilterMaxPopupBlurb = 'mm/dd/yyyy';
      if (dateFilterMaxPopupFilter.val() == '') {
        dateFilterMaxPopupFilter.val(dateFilterMaxPopupBlurb);
      }
      dateFilterMaxPopupFilter.focus(function () {
        if ($(this).val() == dateFilterMaxPopupBlurb) {
          $(this).val('');
        }
      });
      dateFilterMaxPopupFilter.blur(function () {
        if ($(this).val() == '') {
          $(this).val(dateFilterMaxPopupBlurb);
        }
      });
      $('#views-exposed-form-sbv-donations-page').submit(function () {
        if (dateFilterMaxPopupFilter.val() == dateFilterMaxPopupBlurb) {
          dateFilterMaxPopupFilter.val('');
        }
      });

      // Next charge date filter
      var nextChMinFilter = $('#views-exposed-form-sbv-donations-page input#edit-next-charge-min-datepicker-popup-0');
      var nextChMinFilterBlurb = 'mm/dd/yyyy';
      if (nextChMinFilter.val() == '') {
        nextChMinFilter.val(nextChMinFilterBlurb);
      }
      nextChMinFilter.focus(function () {
        if ($(this).val() == nextChMinFilterBlurb) {
          $(this).val('');
        }
      });
      nextChMinFilter.blur(function () {
        if ($(this).val() == '') {
          $(this).val(nextChMinFilterBlurb);
        }
      });
      $('#views-exposed-form-sbv-donations-page').submit(function () {
        if (nextChMinFilter.val() == nextChMinFilterBlurb) {
          nextChMinFilter.val('');
        }
      });
      nextChMinFilter.keydown(function (e) {
        if(e.keyCode == 13){
          e.preventDefault();
          submitButton.click();
        }
      });
      var nextChMaxFilter = $('#views-exposed-form-sbv-donations-page input#edit-next-charge-max-datepicker-popup-0');
      var nextChMaxFilterBlurb = 'mm/dd/yyyy';
      if (nextChMaxFilter.val() == '') {
        nextChMaxFilter.val(nextChMaxFilterBlurb);
      }
      nextChMaxFilter.focus(function () {
        if ($(this).val() == nextChMaxFilterBlurb) {
          $(this).val(''); 
        }
      });
      nextChMaxFilter.blur(function () {
        if ($(this).val() == '') {
          $(this).val(nextChMaxFilterBlurb);
        } 
      });
      nextChMaxFilter.keydown(function (e) {
        if(e.keyCode == 13){
          e.preventDefault();
          submitButton.click();
        }
      });
      $('#views-exposed-form-sbv-donations-page').submit(function () {
        if (nextChMaxFilter.val() == nextChMaxFilterBlurb) {
          nextChMaxFilter.val('');
        }   
      });

      var nextChMinFilter2 = $('#views-exposed-form-sbv-donations-page input#edit-next-charge-min-datepicker-popup-0');
      var nextChMinFilter2Blurb = 'mm/dd/yyyy';
      if (nextChMinFilter2.val() == '') {
        nextChMinFilter2.val(nextChMinFilter2Blurb);
      }
      nextChMinFilter2.focus(function () {
        if ($(this).val() == nextChMinFilter2Blurb) {
          $(this).val('');
        }
      });
      nextChMinFilter2.blur(function () {
        if ($(this).val() == '') {
          $(this).val(nextChMinFilter2Blurb);
        }
      });
      $('#views-exposed-form-sbv-donations-page').submit(function () {
        if (nextChMinFilter2.val() == nextChMinFilter2Blurb) {
          nextChMinFilter2.val('');
        }
      });
      var nextChMaxFilter2 = $('#views-exposed-form-sbv-donations-page input#edit-next-charge-max-datepicker-popup-0');
      var nextChMaxFilter2Blurb = 'mm/dd/yyyy';
      if (nextChMaxFilter2.val() == '') {
        nextChMaxFilter2.val(nextChMaxFilter2Blurb);
      }
      nextChMaxFilter2.focus(function () {
        if ($(this).val() == nextChMaxFilter2Blurb) {
          $(this).val('');
        }
      });
      nextChMaxFilter2.blur(function () {
        if ($(this).val() == '') {
          $(this).val(nextChMaxFilter2Blurb);
        }
      });
      $('#views-exposed-form-sbv-donations-page').submit(function () {
        if (nextChMaxFilter2.val() == nextChMaxFilter2Blurb) {
          nextChMaxFilter2.val('');
        }
      });
      // End next charge date filter



      // Re-position the download link and add ajax callback when it is clicked; hide on no results:
      $(document).ready(function() {
        var downloadButton = $('.view-sbv-donations a.views-data-export');
        $('#sb-db-items-per-page').before('<span id="sbv-export-download-msg"></span>');
        downloadButton.click(function (e) {
          // Disabling csv download customization:
          return;

          $('#sbv-export-download-msg').text('Working...');
          // Gather data:
          if ($('.form-item-date-filter-min-date input').val() == 'mm/dd/yyyy') {
            $('.form-item-date-filter-min-date input').val('');
          }
          if ($('.form-item-date-filter-max-date input').val() == 'mm/dd/yyyy') {
            $('.form-item-date-filter-max-date input').val('');
          }
          if ($('.form-item-next-charge-min-date input').val() == 'mm/dd/yyyy') {
            $('.form-item-next-charge-min-date input').val('');
          }
          if ($('.form-item-next-charge-max-date input').val() == 'mm/dd/yyyy') {
            $('.form-item-next-charge-max-date input').val('');
          }
          if ($('#edit-field-fundraiser-internal-name-value').val() == 'Internal Form Name') {
            $('#edit-field-fundraiser-internal-name-value').val('');
          }
          var viewParams = {};
          viewParams['status'] = $('#views-exposed-form-sbv-donations-page #edit-status').val();
          downloadButton.hide();
          e.preventDefault();
          var isRecurringValue = $('.form-item-master-did-op #edit-master-did-op').val();
          if (isRecurringValue == 'not empty') {
            isRecurringValue = 'yes'; 
          } else if (isRecurringValue == 'empty') {
            isRecurringValue = 'no'; 
          } else {
            isRecurringValue = ''; 
          }
          var statusFilterValue = $('.view-sbv-donations #edit-status').val();
          if (statusFilterValue == 'All') {
            statusFilterValue = '';
          }
          
          $.ajax({
            type: 'POST',
            url: '/springboard-export-queue-ajax',
            dataType: 'json',
            data: {
              'status' : statusFilterValue,
              'internal_name' : $('#edit-field-fundraiser-internal-name-value').val(),
              'date_range_min' : $('.form-item-date-filter-min-date input').val(),
              'date_range_max' : $('.form-item-date-filter-max-date input').val(),
              'recurs' : isRecurringValue,
              'next_charge_min' : $('.form-item-next-charge-min-date input').val(),
              'next_charge_max' : $('.form-item-next-charge-max-date input').val(),
              'order' : Drupal.settings.sbViewDataOrder,
              'sort' : Drupal.settings.sbViewDataSort,
            },
            context: document.body,
            success: function(data) {
              if (data.status == 'success') {
                $('#sbv-export-download-msg').text('Your export has been queued; you will be emailed a download link when it is ready.');
              }
              else {
                $('#sbv-export-download-msg').text('Export failed.');
                alert('There was an error; the export file was not generated.');
              }
            }
          });
        });
        donationsReportTable.before(downloadButton);
        if ($('.view-empty').length) {
          downloadButton.hide();
        }
      });

      // Re-position the reset button:
      // var resetButton = $('#views-exposed-form-sbv-donations-page .views-reset-button');
      // submitButton.parent().before(resetButton);

      // Alter the results table action links:
      $('.view-sbv-donations table.views-table tbody tr').each(function () {
        var row = $(this);
        // Update actions:
        var status = row.children('.views-field-status').text();
        status = $.trim(status);
        if (status != 'Payment Received') {
          row.find('.table-actions .action-refund-link').hide();
          row.find('.table-actions .bar').hide();
        }

        // Link Yes/No recur value:
        order_id = row.find('.views-field-order-id-1 a').text();
        order_id = $.trim(order_id);
        recursField = row.children('.views-field-sustainer-key')
        recurs = $.trim(recursField.text());
      });
    }
  };
})(jQuery);

