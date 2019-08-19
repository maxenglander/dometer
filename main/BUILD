cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        "@jsoncpp//:jsoncpp",
        "//network/dns:resolver",
        "//network/socket:unix_socket",
        "//powerdns:unix_socket_remote_backend",
        "//std/experimental:expected",
    ],
)
