cc_library(
    name = "mock_registry",
    srcs = ["mock_registry.hpp"],
    deps = [
        "@com_github_jupp0r_prometheus_cpp//core",
    ],
)

cc_library(
    name = "types",
    deps = [
        "@com_github_jupp0r_prometheus_cpp//core",
        "@com_github_jupp0r_prometheus_cpp//pull",
        "@com_github_jupp0r_prometheus_cpp//push",
        "//std/x:variant",
    ],
    hdrs = ["types.hpp"],
    srcs = ["types.cpp"],
    visibility = ["//visibility:public"],
)
