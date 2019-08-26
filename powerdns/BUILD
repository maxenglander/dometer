cc_library(
    name = "initialize_remote_backend_handler",
    hdrs = ["initialize_remote_backend_handler.h"],
    srcs = ["initialize_remote_backend_handler.cc"],
    deps = [
        "@com_github_open-source-parsers_jsoncpp//:jsoncpp",
        ":initialize_remote_backend_query",
        ":remote_backend_handler",
        ":remote_backend_replies",
    ],
)

cc_library(
    name = "initialize_remote_backend_query",
    hdrs = ["initialize_remote_backend_query.h"],
)

cc_library(
    name = "instrumented_lookup_remote_backend_handler",
    hdrs = ["instrumented_lookup_remote_backend_handler.h"],
    srcs = ["instrumented_lookup_remote_backend_handler.cc"],
    deps = [
        ":lookup_remote_backend_handler",
        ":lookup_remote_backend_query",
        ":lookup_remote_backend_reply",
        ":native_lookup_remote_backend_handler",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "lookup_remote_backend_handler",
    hdrs = ["lookup_remote_backend_handler.h"],
    srcs = ["lookup_remote_backend_handler.cc"],
    deps = [
        "@com_github_open-source-parsers_jsoncpp//:jsoncpp",
        "//network/dns:native_resolver",
        "//std/experimental:expected",
        ":lookup_remote_backend_query",
        ":lookup_remote_backend_reply",
        ":remote_backend_handler",
        ":remote_backend_replies",
    ],
)

cc_library(
    name = "lookup_remote_backend_query",
    hdrs = ["lookup_remote_backend_query.h"],
    srcs = ["lookup_remote_backend_query.cc"],
)

cc_library(
    name = "lookup_remote_backend_reply",
    hdrs = ["lookup_remote_backend_reply.h"],
    srcs = ["lookup_remote_backend_reply.cc"],
    deps = [
        ":lookup_remote_backend_query",
    ],
)

cc_library(
    name = "native_lookup_remote_backend_handler",
    hdrs = ["native_lookup_remote_backend_handler.h"],
    srcs = ["native_lookup_remote_backend_handler.cc"],
    deps = [
        ":lookup_remote_backend_handler",
        ":lookup_remote_backend_query",
        ":lookup_remote_backend_reply",
        ":remote_backend_replies",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "remote_backend_handler",
    hdrs = ["remote_backend_handler.h"],
    deps = [
        "@com_github_open-source-parsers_jsoncpp//:jsoncpp",
        "//std/experimental:expected",
    ],
)

cc_library(
    name = "remote_backend_replies",
    hdrs = ["remote_backend_replies.h"],
    srcs = ["remote_backend_replies.cc"],
    deps = [
        "@com_github_open-source-parsers_jsoncpp//:jsoncpp"
    ]
)

cc_library(
    name = "remote_backend_router",
    hdrs = ["remote_backend_router.h"],
    srcs = ["remote_backend_router.cc"],
    deps = [
        "@com_github_open-source-parsers_jsoncpp//:jsoncpp",
        "//std/experimental:expected",
        ":remote_backend_handler",
    ],
    visibility = ["//visibility:public"],
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
        ":remote_backend_router",
    ],
    visibility = ["//visibility:public"],
)
