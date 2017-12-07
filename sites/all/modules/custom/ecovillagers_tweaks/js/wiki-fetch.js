/**
 * Utility function for use by content that includes it manually.
 * Pulls in WikiMedia content from the URI given in the query string
 * and inserts it into <div>s with matching IDs.
 */

(function($) {
    // Grab wiki URL from the querystring used to load wiki-fetch.js.
    // No need to wait for the page to load fully, since this callout will take a moment.
    if (WikiFetchURL != null) {
        $.ajax(WikiFetchURL).done(function(html) {
            // Make sure the page is fully loaded before we proceed.
            $(function(){
                // Throw the wiki page's body content into an offscreen container.
                $('body').append('<div id="wiki-fetch-body" style="display:none;">'
                    + html.split(/<\/?body.*>/)[1] + '</div>'
                );
                // Make sure all links are absolute and open in a new tab/window.
                var wikiDomain = WikiFetchURL.split(/\/+/)[1];
                $('#wiki-fetch-body a').each(function(){
                    var url = $(this).attr('href');
                    if (url != null) {
                        $(this).attr('target', '_blank');
                        if (!url.match(/^http/)) {
                            $(this).attr('href', 'https://' + wikiDomain + url);
                        }
                    }
                });
                // Scan the calling document for containers to fill with wiki page content.
                $('.wiki-fetch-section').each(function(){
                    var id = $(this).attr('id').substr(1);  // Throw away the leading character.
                    var jqElement = $(document.getElementById(id)).parent();
                    var headingTagName = jqElement.get(0).tagName;
                    var proceed = jqElement.length > 0;
                    var jqNextElement;
                    while (proceed) {
                        jqNextElement = jqElement.next();
                        proceed = elementIsInSection(jqNextElement, headingTagName);
                        $(this).append(jqElement);
                        jqElement = jqNextElement;
                    }
                });
                // Done. Throw out the offscreen container.
                $('#wiki-fetch-body').remove();
            });
        });
    }

    function elementIsInSection(jqElement, headingTagName) {
        if (jqElement.length > 0) {
            var elementTagName = jqElement.get(0).tagName;
            if (elementTagName.substr(0, 1) == 'H') {
                // Is this a subheading in our section, or the next section's heading?
                return parseInt(elementTagName.substr(1)) > parseInt(headingTagName.substr(1));
            } else {
                // Assume a non-heading element is part of our section's content.
                return true;
            }
        }
        return false;
    }

    function getQueryStringParam(sParam) {
        var sPageURL = window.location.search.substring(1);
        var sURLVariables = sPageURL.split('&');
        for (var i = 0; i < sURLVariables.length; i++) {
            var sParameterName = sURLVariables[i].split('=');
            if (sParameterName[0] == sParam) {
                return sParameterName[1];
            }
        }
    }

})(jQuery);