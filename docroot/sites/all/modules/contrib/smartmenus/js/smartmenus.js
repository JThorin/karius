/**
 * @file
 * smartmenus.settings.js
 */
(function($) {

  /**
   * jQuery Behaviors for Smartmenus.
   */
  Drupal.behaviors.smartmenus = {
    attach: function (context, settings) {

      $('.sm', context).once('smartmenus-behavior', function() { $(this).smartmenus(); });

      // https://www.smartmenus.org/docs/#menu-toggle-button
      $('.sm-menu-state', context).once('smartmenus-behavior', function() {
        var $mainMenuState = $(this);
        // animate mobile menu
        $mainMenuState.change(function(e) {
          var $menu = $('#' + this.id.slice(0, -6));
          if (this.checked) {
            $menu.hide().slideDown(250, function() { $menu.css('display', ''); });
          } else {
            $menu.show().slideUp(250, function() { $menu.css('display', ''); });
          }
        });
        // hide mobile menu beforeunload
        $(window).bind('beforeunload unload', function() {
          if ($mainMenuState[0].checked) {
            $mainMenuState[0].click();
          }
        });
      });
    }
  }

})(jQuery);
