cc_library(
    name = "app",
    hdrs = ["app.hpp"],
    srcs = ["app.cpp"],
    deps = [
        "//dometer/dns/server:server",
        "//dometer/util:error",
        ":options",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "app_factory",
    hdrs = ["app_factory.hpp"],
    srcs = ["app_factory.cpp"],
    deps = [
        "//dometer/dns/eventmetrics:metric_recording_callback",
        "//dometer/dns/handler:handler",
        "//dometer/dns/handler:resolving_handler",
        "//dometer/dns/resolver:options",
        "//dometer/dns/resolver:resolver",
        "//dometer/dns/resolver:resolver_factory",
        "//dometer/dns/server:server",
        "//dometer/dns/event:any_event",
        "//dometer/event:emitter",
        "//dometer/metrics:options",
        "//dometer/metrics:recorder",
        "//dometer/metrics/handler:handler_factory",
        "//dometer/util:error",
        "//std/x:expected",
        ":app",
        ":options",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "options",
    hdrs = ["options.hpp"],
    deps = [
        "//dometer/app/dns:options",
        "//dometer/app/metrics:options",
    ],
    visibility = ["//visibility:public"],
)
