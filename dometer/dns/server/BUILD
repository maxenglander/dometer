cc_library(
    name = "server",
    hdrs = ["server.hpp"],
    deps = [
        "@net_sourceforge_asio_asio//:asio",
        "//dometer/dns/handler:handler",
        "//dometer/dns/handler:resolving_handler",
        "//dometer/dns:packet",
        "//std/x:expected",
        "//dometer/util:error",
    ],
    srcs = ["server.cpp"],
    visibility = ["//visibility:public"],
)
