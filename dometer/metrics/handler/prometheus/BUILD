cc_library(
    name = "handler",
    deps = [
        "@com_github_jupp0r_prometheus_cpp//core",
        "//dometer/metrics:metric",
        "//dometer/metrics/handler:handler",
        "//dometer/util:error",
        "//prometheus/x:types",
        "//std/x:expected",
        "//std/x:variant",
        ":metric_cache",
    ],
    hdrs = ["handler.hpp"],
    srcs = ["handler.cpp"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "handler_test",
    deps = [
        "@com_github_google_googletest//:gtest_main",
        "@com_github_jupp0r_prometheus_cpp//core",
        "//prometheus/x:types",
        "//dometer/metrics:example_histogram",
        ":handler",
        ":metric_cache",
    ],
    srcs = ["handler_test.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "handler_factory",
    hdrs = ["handler_factory.hpp"],
    srcs = ["handler_factory.cpp"],
    deps = [
        "//dometer/util:error",
        "//prometheus/x:types",
        "//std/x:expected",
        "//std/x:unique",
        ":handler",
        ":options",
        ":transport_factory",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "metric_cache",
    deps = [
        "@com_github_jupp0r_prometheus_cpp//core",
        "//dometer/util:lru_map",
        "//prometheus/x:types",
        "//std/x:variant",
    ],
    hdrs = ["metric_cache.hpp"],
    srcs = ["metric_cache.cpp"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "metric_cache_test",
    deps = [
        "@com_github_google_googletest//:gtest_main",
        "//prometheus/x:types",
        "//std/x:variant",
        ":metric_cache",
    ],
    srcs = ["metric_cache_test.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "options",
    deps = [
        "//std/x:variant",
        ":transport_options",
    ],
    hdrs = ["options.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "pull_transport_options",
    hdrs = ["pull_transport_options.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "transport_factory",
    hdrs = ["transport_factory.hpp"],
    srcs = ["transport_factory.cpp"],
    deps = [
        "@com_github_jupp0r_prometheus_cpp//core",
        "@com_github_jupp0r_prometheus_cpp//pull",
        "@com_github_jupp0r_prometheus_cpp//push",
        "//dometer/util:error",
        "//prometheus/x:types",
        "//std/x:expected",
        "//std/x:variant",
        ":pull_transport_options",
        ":transport_options",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "transport_options",
    deps = [
        "//std/x:variant",
        ":pull_transport_options",
    ],
    hdrs = ["transport_options.hpp"],
    visibility = ["//visibility:public"],
)
