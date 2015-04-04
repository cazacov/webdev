requirejs.config({
    baseUrl: "js",
    //urlArgs: "bust=" + (new Date()).getTime(),  // prevent caching
    shim: {
    },
    paths: {
        sprintf: "lib/sprintf/src/sprintf",
        requirejs: "lib/requirejs/require",
        angular: "lib/angular/angular"
    }
});