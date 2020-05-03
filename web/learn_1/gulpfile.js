const gulp = require("gulp");
const sass = require("gulp-sass");
const pug = require("gulp-pug");
const browser_sync = require("browser-sync").create();

const SASS_SRC = "src/sass/**/*.+(sass|scss)";
const PUG_SRC = "src/**/*.pug";
const JS_SRC = "src/script/**/*.js";

gulp.task("sass", function(){
    return gulp.src(SASS_SRC)
        .pipe(sass())
        .pipe(gulp.dest("build/css"))
        .pipe(browser_sync.reload({
            stream: true
        }));
});

gulp.task("pug", function(){
    return gulp.src(PUG_SRC)
        .pipe(pug())
        .pipe(gulp.dest("build/"))
        .pipe(browser_sync.reload({
            stream: true
        }));
});

gulp.task("js", function(){
    return gulp.src(JS_SRC)
        .pipe(gulp.dest("build/script"))
        .pipe(browser_sync.reload({
            stream: true
        }));
});

gulp.task("browser_sync", function(){
    browser_sync.init({
        server: {
            baseDir: "build"
        }
    })
});

gulp.task("watch", gulp.series(["pug", "sass", "js", "browser_sync"]), function(){
    gulp.watch(PUG_SRC, gulp.series(["pug"]));
    gulp.watch(SASS_SRC, gulp.series(["sass"]));
});