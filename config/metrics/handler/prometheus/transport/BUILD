cc_library(
    name = "exposer",
    hdrs = ["exposer.hpp"],
    deps = [],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "exposer_factory",
    hdrs = ["exposer_factory.hpp"],
    srcs = ["exposer_factory.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        ":exposer",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "transport",
    hdrs = ["transport.hpp"],
    deps = [
        "//x:optional",
        ":exposer",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "transport_factory",
    hdrs = ["transport_factory.hpp"],
    srcs = ["transport_factory.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        ":exposer_factory",
        ":transport",
    ],
    visibility = ["//visibility:public"],
)
