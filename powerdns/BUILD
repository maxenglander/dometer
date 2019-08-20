cc_library(
    name = "lookup_query",
    hdrs = ["lookup_query.h"],
    srcs = ["lookup_query.cc"],
)

cc_library(
    name = "lookup_remote_backend_handler",
    hdrs = ["lookup_remote_backend_handler.h"],
    srcs = ["lookup_remote_backend_handler.cc"],
    deps = [
        "@jsoncpp//:jsoncpp",
        "//network/dns:resolver",
        "//std/experimental:expected",
        ":lookup_query",
        ":lookup_reply",
        ":remote_backend_handler",
    ],
)

cc_library(
    name = "lookup_reply",
    hdrs = ["lookup_reply.h"],
    srcs = ["lookup_reply.cc"],
    deps = [
        ":lookup_query",
    ],
)

cc_library(
    name = "native_lookup_remote_backend_handler",
    hdrs = ["native_lookup_remote_backend_handler.h"],
    srcs = ["native_lookup_remote_backend_handler.cc"],
    deps = [
        ":lookup_query",
        ":lookup_reply",
        ":lookup_remote_backend_handler",
    ],
)

cc_library(
    name = "remote_backend_handler",
    hdrs = ["remote_backend_handler.h"],
    srcs = ["remote_backend_handler.cc"],
    deps = [
        "@jsoncpp//:jsoncpp",
        "//std/experimental:expected",
    ],
)

cc_library(
    name = "remote_backend_router",
    hdrs = ["remote_backend_router.h"],
    srcs = ["remote_backend_router.cc"],
    deps = [
        "@jsoncpp//:jsoncpp",
        "//std/experimental:expected",
        ":remote_backend_handler",
    ],
)

cc_library(
    name = "unix_socket_remote_backend",
    hdrs = ["unix_socket_remote_backend.h"],
    srcs = ["unix_socket_remote_backend.cc"],
    deps = [
        "//network/socket:socket_factory",
        "//network/socket:unix_socket",
        "//std/experimental:expected",
        "//util:json_serde",
    ],
    visibility = ["//visibility:public"],
)
