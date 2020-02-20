cc_library(
    name = "handler_parser",
    hdrs = ["handler_parser.hpp"],
    srcs = ["handler_parser.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        "//config/metrics/handler:prometheus_handler_parser",
        "//metrics/handler:options",
        "//x:optional",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "prometheus_handler_parser",
    hdrs = ["prometheus_handler_parser.hpp"],
    srcs = ["prometheus_handler_parser.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        "//config/metrics/handler:prometheus_transport_parser",
        "//metrics/handler:prometheus_options",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "prometheus_pull_transport_parser",
    hdrs = ["prometheus_pull_transport_parser.hpp"],
    srcs = ["prometheus_pull_transport_parser.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        "//metrics/handler:prometheus_pull_transport_options",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "prometheus_transport_parser",
    hdrs = ["prometheus_transport_parser.hpp"],
    srcs = ["prometheus_transport_parser.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        "//metrics/handler:prometheus_transport_options",
        "prometheus_pull_transport_parser",
    ],
    visibility = ["//visibility:public"],
)
