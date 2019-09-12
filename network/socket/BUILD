cc_library(
    name = "recv_until",
    hdrs = ["recv_until.hpp"],
    srcs = ["recv_until.cpp"],
)

cc_library(
    name = "socket_factory",
    hdrs = ["socket_factory.hpp"],
    srcs = ["socket_factory.cpp"],
    deps = [
        "//network/socket:unix_socket",
        "//std/experimental:expected",
        "//util:error"
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "unix_socket",
    hdrs = ["unix_socket.hpp"],
    srcs = ["unix_socket.cpp"],
    deps = [
        "//std/experimental:expected",
        "//util:error",
        ":recv_until"
    ],
    visibility = ["//visibility:public"],
)
