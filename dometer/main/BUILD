cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [
        "//dometer/config:config_parser",
        "//dometer/dns/resolver:resolver",
        "//dometer/dns/resolver:resolver_factory",
        "//dometer/dns/handler:handler",
        "//dometer/dns/handler:observing_handler",
        "//dometer/dns/handler:resolving_handler",
        "//dometer/dns/server:server",
        "//dometer/metrics:observer",
        "//dometer/metrics:observer_factory",
        ":help",
        ":options",
        ":options_parser",
    ]
)

cc_library(
    name = "help",
    hdrs = ["help.hpp"],
    srcs = ["help.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "options",
    hdrs = ["options.hpp"],
    deps = [
        "//std/x:optional",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "options_parser",
    hdrs = ["options_parser.hpp"],
    srcs = ["options_parser.cpp"],
    deps = [
        "//dometer/util:error",
        "//std/x:expected",
        ":options",
    ],
    visibility = ["//visibility:public"],
)
