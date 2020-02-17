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
        "//metrics:counter",
        "//metrics:metric",
        "//metrics:label_helper",
        "//metrics:observation",
        "//metrics:summary",
        "//util:error",
        "//util:lru_map",
        "//x:expected",
        "//x:variant",
        ":prometheus_lru_map",
        ":prometheus_types",
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
        "//util:lru_map",
        "//x:variant",
        ":prometheus_types",
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
        ":prometheus_handler",
        ":prometheus_options",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "prometheus_options",
    deps = [
        "//x:variant",
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
    name = "prometheus_transport_options",
    deps = [
        "//x:variant",
        ":prometheus_pull_transport_options",
    ],
    hdrs = ["prometheus_transport_options.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "prometheus_types",
    deps = [
        "@com_github_jupp0r_prometheus_cpp//core"
    ],
    hdrs = [
        "prometheus_types.hpp",
    ],
    srcs = [],
    visibility = ["//visibility:public"],
)
