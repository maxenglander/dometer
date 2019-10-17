cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [
        "@net_sourceforge_asio_asio//:asio",
        "//experimental:expected",
        "//network/dns:packet",
        "//network/dns/server:event_type",
        "//network/dns/server:handler",
        "//network/dns/server:lookup_event",
        "//network/dns/server:native_resolving_handler",
        "//network/dns/server:query_event",
        "//network/dns/server:reply_event",
        "//network/dns/server:server",
    ],
    linkopts = [
        "-lresolv"
    ],
)
