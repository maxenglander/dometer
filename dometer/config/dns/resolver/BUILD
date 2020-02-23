cc_library(
    name = "libresolv_parser",
    hdrs = ["libresolv_parser.hpp"],
    srcs = ["libresolv_parser.cpp"],
    deps = [
        "@com_github_open-source-parsers_jsoncpp//:jsoncpp",
        "//dometer/dns/resolver:libresolv_function",
        "//dometer/dns/resolver:libresolv_options",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "resolver_parser",
    hdrs = ["resolver_parser.hpp"],
    srcs = ["resolver_parser.cpp"],
    deps = [
        "@com_github_open-source-parsers_jsoncpp//:jsoncpp",
        "//std/x:optional",
        "//dometer/dns/resolver:options",
        ":libresolv_parser",
    ],
    visibility = ["//visibility:public"],
)
