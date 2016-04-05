<?php
/**
 * @file
 * pennyworth.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function pennyworth_default_rules_configuration() {
  $items = array();
  $items['rules_create_site_environments_for_each_site'] = entity_import('rules_config', '{ "rules_create_site_environments_for_each_site" : {
      "LABEL" : "Create Site Environments for each Site",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "site-environment" ],
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_insert--site" : { "bundle" : "site" } },
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "site" : "site" } } } }
      ],
      "DO" : [
        { "LOOP" : {
            "USING" : { "list" : [ "node:field-environments" ] },
            "ITEM" : { "environment_item" : "Environment Item" },
            "DO" : [
              { "entity_create" : {
                  "USING" : {
                    "type" : "node",
                    "param_type" : "site_environment",
                    "param_title" : "Ignore - Set by Node Auto Label",
                    "param_author" : [ "node:author" ]
                  },
                  "PROVIDE" : { "entity_created" : { "site_environment_created" : "Site Environment Created" } }
                }
              },
              { "data_set" : {
                  "data" : [ "site-environment-created:field-site" ],
                  "value" : [ "node" ]
                }
              },
              { "entity_query" : {
                  "USING" : {
                    "type" : "taxonomy_term",
                    "property" : "name",
                    "value" : [ "environment-item:name" ],
                    "limit" : "1"
                  },
                  "PROVIDE" : { "entity_fetched" : { "environment_term" : "Environment Term" } }
                }
              },
              { "data_set" : {
                  "data" : [ "site-environment-created:field-environment" ],
                  "value" : [ "environment-item" ]
                }
              },
              { "data_set" : {
                  "data" : [ "site-environment-created:field-initialized" ],
                  "value" : [ "0" ]
                }
              },
              { "entity_save" : { "data" : [ "site-environment-created" ], "immediate" : 1 } },
              { "drupal_message" : { "message" : "Site Environment \\u003Cem\\u003E[site-environment-created:title]\\u003C\\/em\\u003E has been created." } }
            ]
          }
        }
      ]
    }
  }');
  $items['rules_link_condition_deploy_users'] = entity_import('rules_config', '{ "rules_link_condition_deploy_users" : {
      "LABEL" : "Rules link: Deploy Users condition",
      "PLUGIN" : "and",
      "OWNER" : "rules",
      "USES VARIABLES" : { "node" : { "type" : "node", "label" : "node" } },
      "AND" : []
    }
  }');
  $items['rules_link_condition_initialize'] = entity_import('rules_config', '{ "rules_link_condition_initialize" : {
      "LABEL" : "Rules link: Initialize condition",
      "PLUGIN" : "and",
      "OWNER" : "rules",
      "USES VARIABLES" : { "node" : { "type" : "node", "label" : "node" } },
      "AND" : []
    }
  }');
  $items['rules_link_condition_migrate'] = entity_import('rules_config', '{ "rules_link_condition_migrate" : {
      "LABEL" : "Rules link: Migrate condition",
      "PLUGIN" : "and",
      "OWNER" : "rules",
      "USES VARIABLES" : { "node" : { "type" : "node", "label" : "node" } },
      "AND" : []
    }
  }');
  $items['rules_link_set_deploy_users'] = entity_import('rules_config', '{ "rules_link_set_deploy_users" : {
      "LABEL" : "Rules link: Deploy Users rules set",
      "PLUGIN" : "rule set",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "jenkins" ],
      "USES VARIABLES" : { "node" : { "type" : "node", "label" : "node" } },
      "RULES" : [
        { "RULE" : {
            "IF" : [
              { "node_is_of_type" : {
                  "node" : [ "node" ],
                  "type" : { "value" : { "user_environment" : "user_environment" } }
                }
              }
            ],
            "DO" : [
              { "jenkins_job_build" : {
                  "name" : "pennyworth_user",
                  "params" : "site=[node:field_site]\\r\\nenvironment=[node:field_environment]\\r\\nrole=[node:field_role]"
                }
              },
              { "drupal_message" : { "message" : "\\u003Cem\\u003E[node:field_user]\\u003C\\/em\\u003E deployed to \\u003Cem\\u003E[node:field_site].[node:field_environment]\\u003C\\/em\\u003E with role \\u003Cem\\u003E[node:field_role]\\u003C\\/em\\u003E." } },
              { "data_set" : { "data" : [ "node:field-last-migration" ], "value" : "now" } }
            ],
            "LABEL" : "Deploy User"
          }
        }
      ]
    }
  }');
  $items['rules_link_set_initialize'] = entity_import('rules_config', '{ "rules_link_set_initialize" : {
      "LABEL" : "Rules link: Initialize rules set",
      "PLUGIN" : "rule set",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "jenkins", "rb_misc" ],
      "USES VARIABLES" : { "node" : { "type" : "node", "label" : "node" } },
      "RULES" : [
        { "RULE" : {
            "PROVIDE" : {
              "entity_fetched" : { "parent_site" : "Parent Site" },
              "node" : { "latest_release" : "Latest release" },
              "entity_created" : { "comment_created" : "Created comment" }
            },
            "IF" : [
              { "node_is_of_type" : {
                  "node" : [ "node" ],
                  "type" : { "value" : { "site_environment" : "site_environment" } }
                }
              }
            ],
            "DO" : [
              { "entity_query" : {
                  "USING" : {
                    "type" : "node",
                    "property" : "nid",
                    "value" : [ "node:field-site:nid" ],
                    "limit" : "1"
                  },
                  "PROVIDE" : { "entity_fetched" : { "parent_site" : "Parent Site" } }
                }
              },
              { "jenkins_job_build" : {
                  "name" : "pennyworth",
                  "params" : "domain=[domain:value]\\r\\nsubdomain=[node:field_subdomain]\\r\\ncdn_basic_mapping=[node:field_cdn_basic_mapping]\\r\\ncdn_basic_mapping_https=[node:field_cdn_basic_mapping_https]\\r\\ngoogle_analytics=[node:field_google_analytics]"
                }
              },
              { "data_set" : { "data" : [ "node:field-initialized" ], "value" : 1 } },
              { "data_set" : { "data" : [ "node:field-last-migration" ], "value" : "now" } },
              { "rb_misc_action_views_load_node" : {
                  "USING" : { "view" : "latest_release|default" },
                  "PROVIDE" : { "node" : { "latest_release" : "Latest release" } }
                }
              },
              { "data_set" : { "data" : [ "node:field-release" ], "value" : [ "latest-release" ] } },
              { "entity_save" : { "data" : [ "node" ] } },
              { "entity_create" : {
                  "USING" : {
                    "type" : "comment",
                    "param_subject" : [ "node:title" ],
                    "param_node" : [ "node" ],
                    "param_author" : [ "site:current-user" ],
                    "param_comment_body" : { "value" : { "value" : "Build added to the queue.", "format" : "filtered_html" } }
                  },
                  "PROVIDE" : { "entity_created" : { "comment_created" : "Created comment" } }
                }
              },
              { "drupal_message" : { "message" : "Deployment build for \\u003Cem\\u003E[node:title]\\u003C\\/em\\u003E has been added to the build queue." } }
            ],
            "LABEL" : "Initialize Site"
          }
        }
      ]
    }
  }');
  $items['rules_link_set_migrate'] = entity_import('rules_config', '{ "rules_link_set_migrate" : {
      "LABEL" : "Rules link: Migrate rules set",
      "PLUGIN" : "rule set",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "jenkins", "rb_misc" ],
      "USES VARIABLES" : { "node" : { "type" : "node", "label" : "node" } },
      "RULES" : [
        { "RULE" : {
            "PROVIDE" : {
              "entity_created" : { "comment_created" : "Comment created" },
              "node" : { "latest_release" : "Latest release" }
            },
            "IF" : [
              { "node_is_of_type" : {
                  "node" : [ "node" ],
                  "type" : { "value" : { "site_environment" : "site_environment" } }
                }
              }
            ],
            "DO" : [
              { "jenkins_job_build" : {
                  "name" : "pennyworth",
                  "params" : "domain=[domain:value]\\r\\nsubdomain=[node:field_subdomain]\\r\\ncdn_basic_mapping=[node:field_cdn_basic_mapping]\\r\\ncdn_basic_mapping_https=[node:field_cdn_basic_mapping_https]\\r\\ngoogle_analytics=[node:field_google_analytics]"
                }
              },
              { "entity_create" : {
                  "USING" : {
                    "type" : "comment",
                    "param_subject" : "[node:title]",
                    "param_node" : [ "node" ],
                    "param_author" : [ "site:current-user" ],
                    "param_comment_body" : { "value" : { "value" : "Build added to the queue.", "format" : "filtered_html" } }
                  },
                  "PROVIDE" : { "entity_created" : { "comment_created" : "Comment created" } }
                }
              },
              { "data_set" : { "data" : [ "node:field-last-migration" ], "value" : "now" } },
              { "rb_misc_action_views_load_node" : {
                  "USING" : { "view" : "latest_release|default" },
                  "PROVIDE" : { "node" : { "latest_release" : "Latest release" } }
                }
              },
              { "data_set" : { "data" : [ "node:field-release" ], "value" : [ "latest-release" ] } },
              { "entity_save" : { "data" : [ "node" ] } },
              { "drupal_message" : { "message" : "Deployment build for \\u003Cem\\u003E[node:title]\\u003C\\/em\\u003E has been added to the build queue." } }
            ],
            "LABEL" : "Deploy Site"
          }
        }
      ]
    }
  }');
  $items['rules_redirect_to_releases_view_after_creating_a_release'] = entity_import('rules_config', '{ "rules_redirect_to_releases_view_after_creating_a_release" : {
      "LABEL" : "Redirect to Releases view after creating a release",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "redirect", "release" ],
      "REQUIRES" : [ "rules" ],
      "ON" : {
        "node_insert--release" : { "bundle" : "release" },
        "node_update--release" : { "bundle" : "release" }
      },
      "DO" : [ { "redirect" : { "url" : "releases" } } ]
    }
  }');
  $items['rules_redirect_to_user_after_saving_user_environment'] = entity_import('rules_config', '{ "rules_redirect_to_user_after_saving_user_environment" : {
      "LABEL" : "Redirect to User after saving User Environment",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "user-environment" ],
      "REQUIRES" : [ "rules" ],
      "ON" : {
        "node_insert--user_environment" : { "bundle" : "user_environment" },
        "node_update--user_environment" : { "bundle" : "user_environment" }
      },
      "DO" : [ { "redirect" : { "url" : "user\\/[node:field_user]" } } ]
    }
  }');
  $items['rules_redirect_to_users_view_after_saving_user'] = entity_import('rules_config', '{ "rules_redirect_to_users_view_after_saving_user" : {
      "LABEL" : "Redirect to Users view after saving User",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "redirect", "user" ],
      "REQUIRES" : [ "rules" ],
      "ON" : {
        "node_insert--user" : { "bundle" : "user" },
        "node_update--user" : { "bundle" : "user" }
      },
      "DO" : [ { "redirect" : { "url" : "users" } } ]
    }
  }');
  $items['rules_return_to_site_after_editing_site_environment'] = entity_import('rules_config', '{ "rules_return_to_site_after_editing_site_environment" : {
      "LABEL" : "Redirect to Site after saving Site Environment",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "site-environment" ],
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_update--site_environment" : { "bundle" : "site_environment" } },
      "DO" : [ { "redirect" : { "url" : "site\\/[node:field_site]" } } ]
    }
  }');
  return $items;
}
