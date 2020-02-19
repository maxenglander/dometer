cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [
        "//config:config_parser",
        "//config:schema_validator",
        "//dns/resolver:resolver",
        "//dns/resolver:resolver_factory",
        "//dns/server:event_type",
        "//dns/server:handler",
        "//dns/server:observing_handler",
        "//dns/server:resolving_handler",
        "//dns/server:server",
        "//metrics:observer",
        "//metrics:observer_factory",
        ":options",
        ":options_parser",
    ]
)

cc_library(
    name = "options",
    hdrs = ["options.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "options_parser",
    hdrs = ["options_parser.hpp"],
    srcs = ["options_parser.cpp"],
    deps = [
        "//util:error",
        "//x:expected",
        ":options",
    ],
    visibility = ["//visibility:public"],
)
