(function ($) {
    Drupal.behaviors.multstepFormSocial = {
        attach: function (context, settings) {
            //var editSubmit = $('#sba-social-action-preview-form').find('input[id*="edit-submit"]');
            //var send = $('#multiflow-send-now');

            //editSubmit.once(function() {
            //    editSubmit.click(function() {
            //        submitOnce(editSubmit, send, this);
            //    });
            //});

            //send.once(function() {
            //    send.click(function() {
            //        submitOnce(editSubmit, send, this);
            //        $('#sba-social-action-preview-form').submit();
            //        return false;
            //    });
            //});

            $(document).ready(function() {

                if (window.__twitterIntentHandler) return;
                var intentRegex = /twitter\.com\/intent\/(\w+)/,
                  windowOptions = 'scrollbars=yes,resizable=yes,toolbar=no,location=yes',
                  width = 550,
                  height = 420,
                  winHeight = screen.height,
                  winWidth = screen.width;

                function handleIntent(e) {
                    e = e || window.event;
                    var target = e.target || e.srcElement,
                      m, left, top;

                    while (target && target.nodeName.toLowerCase() !== 'a') {
                        target = target.parentNode;
                    }

                    if (target && target.nodeName.toLowerCase() === 'a' && target.href) {
                        m = target.href.match(intentRegex);
                        if (m) {
                            left = Math.round((winWidth / 2) - (width / 2));
                            top = 0;

                            if (winHeight > height) {
                                top = Math.round((winHeight / 2) - (height / 2));
                            }

                            var twitWin = window.open(target.href, 'intent', windowOptions + ',width=' + width +
                              ',height=' + height + ',left=' + left + ',top=' + top);
                            twitWin.focus();
                            //var twitInterval = window.setInterval(function(){
                            //    if (twitWin.closed) {
                            //        window.clearInterval(twitInterval);
                            //        ///ajax callback
                            //        console.log('f');
                            //    }
                            //}, 500);
                            e.returnValue = false;
                            e.preventDefault && e.preventDefault();
                        }
                    }
                }

                if (document.addEventListener) {
                    document.addEventListener('click', handleIntent, false);
                } else if (document.attachEvent) {
                    document.attachEvent('onclick', handleIntent);
                }
                window.__twitterIntentHandler = true;

                //$text = $('div[id*="edit-messages"]').find('textarea');
                //var navKeys = [33,34,35,36,37,38,39,40];
                //$text.each(function(){
                //    var desc = $(this).siblings('.description');
                //    $(this).closest('.control-group').prepend(desc);
                //
                //      $(this).once(function() {
                //
                //        var handleCount = $(this).closest('.control-group').siblings('.sba-full-tweet').find('.preview-target-text').text().length + 1;
                //
                //        $('#' + this.id).simplyCountable({
                //            counter:            $(this).siblings('.description').find('.counter'),
                //            countType:          'characters',
                //            maxCount:           140 - handleCount,
                //            strictMax:          true,
                //            countDirection:     'down',
                //            safeClass:          'safe',
                //            overClass:          'over',
                //            thousandSeparator:  ',',
                //            onOverCount:        function(count, countable, counter){},
                //            onSafeCount:        function(count, countable, counter){
                //            },
                //            onMaxCount:         function(count, countable, counter){}
                //        });
                //
                //        var screenName = $(this).closest('.control-group').siblings('.sba-full-tweet').find('.preview-target-text').text();
                //
                //        var newText;
                //        var defaultText = screenName + ' ' +  $(this).val();
                //        $(this).closest('.control-group').siblings('.sba-full-tweet').find('.editable-message-preview').text(screenName + ' ' +  $(this).val());
                //
                //        $(this).on('keyup blur paste', function(e) {
                //            switch(e.type) {
                //                case 'keyup':
                //                    if ($.inArray(e.which, navKeys) < 0) {
                //                        replacer(screenName, $(this));
                //                    }
                //                    break;
                //                case 'paste':
                //                    setTimeout(replacer(screenName, $(this)), (e.type === 'paste' ? 5 : 0));
                //                    break;
                //                default:
                //                    replacer(screenName, $(this));
                //                    break;
                //            }
                //        });
                //    })
                //})
            });

        } // attach.function
    } // drupal.behaviors


    //var replacer = function(screenName, element) {
    //    newText = screenName + ' ' + element.val().replace(/\r?\n/g, '<br>');
    //    element.closest('.control-group').siblings('.sba-full-tweet').find('.editable-message-preview').html(newText);
    //};

    $(document).ready(function () {

        //$('textarea').each(function (e) {
        //    $(this).height(this.scrollHeight)
        //});
        //$('label').has('.form-required').addClass('required');

        $('.twitter-sign').click(function(){
            $.oauthpopup({
                path: '/sba/twitter/login',
                callback: function(success){
                    if(typeof success != 'undefined' && success) {
                        $('#edit-ajaxify').trigger('mousedown');
                    }
                    else {
                       $('#sba-social-action-preview-form').prepend('<div class="alert error"><button type="button" class="close" data-dismiss="alert">×</button>Twitter authorization failed. Web site access token is missing.</div>');
                    }
                }
            });
            return false;
        });
    });

    //function submitOnce(editSubmit, send, clicked) {
    //
    //    if($('#sba-social-action-preview-form')[0].checkValidity) {
    //        if($('#sba-social-action-preview-form')[0].checkValidity()) {
    //            editSubmit.hide();
    //            var link = send.replaceWith('<span id="multiflow-send-now-processed">send now</span>');
    //            if (clicked.id == 'multiflow-send-now') {
    //                rotate();
    //            }
    //            editSubmit.after('<div class="webform-user-wrapper">' +
    //              '<p class="webform-user-thank-you">Thank you, your submission is processing.</p>' +
    //              '<div class="webform-user-spinner"></div>' +
    //              '</div>');
    //        }
    //    }
    //    else {
    //        editSubmit.hide();
    //        var link = send.replaceWith('<span id="multiflow-send-now-processed">send now</span>');
    //        if (clicked.id == 'multiflow-send-now') {
    //            rotate();
    //        }
    //        editSubmit.after('<div class="webform-user-wrapper">' +
    //          '<p class="webform-user-thank-you">Thank you, your submission is processing.</p>' +
    //          '<div class="webform-user-spinner"></div>' +
    //          '</div>');
    //    }
    //}
    //function rotate(num) {
    //    num = typeof num !== 'undefined' ? num : 10;
    //    $('#multiflow-send-now-wrapper').css({ 'transform': 'rotate(' + num + 'deg)'});
    //    var spinner = setTimeout(function() { rotate(num+10); }, 10);
    //    if (num >= 360) {
    //        clearTimeout(spinner);
    //    }
    //}

})(jQuery);