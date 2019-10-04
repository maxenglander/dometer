cc_library(
    name = "handler",
    deps = [
        "//experimental:expected",
        "//network/dns:packet",
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
        "//util:error",
        "//network/dns:packet",
        "//network/dns/resolver:native_resolver",
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
