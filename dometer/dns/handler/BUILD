cc_library(
    name = "handler",
    deps = [
        "//dometer/dns/message:message",
        "//dometer/event:callback",
        "//dometer/event:emitter",
        "//dometer/util:error",
        "//std/x:expected",
    ],
    hdrs = ["handler.hpp"],
    srcs = [],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "resolving_handler",
    hdrs = ["resolving_handler.hpp"],
    srcs = ["resolving_handler.cpp"],
    deps = [
        "//dometer/dns/event:any_event",
        "//dometer/dns/event:parse_query_event",
        "//dometer/dns/event:parse_reply_event",
        "//dometer/dns/event:resolve_query_event",
        "//dometer/dns/message:message",
        "//dometer/dns/message:message_factory",
        "//dometer/dns/message:parser",
        "//dometer/dns/resolver:libresolv_resolver",
        "//dometer/event:callback",
        "//dometer/event:emitter",
        "//dometer/util:error",
        "//dometer/util:human_error_encoder",
        "//std/x:expected",
        ":handler",
    ],
    visibility = ["//visibility:public"],
)
