cc_library(
    name = "header",
    deps = [],
    hdrs = ["header.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "native_resolver",
    hdrs = ["native_resolver.hpp"],
    srcs = ["native_resolver.cpp"],
    deps = [
        "//experimental:expected",
        "//util:error",
        ":packet",
    ],
    linkopts = ["-lresolv"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "packet",
    hdrs = ["packet.hpp"],
    deps = [
        "//experimental:expected",
        "//util:error",
        ":header",
    ],
    srcs = ["packet.cpp"],
    visibility = ["//visibility:public"],
)
