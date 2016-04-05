<?php
/**
 * @file
 * pennyworth.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pennyworth_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function pennyworth_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function pennyworth_node_info() {
  $items = array(
    'release' => array(
      'name' => t('Release'),
      'base' => 'node_content',
      'description' => t('Details on each release of the platform. Each time a new commit is merged to the master branch, a release should be added here. Ex. <em>7.x-1.0-rc1</em>'),
      'has_title' => '1',
      'title_label' => t('Release version number'),
      'help' => '',
    ),
    'site' => array(
      'name' => t('Site'),
      'base' => 'node_content',
      'description' => t('A web site to be deployed in the az.gov infrastructure. Ex. <em>lottery</em>'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => t('Use this form to collect meta-data for the site. Saving this form will not deploy the site.
'),
    ),
    'site_environment' => array(
      'name' => t('Site Environment'),
      'base' => 'node_content',
      'description' => t('How a site gets deployed to a specific environment. This node contains the specific settings for that site in that environment. This is a join between <em>site</em> content type and <em>environment</em> taxonomy. Ex. <em>lottery.devaz.gov</em>'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'user' => array(
      'name' => t('User'),
      'base' => 'node_content',
      'description' => t('A user account which will be created in the deployed site. This content type contains only the global values for the user, not the specifics for each site. Those specifics are stored in the <em>User Environment</em> content type. Ex. <em>johndoe</em>'),
      'has_title' => '1',
      'title_label' => t('Username'),
      'help' => '',
    ),
    'user_environment' => array(
      'name' => t('User Environment'),
      'base' => 'node_content',
      'description' => t('Details on how the user will be deployed to a site. Each node indicates that a specific user is deployed to specific environments(s) in a specific site with specified role(s). This is essentially a join between <em>user</em> content type, <em>site</em> content type, <em>environment</em> taxonomy and <em>roles</em> taxonomy. Ex. <em>johndoe on lottery.devaz.gov</em>'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implements hook_default_rules_link().
 */
function pennyworth_default_rules_link() {
  $items = array();
  $items['deploy_users'] = entity_import('rules_link', '{
    "settings" : {
      "text" : "Deploy",
      "link_type" : "token",
      "bundles" : { "user_environment" : "user_environment" },
      "entity_link" : 1
    },
    "name" : "deploy_users",
    "label" : "Deploy Users",
    "path" : "deploy\\/user",
    "entity_type" : "node",
    "rdf_mapping" : []
  }');
  $items['initialize'] = entity_import('rules_link', '{
    "settings" : {
      "text" : "Initialize",
      "link_type" : "token",
      "bundles" : { "site_environment" : "site_environment" },
      "entity_link" : 1,
      "confirm_question" : "Are you sure?",
      "confirm_description" : ""
    },
    "name" : "initialize",
    "label" : "Initialize",
    "path" : "build\\/initialize",
    "entity_type" : "node",
    "rdf_mapping" : []
  }');
  $items['migrate'] = entity_import('rules_link', '{
    "settings" : {
      "text" : "Deploy",
      "link_type" : "token",
      "bundles" : { "site_environment" : "site_environment" },
      "entity_link" : 1,
      "confirm_question" : "Are you sure?",
      "confirm_description" : ""
    },
    "name" : "migrate",
    "label" : "Deploy",
    "path" : "build\\/deploy",
    "entity_type" : "node",
    "rdf_mapping" : []
  }');
  return $items;
}
