(function($) {
  var callback = {
    exec:function(editor) {
      // get the current path as an array
      var parts = location.pathname.split('/');
      if (parts[1] == 'node' && parts[3] == 'webform') {
        var token = window.showModalDialog("/webform/confirmation-token-list/"+parts[2],null,"dialogWidth:450px;dialogHeight:320px;center:yes; resizable: yes; help: no");
        if (token != false && token != null) {
          editor.insertHtml(token);
        }
      }
      else {
        alert('This only works for webform confirmations');
      }
    }
  },

  /**
   * Adds a CKEditor plugin to insert <pre> tags.
   *
   * This is heavily based on blog posts by:
   *
   * Nikolay Ulyanitsky
   * http://blog.lystor.org.ua/2010/11/ckeditor-plugin-and-toolbar-button-for.html
   *
   * and
   *
   * Peter Petrik
   * http://peterpetrik.com/blog/ckeditor-and-geshi-filter
   */
  buttonName = 'webform-tokens';
  CKEDITOR.plugins.add(buttonName, {
    init: function (editor) {
      // Create a new CKEditor style to add <pre> tags.
      //var buttonName = b;


      // Add the command and the button to the editor.
      editor.addCommand(buttonName, callback);
      editor.ui.addButton(buttonName, {
        label: Drupal.t('Confirmation page tokens'),
        icon: this.path + 'webform-tokens.png',
        command: buttonName
      });
    }
  });

})(jQuery);
