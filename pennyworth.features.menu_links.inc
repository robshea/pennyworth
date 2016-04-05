<?php
/**
 * @file
 * pennyworth.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function pennyworth_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_releases:releases
  $menu_links['main-menu_releases:releases'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'releases',
    'router_path' => 'releases',
    'link_title' => 'Releases',
    'options' => array(
      'identifier' => 'main-menu_releases:releases',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: main-menu_sites:sites
  $menu_links['main-menu_sites:sites'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'sites',
    'router_path' => 'sites',
    'link_title' => 'Sites',
    'options' => array(
      'identifier' => 'main-menu_sites:sites',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: main-menu_users:users
  $menu_links['main-menu_users:users'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'users',
    'router_path' => 'users',
    'link_title' => 'Users',
    'options' => array(
      'identifier' => 'main-menu_users:users',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Releases');
  t('Sites');
  t('Users');


  return $menu_links;
}
