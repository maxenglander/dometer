cc_library(
    name = "transport",
    hdrs = ["transport.hpp"],
    deps = [],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "transport_factory",
    hdrs = ["transport_factory.hpp"],
    srcs = ["transport_factory.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        ":transport",
    ],
    visibility = ["//visibility:public"],
)
