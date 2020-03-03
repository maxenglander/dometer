cc_library(
    name = "event",
    deps = [
        ":event_type",
    ],
    hdrs = ["event.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "event_type",
    hdrs = ["event_type.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "parse_message_event",
    deps = [
        "//dometer/dns/message:message",
        "//dometer/util:error",
        "//std/x:expected",
        ":event",
        ":event_type",
    ],
    hdrs = ["parse_message_event.hpp"],
    srcs = ["parse_message_event.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "resolve_query_event",
    deps = [
        "//dometer/dns:question",
        "//dometer/dns/resolver:error",
        "//std/x:expected",
        ":event",
        ":event_type",
    ],
    hdrs = ["resolve_query_event.hpp"],
    srcs = ["resolve_query_event.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "start_session_event",
    deps = [
        ":event",
        ":event_type",
    ],
    hdrs = ["start_session_event.hpp"],
    srcs = ["start_session_event.cpp"],
    visibility = ["//visibility:public"],
)
