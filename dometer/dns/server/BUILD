cc_library(
    name = "server",
    hdrs = ["server.hpp"],
    deps = [
        "@net_sourceforge_asio_asio//:asio",
        "//dometer/dns/handler:handler",
        "//dometer/dns/handler:resolving_handler",
        "//dometer/dns:packet",
        "//dometer/util:error",
        "//std/x:expected",
        "//std/x:unique",
    ],
    srcs = ["server.cpp"],
    visibility = ["//visibility:public"],
)
