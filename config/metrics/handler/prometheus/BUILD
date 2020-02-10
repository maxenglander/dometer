cc_library(
    name = "prometheus",
    hdrs = ["prometheus.hpp"],
    deps = [
        "//config/metrics/handler/prometheus/transport:transport"
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "prometheus_factory",
    hdrs = ["prometheus_factory.hpp"],
    srcs = ["prometheus_factory.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        "//config/metrics/handler/prometheus/transport:transport_factory",
        ":prometheus",
    ],
    visibility = ["//visibility:public"],
)
