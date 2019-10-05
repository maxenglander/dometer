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
        "//experimental:expected",
        "//network/dns:packet",
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
    name = "native_resolving_handler",
    hdrs = ["native_resolving_handler.hpp"],
    srcs = ["native_resolving_handler.cpp"],
    deps = [
        "//experimental:expected",
        "//network/dns:packet",
        "//network/dns/resolver:native_resolver",
        "//util:callback",
        "//util:callback_registry",
        "//util:error",
        ":event",
        ":event_type",
        ":handler",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "server",
    hdrs = ["server.hpp"],
    deps = [
        "@net_sourceforge_asio_asio//:asio",
        "//experimental:expected",
        "//util:error",
        "//network/dns:packet",
        ":handler",
        ":native_resolving_handler",
    ],
    srcs = ["server.cpp"],
    visibility = ["//visibility:public"],
)
