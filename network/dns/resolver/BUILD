cc_library(
    name = "native_resolver",
    hdrs = ["native_resolver.hpp"],
    srcs = ["native_resolver.cpp"],
    deps = [
        "//experimental:expected",
        "//network/dns:packet",
        "//util:error",
        ":resolution_mode",
    ],
    linkopts = ["-lresolv"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "resolution_mode",
    deps = [],
    hdrs = ["resolution_mode.hpp"],
    srcs = [],
    visibility = ["//visibility:public"],
)
