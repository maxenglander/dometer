cc_library(
    name = "app",
    hdrs = ["app.hpp"],
    srcs = ["app.cpp"],
    deps = [
        "//dometer/dns/event:any_event",
        "//dometer/dns/server:server",
        "//dometer/dns/eventmetrics:metric_recording_callback",
        "//dometer/event:emitter",
        "//dometer/metrics:recorder",
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
        "//dometer/dns/server:basic_server",
        "//dometer/dns/server:server",
        "//dometer/dns/event:any_event",
        "//dometer/event:emitter",
        "//dometer/metrics:options",
        "//dometer/metrics:recorder",
        "//dometer/metrics/handler:handler_factory",
        "//dometer/util:error",
        "//std/x:expected",
        "//std/x:unique",
        ":app",
        ":options",
    ],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "app_test",
    srcs = ["app_test.cpp"],
    deps = [
        "//dometer/dns/server:mock_server",
        "//dometer/event:mock_emitter",
        "//dometer/metrics:mock_recorder",
        "//dometer/util:error",
        ":app",
        ":options",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "options",
    hdrs = ["options.hpp"],
    deps = [
        "@com_github_google_googletest//:gtest_main",
        "//dometer/app/dns:options",
        "//dometer/app/metrics:options",
    ],
    visibility = ["//visibility:public"],
)
