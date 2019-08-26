cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        "//network/dns:native_resolver",
        "//network/socket:unix_socket",
        "//powerdns:remote_backend_router",
        "//powerdns:native_lookup_remote_backend_handler",
        "//powerdns:noop_initialize_remote_backend_handler",
        "//powerdns:unix_socket_remote_backend",
        "//std/experimental:expected",
        "//util:json_serde",
    ],
)
