cc_library(
    name = "recv_until",
    hdrs = ["recv_until.h"],
    srcs = ["recv_until.cc"],
)

cc_library(
    name = "socket_factory",
    hdrs = ["socket_factory.h"],
    srcs = ["socket_factory.cc"],
    deps = [
        "//network/socket:unix_socket",
        "//std/experimental:expected",
        "//util:error"
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "unix_socket",
    hdrs = ["unix_socket.h"],
    srcs = ["unix_socket.cc"],
    deps = [
        "//std/experimental:expected",
        "//util:error",
        ":recv_until"
    ],
    visibility = ["//visibility:public"],
)
