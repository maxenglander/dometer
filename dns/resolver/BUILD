cc_library(
    name = "libresolv_function",
    deps = [],
    hdrs = ["libresolv_function.hpp"],
    srcs = [],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "libresolv_resolver",
    hdrs = ["libresolv_resolver.hpp"],
    srcs = ["libresolv_resolver.cpp"],
    deps = [
        "//dns:class",
        "//dns:packet",
        "//dns:type",
        "//x:expected",
        "//util:error",
        ":libresolv_function",
        ":resolver",
    ],
    linkopts = ["-lresolv"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "resolver",
    hdrs = ["resolver.hpp"],
    deps = [
        "//dns:class",
        "//dns:packet",
        "//dns:type",
        "//util:error",
        "//x:expected",
    ],
    visibility = ["//visibility:public"],
)
