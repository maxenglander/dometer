cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [
        "//dometer/config:parser",
        "//dometer/dns/event:any_event",
        "//dometer/dns/event:parse_message_event",
        "//dometer/dns/event:resolve_query_event",
        "//dometer/dns/event:start_session_event",
        "//dometer/dns/event:stop_session_event",
        "//dometer/dns/resolver:resolver",
        "//dometer/dns/resolver:resolver_factory",
        "//dometer/dns/handler:handler",
        "//dometer/dns/handler:resolving_handler",
        "//dometer/dns/server:server",
        "//dometer/event:emitter",
        "//dometer/metrics:observer",
        "//dometer/metrics/handler:handler_factory",
        "//dometer/util:error",
        "//dometer/util:error_encoder",
        "//dometer/util:human_error_encoder",
        "//std/x:variant",
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
