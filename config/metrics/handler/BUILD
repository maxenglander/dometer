cc_library(
    name = "handler_factory",
    hdrs = ["handler_factory.hpp"],
    srcs = ["handler_factory.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        "//config/metrics/handler:prometheus_handler_factory",
        "//metrics/handler:options",
        "//x:optional",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "prometheus_handler_factory",
    hdrs = ["prometheus_handler_factory.hpp"],
    srcs = ["prometheus_handler_factory.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        "//config/metrics/handler:prometheus_transport_factory",
        "//metrics/handler:prometheus_options",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "prometheus_pull_transport_factory",
    hdrs = ["prometheus_pull_transport_factory.hpp"],
    srcs = ["prometheus_pull_transport_factory.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        "//metrics/handler:prometheus_pull_transport_options",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "prometheus_transport_factory",
    hdrs = ["prometheus_transport_factory.hpp"],
    srcs = ["prometheus_transport_factory.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        "//metrics/handler:prometheus_transport_options",
        "prometheus_pull_transport_factory",
    ],
    visibility = ["//visibility:public"],
)
