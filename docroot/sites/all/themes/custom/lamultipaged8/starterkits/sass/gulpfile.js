var gulp = require('gulp'),
  sass = require('gulp-sass'),
  sourcemaps = require('gulp-sourcemaps'),
  cleanCss = require('gulp-clean-css'),
  postcss = require('gulp-postcss'),
  autoprefixer = require('autoprefixer'),
  gulpIf = require('gulp-if'),
  eslint = require('gulp-eslint'),
  imagemin = require('gulp-imagemin'),
  pngquant = require('imagemin-pngquant');

gulp.task('imagemin', function () {
  return gulp.src('src/images/*')
    .pipe(imagemin({
      progressive: true,
      svgoPlugins: [{removeViewBox: false}],
      use: [pngquant()]
    }))
    .pipe(gulp.dest('images/'));
});

gulp.task('sass', function () {
  return gulp.src(['src/scss/**/*.scss'])
    .pipe(sourcemaps.init())
    .pipe(sass().on('error', sass.logError))
    .pipe(postcss([ autoprefixer({ browsers: [
        'Chrome >= 35',
        'Firefox >= 38',
        'Edge >= 12',
        'Explorer >= 10',
        'iOS >= 8',
        'Safari >= 8',
        'Android 2.3',
        'Android >= 4',
        'Opera >= 12']})]))
    .pipe(sourcemaps.write())
    .pipe(cleanCss())
    .pipe(gulp.dest('css/'));
});

function isFixed(file) {
  // Has ESLint fixed the file contents?
  return file.eslint != null && file.eslint.fixed;
}

gulp.task('eslint', function(){
  gulp.src(['src/js/*.js'])
    .pipe(eslint({
      fix: true,
    }))
    .pipe(eslint.format())
    // if fixed, write the file to dest
    .pipe(gulpIf(isFixed, gulp.dest('js/')));
});

gulp.task('watch', ['sass', 'eslint'],function(){

  gulp.watch('src/scss/**/*.scss', ['sass']);
  gulp.watch('src/js/**/*.js', ['eslint']);

});