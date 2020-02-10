cc_library(
    name = "handler",
    hdrs = ["handler.hpp"],
    deps = [],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "handler_factory",
    hdrs = ["handler_factory.hpp"],
    srcs = ["handler_factory.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        "//config/metrics/handler/prometheus:prometheus_factory",
        "//x:optional",
        ":handler",
    ],
    visibility = ["//visibility:public"],
)
