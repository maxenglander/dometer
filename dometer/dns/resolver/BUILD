cc_library(
    name = "error",
    hdrs = ["error.hpp"],
    srcs = ["error.cpp"],
    deps = [
        "//dometer/util:error",
        ":error_code",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "error_code",
    hdrs = ["error_code.hpp"],
    visibility = ["//visibility:public"],
)

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
        "//dometer/dns:class",
        "//dometer/dns/message:message",
        "//dometer/dns/message:message_factory",
        "//dometer/dns:type",
        "//std/x:expected",
        ":error",
        ":error_code",
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
        "//std/x:variant",
        ":libresolv_options",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "resolver",
    hdrs = ["resolver.hpp"],
    deps = [
        "//dometer/dns:class",
        "//dometer/dns:type",
        "//dometer/dns/message:message",
        "//std/x:expected",
        ":error",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "resolver_factory",
    hdrs = ["resolver_factory.hpp"],
    srcs = ["resolver_factory.cpp"],
    deps = [
        "//std/x:variant",
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
