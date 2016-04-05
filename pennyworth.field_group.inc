<?php
/**
 * @file
 * pennyworth.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function pennyworth_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_cdn|node|site_settings|form';
  $field_group->group_name = 'group_cdn';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'site_environment';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_site_environment';
  $field_group->data = array(
    'label' => 'CDN',
    'weight' => '9',
    'children' => array(
      0 => 'field_cdn_basic_mapping',
      1 => 'field_cdn_basic_mapping_https',
    ),
    'format_type' => 'accordion-item',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_cdn|node|site_settings|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_google|node|site_environment|form';
  $field_group->group_name = 'group_google';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'site_environment';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_site_environment';
  $field_group->data = array(
    'label' => 'Google',
    'weight' => '10',
    'children' => array(
      0 => 'field_google_analytics',
    ),
    'format_type' => 'accordion-item',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-google field-group-accordion-item',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_google|node|site_environment|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_required|node|site_environment|form';
  $field_group->group_name = 'group_required';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'site_environment';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_site_environment';
  $field_group->data = array(
    'label' => 'Site and Environment',
    'weight' => '8',
    'children' => array(
      0 => 'field_site',
      1 => 'field_environment',
      2 => 'field_initialized',
      3 => 'field_last_migration',
      4 => 'title',
      5 => 'field_release',
    ),
    'format_type' => 'accordion-item',
    'format_settings' => array(
      'label' => 'Site and Environment',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-required field-group-accordion-item',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_required|node|site_environment|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_site_environment|node|site_environment|form';
  $field_group->group_name = 'group_site_environment';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'site_environment';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Site Environment',
    'weight' => '0',
    'children' => array(
      0 => 'group_cdn',
      1 => 'group_required',
      2 => 'group_google',
    ),
    'format_type' => 'accordion',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'effect' => 'none',
        'classes' => 'group-site-environment field-group-accordion',
      ),
    ),
  );
  $export['group_site_environment|node|site_environment|form'] = $field_group;

  return $export;
}
