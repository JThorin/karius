<?php
/**
 * @file
 * Smartmenus theme fnctions.
 */

/**
 * Theme function definition.
 */
function theme_smartmenus_menu($variables = array()) {
  // Build the menu.
  $tree = $variables['tree'];

  // Create menu attributes.
  $attributes = array (
    'id' => $variables['attributes']['id'],
    'class' => $class = implode(' ', array_filter($variables['attributes']['class'])),
  );

  // Add a menu toggle button.
  $output = '';
  if ($variables['toggle']) {
    $output .= theme('smartmenus_toggle', array('menu_id' => $variables['attributes']['id'], 'text' => t('Toggle main menu visibility')));
  }

  // Recursively build menu outpout.
  $menu_tree = smartmenus_format_menu_tree($tree, $attributes);
  $output .= drupal_render($menu_tree);

  return $output;
}

/**
 * Generate markup for the menu tree including special ID and classes.
 */
function theme_smartmenus_toggle($variables) {
  $menu_id = $variables['menu_id'];
  $text = $variables['text'];

  $output  = '<input id="' . $menu_id . '-state" class="sm-menu-state" type="checkbox" />';
  $output .= '<label class="sm-menu-btn" for="' . $menu_id . '-state">';
  $output .= '  <span class="sm-menu-btn-icon"></span> ' . $text;
  $output .= '</label>';

  return $output;
}

/**
 * Generate markup for the menu tree including special ID and classes.
 */
function theme_smartmenus_menu_tree($variables) {
  if (!empty($variables['attributes'])) {
    $id = $variables['attributes']['id'];
    $class = $variables['attributes']['class'];

    //$output  = '<div class="menu-button">' . t('Menu') . '</div>';
    $output = '<ul id="' . $id . '" class="' . $class . '">' . drupal_render($variables['tree']) . '</ul>';
  }
  else {
    $output = '<ul>' . drupal_render($variables['tree']) . '</ul>';
  }

  return $output;
}

/**
 * Reformat the menu tree.
 *
 * @param (array) $tree
 *   The fully rendered menu tree.
 * @param (array) $attributes
 *  Any additional attributes to be added.
 *
 * @return (array)
 *   Renderable array representing the menu tree.
 */
function smartmenus_format_menu_tree($tree, $attributes = NULL) {
  $items = array();
  foreach ($tree as $data) {
    if ($data['link']['access'] && !$data['link']['hidden']) {
      $items[] = $data;
    }
  }

  $build = array();
  $num_items = count($items);
  foreach ($items as $i => $item) {
    $class = array();

    if ($i == 0) {
      $class[] = 'first';
    }
    if ($i == $num_items - 1) {
      $class[] = 'last';
    }

    // Build link.
    $element['#theme'] = 'menu_link__' . strtr($item['link']['menu_name'], '-', '_');
    $element['#attributes']['class'] = $class;
    $element['#title'] = $item['link']['title'];
    $element['#href'] = $item['link']['href'];
    $element['#localized_options'] = !empty($item['link']['localized_options']) ? $item['link']['localized_options'] : array();
    $element['#original_link'] = $item['link'];

    // Recursively build menu output.
    if ($item['below']) {
      $element['#below'] = smartmenus_format_menu_tree($item['below']);
    } else {
      $element['#below'] = array();
    }

    // Return expected menu array.
    $build[$item['link']['mlid']] = $element;
  }

  $output = array();

  if ($build) {
    // Implement own menu wrapper.
    $output['#sorted'] = TRUE;
    $output['#tree'] = $build;
    $output['#attributes'] = $attributes;
    $output['#theme_wrappers'][] = 'smartmenus_menu_tree';
  }

  return $output;
}
