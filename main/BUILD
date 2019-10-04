cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [
        "@net_sourceforge_asio_asio//:asio",
        "//experimental:expected",
        "//network/dns:opcode",
        "//network/dns:packet",
        "//network/dns/resolver:native_resolver",
        "//network/dns/server:server",
    ],
    linkopts = [
        "-lresolv"
    ],
)
