cc_library(
    name = "parser",
    hdrs = ["parser.hpp"],
    srcs = ["parser.cpp"],
    deps = [
        "@com_github_open-source-parsers_jsoncpp//:jsoncpp",
        "//dometer/config/metrics/handler/prometheus:transport_parser",
        "//dometer/metrics/handler:options",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "pull_transport_parser",
    hdrs = ["pull_transport_parser.hpp"],
    srcs = ["pull_transport_parser.cpp"],
    deps = [
        "@com_github_open-source-parsers_jsoncpp//:jsoncpp",
        "//dometer/metrics/handler/prometheus:pull_transport_options",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "transport_parser",
    hdrs = ["transport_parser.hpp"],
    srcs = ["transport_parser.cpp"],
    deps = [
        "@com_github_open-source-parsers_jsoncpp//:jsoncpp",
        "//dometer/metrics/handler/prometheus:transport_options",
        ":pull_transport_parser",
    ],
    visibility = ["//visibility:public"],
)
