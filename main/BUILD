cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [
        "@net_sourceforge_asio_asio//:asio",
        "//experimental:expected",
        "//network/dns/server:event_type",
        "//network/dns/server:native_resolving_handler",
        "//network/dns/server:server",
    ],
    linkopts = [
        "-lresolv"
    ],
)
