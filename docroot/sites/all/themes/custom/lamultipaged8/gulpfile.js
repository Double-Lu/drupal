const 
  devBuild = (process.env.NODE_ENV !== 'production'),

  // modules
  gulp = require('gulp'),
  noop = require('gulp-noop'),
  newer = require('gulp-newer'),
  imagemin = require('gulp-imagemin'),
  htmlclean = require('gulp-htmlclean'),
  concat = require('gulp-concat'),
  deporder = require('gulp-deporder'),
  terser = require('gulp-terser'),
  stripdebug = devBuild ? null : require('gulp-strip-debug'),
  sourcemaps = devBuild ? require('gulp-sourcemaps') : null,
  sass = require('gulp-sass'),
  postcss = require('gulp-postcss'),
  assets = require('postcss-assets'),
  autoprefixer = require('autoprefixer'),
  mqpacker = require('css-mqpacker'),
  cssnano = require('cssnano'),
  // cleanCss = require('gulp-clean-css'),
  // gulpIf = require('gulp-if'),
  // eslint = require('gulp-eslint'),
  // pngquant = require('imagemin-pngquant')
  
  src = 'src/',
  build = ''
  ;

 // image processing
function images() {

  const out = build + 'images/';

  return gulp.src(src + 'images/**/*')
    .pipe(newer(out))
    .pipe(imagemin({ optimizationLevel: 5 }))
    .pipe(gulp.dest(out));

};
exports.images = images;

// HTML processing
function html() {
  const out = build + 'html/';

  return gulp.src(src + 'html/**/*')
    .pipe(newer(out))
    .pipe(devBuild ? noop() : htmlclean())
    .pipe(gulp.dest(out));
};
exports.html = gulp.series(images, html);

// JavaScript processing
function js() {

  return gulp.src(src + 'js/**/*')
    .pipe(sourcemaps ? sourcemaps.init() : noop())
    .pipe(deporder())
    .pipe(concat('main.js'))
    .pipe(stripdebug ? stripdebug() : noop())
    .pipe(terser())
    .pipe(sourcemaps ? sourcemaps.write() : noop())
    .pipe(gulp.dest(build + 'js/'));

};
exports.js = js;

// CSS processing
function css() {

  return gulp.src(src + 'scss/**/*.scss') //was 'scss/main.scss'
    .pipe(sourcemaps ? sourcemaps.init() : noop())
    .pipe(sass({
      outputStyle: 'nested',
      imagePath: '/images/',
      precision: 3,
      errLogToConsole: true
    }).on('error', sass.logError))
    .pipe(postcss([
      assets({ loadPaths: ['images/'] }),
      autoprefixer({ browsers: ['last 2 versions', '> 2%'] }),
      mqpacker,
      cssnano
    ]))
    .pipe(sourcemaps ? sourcemaps.write() : noop())
    .pipe(gulp.dest(build + 'css/'));

};
exports.css = gulp.series(images, css);

// run all tasks
exports.build = gulp.parallel(exports.html, exports.css, exports.js);

// watch for file changes
function watch(done) {

  // image changes
  gulp.watch(src + 'images/**/*', images);

  // html changes
  gulp.watch(src + 'html/**/*', html);

  // css changes
  gulp.watch(src + 'scss/**/*', css);

  // js changes
  gulp.watch(src + 'js/**/*', js);

  done();

}
exports.watch = watch;

// default task
exports.default = gulp.series(exports.build, exports.watch);

// gulp.task('imagemin', function () {
//   return gulp.src('src/images/*')
//     .pipe(imagemin({
//       progressive: true,
//       svgoPlugins: [{removeViewBox: false}],
//       use: [pngquant()]
//     }))
//     .pipe(gulp.dest('images/'));
// });

// gulp.task('sass', function () {
//   return gulp.src(['src/scss/**/*.scss'])
//     .pipe(sourcemaps.init())
//     .pipe(sass().on('error', sass.logError))
//     .pipe(postcss([ autoprefixer({ browsers: [
//         'Chrome >= 35',
//         'Firefox >= 38',
//         'Edge >= 12',
//         'Explorer >= 10',
//         'iOS >= 8',
//         'Safari >= 8',
//         'Android 2.3',
//         'Android >= 4',
//         'Opera >= 12']})]))
//     .pipe(sourcemaps.write())
//     .pipe(cleanCss())
//     .pipe(gulp.dest('css/'));
// });

// function isFixed(file) {
//   // Has ESLint fixed the file contents?
//   return file.eslint != null && file.eslint.fixed;
// }

// gulp.task('eslint', function(){
//   gulp.src(['src/js/*.js'])
//     .pipe(eslint({
//       fix: true,
//     }))
//     .pipe(eslint.format())
//     // if fixed, write the file to dest
//     .pipe(gulpIf(isFixed, gulp.dest('js/')));
// });

// gulp.task('watch', ['sass', 'eslint'],function(){

//   gulp.watch('src/scss/**/*.scss', ['sass']);
//   gulp.watch('src/js/**/*.js', ['eslint']);

// });