const gulp = require("gulp");
const sass = require("gulp-sass");
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
        input: "src/styles/**/*.scss",
        output: "dist/css/"
    },
    html: {
        input: "src/**/*.html",
        output: "dist/",
    },
    reload: "./dist"
};

function browserSync(done) {
    browser_sync.init({
        server: {baseDir: paths.reload},
        port: 8555
    });
    done();
}

function browserSyncReload(done) {
    browser_sync.reload();
    done();
}

function sassTask() {
    return gulp.src(paths.styles.input)
        .pipe(sass())
        .pipe(gulp.dest(paths.styles.output))
        .pipe(browser_sync.stream());
}

function htmlTask() {
    return gulp.src(paths.html.input)
        .pipe(gulp.dest(paths.html.output))
        .pipe(browser_sync.stream());
}

function scriptTask() {
    return gulp.src(paths.scripts.input)
        .pipe(gulp.dest(paths.scripts.output))
        .pipe(browser_sync.stream());
}

function clean() {
    return del([paths.output]);
}

function watchTask() {
    gulp.watch(paths.html.input, htmlTask);
    gulp.watch(paths.styles.input, sassTask);
    gulp.watch(paths.scripts.input, scriptTask);
}

const build = gulp.series(clean, gulp.parallel(htmlTask, sassTask, scriptTask));
const watch = gulp.parallel(watchTask, browserSync);

exports.build = build;
exports.watch = watch;
exports.default = build;