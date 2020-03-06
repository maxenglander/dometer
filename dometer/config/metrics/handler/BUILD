cc_library(
    name = "parser",
    hdrs = ["parser.hpp"],
    srcs = ["parser.cpp"],
    deps = [
        "@com_github_open-source-parsers_jsoncpp//:jsoncpp",
        "//dometer/config/metrics/handler/prometheus:parser",
        "//dometer/metrics/handler:options",
        "//std/x:optional",
    ],
    visibility = ["//visibility:public"],
)
