cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [
        "@net_sourceforge_asio_asio//:asio",
        "//experimental:expected",
        "//network/dns:native_resolver",
        "//network/dns:server",
        "//network/dns:opcode",
        "//network/dns:packet",
    ],
    linkopts = [
        "-lresolv"
    ],
)
