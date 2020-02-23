cc_library(
    name = "metrics_parser",
    hdrs = ["metrics_parser.hpp"],
    srcs = ["metrics_parser.cpp"],
    deps = [
        "@com_github_open-source-parsers_jsoncpp//:jsoncpp",
        "//dometer/config/metrics/handler:handler_parser",
        "//dometer/metrics:options",
    ],
    visibility = ["//visibility:public"],
)
