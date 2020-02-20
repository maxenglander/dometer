cc_library(
    name = "server",
    hdrs = ["server.hpp"],
    deps = [
    ],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "server_parser",
    hdrs = ["server_parser.hpp"],
    srcs = ["server_parser.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        ":server",
        ":transport",
        ":transport_parser",
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
    name = "transport_parser",
    hdrs = ["transport_parser.hpp"],
    srcs = ["transport_parser.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        ":transport",
    ],
    visibility = ["//visibility:public"]
)
