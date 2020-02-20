cc_library(
    name = "handler",
    hdrs = ["handler.hpp", "handler.ipp"],
    srcs = ["handler.cpp"],
    deps = [
        "//dometer/metrics:counter",
        "//dometer/metrics:observation",
        "//dometer/metrics:summary",
        "//std/x:variant",
        ":prometheus_handler",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "handler_factory",
    hdrs = ["handler_factory.hpp"],
    srcs = ["handler_factory.cpp"],
    deps = [
        "//std/x:variant",
        ":handler",
        ":options",
        ":prometheus_handler_factory",
        ":prometheus_options",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "options",
    hdrs = ["options.hpp"],
    deps = [
        ":prometheus_options",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "prometheus_handler",
    deps = [
        "@com_github_jupp0r_prometheus_cpp//core",
        "//dometer/metrics:counter",
        "//dometer/metrics:metric",
        "//dometer/metrics:label_helper",
        "//dometer/metrics:observation",
        "//dometer/metrics:summary",
        "//dometer/util:error",
        "//dometer/util:lru_map",
        "//prometheus/x:types",
        "//std/x:expected",
        "//std/x:variant",
        ":prometheus_lru_map",
    ],
    hdrs = [
        "prometheus_handler.hpp",
        "prometheus_handler.ipp",
    ],
    srcs = ["prometheus_handler.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "prometheus_lru_map",
    deps = [
        "@com_github_jupp0r_prometheus_cpp//core",
        "//dometer/util:lru_map",
        "//prometheus/x:types",
        "//std/x:variant",
    ],
    hdrs = [
        "prometheus_lru_map.hpp",
    ],
    srcs = ["prometheus_lru_map.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "prometheus_handler_factory",
    hdrs = ["prometheus_handler_factory.hpp"],
    srcs = ["prometheus_handler_factory.cpp"],
    deps = [
        "//prometheus/x:types",
        ":prometheus_handler",
        ":prometheus_options",
        ":prometheus_transport_factory",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "prometheus_options",
    deps = [
        "//std/x:variant",
        ":prometheus_transport_options",
    ],
    hdrs = ["prometheus_options.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "prometheus_pull_transport_options",
    deps = [],
    hdrs = ["prometheus_pull_transport_options.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "prometheus_transport_factory",
    hdrs = ["prometheus_transport_factory.hpp"],
    srcs = ["prometheus_transport_factory.cpp"],
    deps = [
        "@com_github_jupp0r_prometheus_cpp//core",
        "@com_github_jupp0r_prometheus_cpp//pull",
        "@com_github_jupp0r_prometheus_cpp//push",
        "//prometheus/x:types",
        "//std/x:variant",
        ":prometheus_pull_transport_options",
        ":prometheus_transport_options",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "prometheus_transport_options",
    deps = [
        "//std/x:variant",
        ":prometheus_pull_transport_options",
    ],
    hdrs = ["prometheus_transport_options.hpp"],
    visibility = ["//visibility:public"],
)
