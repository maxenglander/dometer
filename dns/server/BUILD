cc_library(
    name = "event",
    deps = [
        ":event_type",
    ],
    hdrs = ["event.hpp"],
    srcs = [],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "event_type",
    deps = [],
    hdrs = ["event_type.hpp"],
    srcs = [],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "handler",
    deps = [
        "//dns:packet",
        "//experimental:expected",
        "//util:callback",
        "//util:callback_registry",
        "//util:error",
        ":event",
        ":event_type",
    ],
    hdrs = ["handler.hpp"],
    srcs = [],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "lookup_event",
    deps = [
        "//dns:packet",
        "//experimental:expected",
        "//util:error",
        ":event",
        ":event_type",
    ],
    hdrs = ["lookup_event.hpp"],
    srcs = ["lookup_event.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "native_resolving_handler",
    hdrs = ["native_resolving_handler.hpp"],
    srcs = ["native_resolving_handler.cpp"],
    deps = [
        "//dns:packet",
        "//dns/resolver:native_resolver",
        "//experimental:expected",
        "//util:callback",
        "//util:callback_registry",
        "//util:error",
        ":event",
        ":event_type",
        ":handler",
        ":lookup_event",
        ":query_event",
        ":reply_event",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "query_event",
    deps = [
        "//dns:packet",
        "//experimental:expected",
        "//util:error",
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
        "//experimental:expected",
        "//util:error",
        ":event",
        ":event_type",
    ],
    hdrs = ["reply_event.hpp"],
    srcs = ["reply_event.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "server",
    hdrs = ["server.hpp"],
    deps = [
        "@net_sourceforge_asio_asio//:asio",
        "//dns:packet",
        "//experimental:expected",
        "//util:error",
        ":handler",
        ":native_resolving_handler",
    ],
    srcs = ["server.cpp"],
    visibility = ["//visibility:public"],
)
