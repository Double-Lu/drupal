<?php

/**
 * @file
 * Drupal Bootstrap Drush commands.
 */

/**
 * Implements hook_drush_command().
 */
function drupalcoders_bootstrap_drush_command() {
  $items = [];
  $items['drupalcoders-bootstrap-sub-theme'] = [
    'description' => 'Create a DrupalCoders Bootstrap sub-theme',
    'aliases' => ['dc'],
    'arguments' => [
      'name'         => 'Your sub-theme name.',
      'machine_name' => 'A machine-readable name for your theme, optional only  [a-z, 0-9] ',
    ],
    'options' => [
      'description'  => 'Your sub-theme description.',
      'machine-name' => '[a-z, 0-9] A machine-readable name for your theme.',
    ],
    'examples' => [
      'drush dc "custom theme name"' => 'Create a sub-theme with the default options.',
      'drush dc "foo bar" "foo_bar"  --description="My supersweet awesome theme"' => 'Create a sub-theme with additional options.',
    ],
  ];

  return $items;
}

/**
 * Create a Boostrap sub-theme.
 */
function drush_drupalcoders_bootstrap_sub_theme($name = NULL, $machine_name = NULL, $description = NULL) {
  if (empty($name)) {
    drush_set_error(dt("Please provide a name for the sub-theme.\nUSAGE:\tdrush dc [name] [machine_name !OPTIONAL] [description !OPTIONAL]\n"));
    return;
  }
  // Filter everything but letters, numbers, underscores, and hyphens.
  $machine_name = !empty($machine_name) ? preg_replace('/[^a-z0-9_-]+/', '', strtolower($machine_name)) : preg_replace('/[^a-z0-9_-]+/', '', strtolower($name));
  // Eliminate hyphens.
  $machine_name = str_replace('-', '_', $machine_name);

  $bootstrap_path = drush_get_context('DRUSH_DRUPAL_ROOT') . '/' . drupal_get_path('theme', 'drupalcoders_bootstrap');
  $subtheme_path = explode('/', $bootstrap_path);
  array_pop($subtheme_path);
  $subtheme_path = implode('/', $subtheme_path) . '/' . $machine_name;

  // Make a fresh copy of the subtheme.
  $s = drush_copy_dir("$bootstrap_path/starterkits/sass", $subtheme_path);
  if (empty($s)) {
    return;
  }

  // Rename files and fill in the theme machine name.
  drush_op('rename', "$subtheme_path/THEMENAME.starterkit.yml", "$subtheme_path/$machine_name.info.yml");
  drush_op('rename', "$subtheme_path/THEMENAME.libraries.yml", "$subtheme_path/$machine_name.libraries.yml");
  drush_op('rename', "$subtheme_path/THEMENAME.theme", "$subtheme_path/$machine_name.theme");
  drush_op('rename', "$subtheme_path/config/install/THEMENAME.settings.yml", "$subtheme_path/config/install/$machine_name.settings.yml");
  drush_op('rename', "$subtheme_path/config/schema/THEMENAME.schema.yml", "$subtheme_path/config/schema/$machine_name.schema.yml");
  drush_op('rename', "$subtheme_path/js/THEMENAME.app.js", "$subtheme_path/js/$machine_name.app.js");
  drush_op('rename', "$subtheme_path/src/js/THEMENAME.app.js", "$subtheme_path/src/js/$machine_name.app.js");
  drush_op('rename', "$subtheme_path/src/scss/THEMENAME.style.scss", "$subtheme_path/src/scss/$machine_name.style.scss");
  drush_op('rename', "$subtheme_path/css/THEMENAME.style.css", "$subtheme_path/css/$machine_name.style.css");

  // Rename Config Optional Blocks.
  drush_op('rename', "$subtheme_path/config/optional/block.block.bootstrap_account_menu.yml", "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "account_menu.yml");
  drush_op('rename', "$subtheme_path/config/optional/block.block.bootstrap_branding.yml", "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "branding.yml");
  drush_op('rename', "$subtheme_path/config/optional/block.block.bootstrap_breadcrumbs.yml", "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "breadcrumbs.yml");
  drush_op('rename', "$subtheme_path/config/optional/block.block.bootstrap_content.yml", "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "content.yml");
  drush_op('rename', "$subtheme_path/config/optional/block.block.bootstrap_footer.yml", "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "footer.yml");
  drush_op('rename', "$subtheme_path/config/optional/block.block.bootstrap_help.yml", "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "help.yml");
  drush_op('rename', "$subtheme_path/config/optional/block.block.bootstrap_local_actions.yml", "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "local_actions.yml");
  drush_op('rename', "$subtheme_path/config/optional/block.block.bootstrap_local_tasks.yml", "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "local_tasks.yml");
  drush_op('rename', "$subtheme_path/config/optional/block.block.bootstrap_main_menu.yml", "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "main_menu.yml");
  drush_op('rename', "$subtheme_path/config/optional/block.block.bootstrap_messages.yml", "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "messages.yml");
  drush_op('rename', "$subtheme_path/config/optional/block.block.bootstrap_page_title.yml", "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "page_title.yml");
  drush_op('rename', "$subtheme_path/config/optional/block.block.bootstrap_powered.yml", "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "powered.yml");
  drush_op('rename', "$subtheme_path/config/optional/block.block.bootstrap_search.yml", "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "search.yml");
  drush_op('rename', "$subtheme_path/config/optional/block.block.bootstrap_tools.yml", "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "tools.yml");

  // Change Optional Bootstrap Blocks to the name of the theme.
  drush_op('drupalcoders_bootstrap_file_str_replace', "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "account_menu.yml", 'bootstrap', "$machine_name");
  drush_op('drupalcoders_bootstrap_file_str_replace', "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "branding.yml", 'bootstrap', "$machine_name");
  drush_op('drupalcoders_bootstrap_file_str_replace', "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "breadcrumbs.yml", 'bootstrap', "$machine_name");
  drush_op('drupalcoders_bootstrap_file_str_replace', "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "content.yml", 'bootstrap', "$machine_name");
  drush_op('drupalcoders_bootstrap_file_str_replace', "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "footer.yml", 'bootstrap', "$machine_name");
  drush_op('drupalcoders_bootstrap_file_str_replace', "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "help.yml", 'bootstrap', "$machine_name");
  drush_op('drupalcoders_bootstrap_file_str_replace', "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "local_actions.yml", 'bootstrap', "$machine_name");
  drush_op('drupalcoders_bootstrap_file_str_replace', "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "local_tasks.yml", 'bootstrap', "$machine_name");
  drush_op('drupalcoders_bootstrap_file_str_replace', "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "main_menu.yml", 'bootstrap', "$machine_name");
  drush_op('drupalcoders_bootstrap_file_str_replace', "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "messages.yml", 'bootstrap', "$machine_name");
  drush_op('drupalcoders_bootstrap_file_str_replace', "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "page_title.yml", 'bootstrap', "$machine_name");
  drush_op('drupalcoders_bootstrap_file_str_replace', "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "powered.yml", 'bootstrap', "$machine_name");
  drush_op('drupalcoders_bootstrap_file_str_replace', "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "search.yml", 'bootstrap', "$machine_name");
  drush_op('drupalcoders_bootstrap_file_str_replace', "$subtheme_path/config/optional/block.block.$machine_name" . '_' . "tools.yml", 'bootstrap', "$machine_name");

  // Change the name of the theme.
  drush_op('drupalcoders_bootstrap_file_str_replace', "$subtheme_path/$machine_name.info.yml", 'THEMETITLE', "$name");

  // Change the name of the theme.
  if (!empty($description)) {
    drush_op('drupalcoders_bootstrap_file_str_replace', "$subtheme_path/$machine_name.info.yml", 'Custom sub-theme, inherits from the Bootstrap base theme', $description);
  }

  // Replaces instances of THEMENAME in required files to name of the theme.
  drush_op('drupalcoders_bootstrap_file_str_replace', "$subtheme_path/$machine_name.info.yml", 'THEMENAME', "$machine_name");
  drush_op('drupalcoders_bootstrap_file_str_replace', "$subtheme_path/$machine_name.libraries.yml", 'THEMENAME', "$machine_name");
  drush_op('drupalcoders_bootstrap_file_str_replace', "$subtheme_path/$machine_name.theme", 'THEMENAME', "$machine_name");
  drush_op('drupalcoders_bootstrap_file_str_replace', "$subtheme_path/package.json", 'THEMENAME', "$machine_name");
  drush_op('drupalcoders_bootstrap_file_str_replace', "$subtheme_path/js/$machine_name.app.js", 'THEMENAME', "$machine_name");
  drush_op('drupalcoders_bootstrap_file_str_replace', "$subtheme_path/src/js/$machine_name.app.js", 'THEMENAME', "$machine_name");

  // Replaces instances of THEMENAME in required files to name of the theme.
  drush_op('drupalcoders_bootstrap_file_str_replace', "$subtheme_path/config/install/$machine_name.settings.yml", 'THEMENAME.settings', "$machine_name" . "." . "settings");
  drush_op('drupalcoders_bootstrap_file_str_replace', "$subtheme_path/config/schema/$machine_name.schema.yml", 'THEMETITLE', "$name");
  drush_print("Printing Theme Path");
  // Notify user of the newly created theme.
  drush_print(dt("\n!name sub-theme was created in !path. \n",
    [
      '!name' => $name,
      '!path' => $subtheme_path,
    ]
  ));
  drush_print("Clearing Cache");
  drush_cache_clear_all();
  drush_print("Rebuild Cache");
  drush_cache_rebuild();
  drush_pm_enable($machine_name);

}

/**
 * Internal helper: Replace strings in a file.
 */
function drupalcoders_bootstrap_file_str_replace($file_path, $find, $replace) {
  $file_contents = file_get_contents($file_path);
  $file_contents = str_replace($find, $replace, $file_contents);
  file_put_contents($file_path, $file_contents);
}

/**
 * Implements hook_drush_help().
 */
function drupalcoders_bootstrap_drush_help($section) {
  switch ($section) {
    case 'drush:bootstrap-sub-theme':
      return dt("Create a Boostrap custom sub-theme.");
  }
}
