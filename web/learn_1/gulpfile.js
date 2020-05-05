const gulp = require("gulp");
const sass = require("gulp-sass");
const pug = require("gulp-pug");
const del = require("del");
const browser_sync = require("browser-sync").create();

// const settings = {
//     clean: true,
//     scripts: true,
//     polyfills: false,
//     styles: true,
//     svgs: false,
//     copy: false,
//     reload: true
// };

const paths = {
    input: "src/",
    output: "dist/",
    scripts: {
      input: "src/scripts/**/*.js",
      output: "dist/scripts/"
    },
    styles: {
        input: "src/sass/**/*.sass",
        output: "dist/css/"
    },
    pug: {
        input: "src/**/*.pug",
        output: "dist/",
    },
    reload: "./dist"
};

function browserSync(done){
    browser_sync.init({
        server:{ baseDir: paths.reload },
        port: 8555
    });
    done();
}

function browserSyncReload(done){
    browser_sync.reload();
    done();
}

function sassTask(){
    return gulp.src(paths.styles.input)
        .pipe(sass())
        .pipe(gulp.dest(paths.styles.output))
        .pipe(browser_sync.stream());
}

function pugTask(){
    return gulp.src(paths.pug.input)
        .pipe(pug())
        .pipe(gulp.dest(paths.pug.output))
        .pipe(browser_sync.stream());
}

function scriptTask(){
    return gulp.src(paths.scripts.input)
        .pipe(gulp.dest(paths.scripts.output))
        .pipe(browser_sync.stream());
}

function clean(){
    return del([paths.output]);
}

function watchTask(){
    gulp.watch(paths.pug.input, pugTask);
    gulp.watch(paths.styles.input, sassTask);
    gulp.watch(paths.scripts.input, scriptTask);
}

const build = gulp.series(clean, gulp.parallel(pugTask, sassTask, scriptTask));
const watch = gulp.parallel(watchTask, browserSync);

exports.build = build;
exports.watch = watch;
exports.default = build;