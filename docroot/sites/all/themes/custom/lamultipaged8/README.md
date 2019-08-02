<!-- @file Instructions for subtheming using the Sass Starterkit. -->
<!-- @defgroup sub_theming_sass -->
<!-- @ingroup sub_theming -->
# Sass Starterkit

Below are instructions on how to create a Bootstrap sub-theme using a Sass
preprocessor.

- [Prerequisites](#prerequisites)
- [Additional Setup](#setup)
- [Overrides](#overrides)

## Prerequisites

Do you like SCSS? Do you find it hard to start with Bootstrap SASS?

<h2>This theme will help you get started with SCSS Bootstrap in minutes.</h2>
<p><img src="/files/project-images/frontpage.png"></p>
<h3 id="project-description">What is DrupalCoders Bootstrap SASS ?</h3>
DrupalCoders Bootstrap SASS intends to improve bootstrap base theme:

1. Creating sub-theme using Drush
2. Adding compilers for SCSS .
3. Improving SCSS files.
4. Adding easy to read media queries.

Purpose of this theme is to easy add SASS sub-themes.

This theme is using Bootstrap as base theme.
<h3 id="project-requirements">Requirements</h3>
This theme is using Bootstrap as base theme, you need to download and enable it
before installing DrupalCoders theme.
<a href="http://drupal.org/project/bootstrap" rel="nofollow">Bootstrap Theme</a>

## Additional Setup {#setup}
<h3 id="project-installation">Installation</h3>
1. Install and enable the theme:
drush dl drupalcoders_bootstrap
drush en drupalcoders_bootstrap

2. Create a sub-theme using drush dc command: 
drush dc [theme-name]
Example:'drush dc mytheme'

4. Install node modules: 
cd/path/theme
npm install 

5. Compile and Watch SCSS files:
gulp

<h3 id="project-usage">Usage</h3>

Media Queries are changed to:

$mobile:           "screen and (max-width: #{$screen-xs-max})";
$tablet:            "screen and (min-width: #{$screen-sm-min})";
$tablet-only:     
"(min-width: #{$screen-sm-min}) and (max-width: #{$screen-sm-max})";
$normal:          "screen and (min-width: #{$screen-md-min})";
$normal-only:   
"(min-width: #{$screen-md-min}) and (max-width: #{$screen-md-max})";
$large:             "screen and (min-width: #{$screen-lg-min})";

In SCSS you can use it like @media #{$tablet} { } to help you style faster.

## Overrides {#overrides}
The `./THEMENAME/scss/_default-variables.scss` file is generally where you will
spend the majority of your time providing any default variables that should be
used by the [Bootstrap Framework] instead of its own.

The `./THEMENAME/scss/overrides.scss` file contains various Drupal overrides to
properly integrate with the [Bootstrap Framework]. It may contain a few
enhancements, feel free to edit this file as you see fit.

The `./THEMENAME/scss/style.scss` file is the glue that combines:
`_default-variables.scss`, [Bootstrap Framework Source Files] and the 
`overrides.scss` file together. Generally, you will not need to modify this
file unless you need to add or remove files to be imported. This is the file
that you should compile to `./THEMENAME/css/style.css` (note the same file
name, using a different extension of course).

#### See also:
- @link theme_settings Theme Settings @endlink
- @link templates Templates @endlink
- @link plugins Plugin System @endlink

[Bootstrap Framework]: http://getbootstrap.com
[Bootstrap Framework Source Files]: https://github.com/twbs/bootstrap-sass
[Sass]: http://sass-lang.com
