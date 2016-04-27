(function ($) {

  Drupal.behaviors.exampleModule = {
    attach: function (context, settings) {

	  //Functions for hiding data an pid popups

	  $( '.removepids').click(function() {
		  var pathid = $(this).attr('pathid');
 		  $(this).replaceWith('<div id="allpathpids-' + pathid + '"></div>' );

          });

	  $( '.removemissingpids').click(function() {
		  var pathid = $(this).attr('pathid');
 		  $(this).replaceWith('<div id="missingallpathpids-' + pathid + '"></div>' );

          });

	  $( '.removedataelements').click(function() {
		  var pathid = $(this).attr('pathid');
 		  $(this).replaceWith('<div id="pathdata-' + pathid + '"></div>' );

          });

    }
  };
  
}(jQuery));