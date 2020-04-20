cc_library(
    name = "any_event",
    hdrs = ["any_event.hpp"],
    deps = [
        "//std/x:variant",
        ":parse_query_event",
        ":parse_reply_event",
        ":resolve_query_event",
        ":start_session_event",
        ":stop_session_event",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "parse_message_event",
    deps = [
        "//dometer/dns/message:message",
        "//dometer/util:error",
        "//std/x:expected",
    ],
    hdrs = ["parse_message_event.hpp"],
    srcs = ["parse_message_event.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "parse_query_event",
    deps = [
        "//dometer/dns/event:parse_message_event",
        "//dometer/dns/message:message",
        "//dometer/util:error",
        "//std/x:expected",
    ],
    hdrs = ["parse_query_event.hpp"],
    srcs = ["parse_query_event.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "parse_reply_event",
    deps = [
        "//dometer/dns/event:parse_message_event",
        "//dometer/dns/message:message",
        "//dometer/util:error",
        "//std/x:expected",
    ],
    hdrs = ["parse_reply_event.hpp"],
    srcs = ["parse_reply_event.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "resolve_query_event",
    deps = [
        "//dometer/dns/message:question",
        "//dometer/dns/resolver:error",
        "//std/x:expected",
    ],
    hdrs = ["resolve_query_event.hpp"],
    srcs = ["resolve_query_event.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "start_session_event",
    hdrs = ["start_session_event.hpp"],
    srcs = ["start_session_event.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "stop_session_event",
    hdrs = ["stop_session_event.hpp"],
    srcs = ["stop_session_event.cpp"],
    visibility = ["//visibility:public"],
)
