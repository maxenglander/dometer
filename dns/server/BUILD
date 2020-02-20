cc_library(
    name = "server",
    hdrs = ["server.hpp"],
    deps = [
        "@net_sourceforge_asio_asio//:asio",
        "//dns/handler:handler",
        "//dns/handler:resolving_handler",
        "//dns:packet",
        "//x:expected",
        "//util:error",
    ],
    srcs = ["server.cpp"],
    visibility = ["//visibility:public"],
)
