cc_library(
    name = "metrics",
    hdrs = ["metrics.hpp"],
    deps = [
        "//metrics/handler:options",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "metrics_factory",
    hdrs = ["metrics_factory.hpp"],
    srcs = ["metrics_factory.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        "//config/metrics/handler:handler_factory",
        ":metrics",
    ],
    visibility = ["//visibility:public"],
)
