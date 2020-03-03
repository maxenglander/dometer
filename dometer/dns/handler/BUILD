cc_library(
    name = "handler",
    deps = [
        "//dometer/dns/message:message",
        "//dometer/dns/event:event",
        "//dometer/dns/event:event_type",
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
    name = "observing_handler",
    hdrs = ["observing_handler.hpp"],
    srcs = ["observing_handler.cpp"],
    deps = [
        "//dometer/dns/message:message",
        "//dometer/dns/event:event",
        "//dometer/dns/event:event_type",
        "//dometer/dns/event:parse_message_event",
        "//dometer/dns/event:resolve_query_event",
        "//dometer/dns/metrics:lookup_observation",
        "//dometer/metrics:observer",
        "//dometer/util:error",
        "//std/x:expected",
        ":handler",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "resolving_handler",
    hdrs = ["resolving_handler.hpp"],
    srcs = ["resolving_handler.cpp"],
    deps = [
        "//dometer/dns/event:event",
        "//dometer/dns/event:event_type",
        "//dometer/dns/event:parse_message_event",
        "//dometer/dns/event:resolve_query_event",
        "//dometer/dns/message:message",
        "//dometer/dns/message:factory",
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
