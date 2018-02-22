(function ($, Drupal, window, document, undefined) {
  var Parallax = require('parallax-js');

  exports.init = function() {
	var scene = $('#scene');

	var parallaxInstance = new Parallax(scene.get(0), {
	});
  };
})(jQuery, Drupal, this, this.document);
