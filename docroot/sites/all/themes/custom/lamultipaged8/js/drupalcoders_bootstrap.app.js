/**
 * @file
 * Behaviors for the drupalcoders_bootstrap theme.
 */

(function ($, _, Drupal, drupalSettings) {
  'use strict';

  Drupal.behaviors.drupalcoders_bootstrap = {
    attach: function (context) {
    	
      //Dropdown Mobile Menu
      if($(window).innerWidth() < 768) {
        $('.expanded.dropdown').click(function() {
          $(this).children('ul').slideToggle(); // Change the the speed of the animation. 1000 = 1 second.
        });
      }
      // Fix toolbar top space load of the page.
      var toolbarTabOuterHeight = $('#toolbar-bar').find('.toolbar-tab').outerHeight() || 0;
      var toolbarTrayHorizontalOuterHeight = $('.is-active.toolbar-tray-horizontal').outerHeight() || 0;
      var topSpace = toolbarTabOuterHeight + toolbarTrayHorizontalOuterHeight;
      $('body').css({ 'padding-top': topSpace });
      // Added Icons to User Login Page
      $('.path-user .user-login-form .form-item-name label').before().html('<span class="glyphicon glyphicon-user" aria-hidden="true"></span> Username');
      $('.path-user .user-login-form .form-item-pass label').before().html('<span class="glyphicon glyphicon-lock" aria-hidden="true"></span> Password');

      }
  };
})(window.jQuery, window._, window.Drupal, window.drupalSettings);