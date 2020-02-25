cc_library(
    name = "server_parser",
    hdrs = ["server_parser.hpp"],
    srcs = ["server_parser.cpp"],
    deps = [
        "@com_github_open-source-parsers_jsoncpp//:jsoncpp",
        "//dometer/dns/server:options",
        "//dometer/dns/server:transport_options",
        ":transport_parser",
    ],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "transport_parser",
    hdrs = ["transport_parser.hpp"],
    srcs = ["transport_parser.cpp"],
    deps = [
        "@com_github_open-source-parsers_jsoncpp//:jsoncpp",
        "//dometer/dns/server:transport_options",
    ],
    visibility = ["//visibility:public"]
)
