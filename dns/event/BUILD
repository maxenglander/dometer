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
    name = "lookup_event",
    deps = [
        "//dns:packet",
        "//util:error",
        "//x:expected",
        ":event",
        ":event_type",
    ],
    hdrs = ["lookup_event.hpp"],
    srcs = ["lookup_event.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "query_event",
    deps = [
        "//dns:packet",
        "//util:error",
        "//x:expected",
        ":event",
        ":event_type",
    ],
    hdrs = ["query_event.hpp"],
    srcs = ["query_event.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "reply_event",
    deps = [
        "//dns:packet",
        "//util:error",
        "//x:expected",
        ":event",
        ":event_type",
    ],
    hdrs = ["reply_event.hpp"],
    srcs = ["reply_event.cpp"],
    visibility = ["//visibility:public"],
)
