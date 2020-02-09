cc_library(
    name = "server",
    hdrs = ["server.hpp"],
    deps = [
    ],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "server_factory",
    hdrs = ["server_factory.hpp"],
    srcs = ["server_factory.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        ":server",
        ":transport",
        ":transport_factory",
    ],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "transport",
    hdrs = ["transport.hpp"],
    deps = [
    ],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "transport_factory",
    hdrs = ["transport_factory.hpp"],
    srcs = ["transport_factory.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        ":transport",
    ],
    visibility = ["//visibility:public"]
)
