<?php
/**
 * @file
 * Smartmenus module settings.
 */

/**
 * Smartmenus settings form.
 */
function smartmenus_settings_form() {
  $form['container'] = array(
    '#type' => 'fieldset',
    '#title' => t('Smartmenus Settings'),
  );
  $form['container']['smartmenus_block_count'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of Smartmenu blocks'),
    '#size' => 10,
    '#default_value' => variable_get('smartmenus_block_count', 1),
    '#description' => t('Number of Smartmenu blocks available on the <a href="@url">blocks page</a>.', array(
      '@url' => url('admin/structure/block'),
    )),
  );
  $theme_options = array(
    '' => t('None'),
    'sm-blue' => t('Blue'),
    'sm-clean' => t('Clean'),
    'sm-mint' => t('Mint'),
    'sm-simple' => t('Simple'),
  );
  $form['container']['smartmenus_theme'] = array(
    '#type' => 'select',
    '#title' => t('Smart menus theme'),
    '#options' => $theme_options,
    '#default_value' => variable_get('smartmenus_theme', ''),
  );

  return system_settings_form($form);
}
