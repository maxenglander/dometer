cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [
        "@net_sourceforge_asio_asio//:asio",
        "//dns:packet",
        "//dns/server:event_type",
        "//dns/server:handler",
        "//dns/server:lookup_event",
        "//dns/server:native_resolving_handler",
        "//dns/server:query_event",
        "//dns/server:reply_event",
        "//dns/server:server",
        "//experimental:expected",
        "//metrics:observer",
        "//metrics:query_observation",
    ],
    linkopts = [
        "-lresolv"
    ],
)
