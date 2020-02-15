cc_library(
    name = "libresolv_function",
    deps = [],
    hdrs = ["libresolv_function.hpp"],
    srcs = [],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "libresolv_options",
    hdrs = ["libresolv_options.hpp"],
    deps = [
        ":libresolv_function",
    ],
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
        "//util:error",
        "//x:expected",
        ":resolver",
        ":libresolv_function",
    ],
    linkopts = ["-lresolv"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "options",
    hdrs = ["options.hpp"],
    deps = [
        "//x:variant",
        ":libresolv_options",
    ],
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

cc_library(
    name = "resolver_factory",
    hdrs = ["resolver_factory.hpp"],
    srcs = ["resolver_factory.cpp"],
    deps = [
        "//x:variant",
        ":libresolv_options",
        ":libresolv_resolver",
        ":options",
        ":resolver",
    ],
    copts = [
        "-Werror=unreachable-code",
    ],
    visibility = ["//visibility:public"],
)
