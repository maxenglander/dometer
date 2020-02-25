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
    name = "parser",
    hdrs = ["parser.hpp"],
    srcs = ["parser.cpp"],
    deps = [
        "@com_github_open-source-parsers_jsoncpp//:jsoncpp",
        "//std/x:optional",
        "//dometer/dns/resolver:options",
        ":libresolv_parser",
    ],
    visibility = ["//visibility:public"],
)
