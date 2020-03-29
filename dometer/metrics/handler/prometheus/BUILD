cc_library(
    name = "handler",
    deps = [
        "@com_github_jupp0r_prometheus_cpp//core",
        "//dometer/metrics:counter",
        "//dometer/metrics:metric",
        "//dometer/metrics:summary",
        "//dometer/metrics/handler:handler",
        "//dometer/util:error",
        "//dometer/util:lru_map",
        "//prometheus/x:types",
        "//std/x:expected",
        "//std/x:variant",
        ":lru_map",
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
        ":handler",
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
    name = "lru_map",
    deps = [
        "@com_github_jupp0r_prometheus_cpp//core",
        "//dometer/util:lru_map",
        "//prometheus/x:types",
        "//std/x:variant",
    ],
    hdrs = [
        "lru_map.hpp",
    ],
    srcs = ["lru_map.cpp"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "lru_map_test",
    deps = [
        "@com_github_google_googletest//:gtest_main",
        "//prometheus/x:types",
        "//std/x:variant",
        ":lru_map",
    ],
    srcs = ["lru_map_test.cpp"],
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
