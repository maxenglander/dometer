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
    srcs = ["error_code.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "libresolv_function",
    hdrs = ["libresolv_function.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "libresolv_helper",
    hdrs = ["libresolv_helper.hpp"],
    srcs = ["libresolv_helper.cpp"],
    copts = [
        "-DBIND_8_COMPAT=1",
    ],
    linkopts = [
        "-lresolv",
    ],
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
        "//dometer/dns/message:parser",
        "//dometer/dns:type",
        "//std/x:expected",
        ":error",
        ":error_code",
        ":resolver",
        ":libresolv_function",
    ],
    copts = [
        "-DBIND_8_COMPAT=1",
    ],
    linkopts = [
        "-lresolv"
    ],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "libresolv_resolver_test",
    srcs = ["libresolv_resolver_test.cpp"],
    deps = [
        "@com_github_google_googletest//:gtest_main",
        "//dometer/dns:class",
        "//dometer/dns:rcode",
        "//dometer/dns:type",
        "//dometer/dns/event:any_event",
        "//dometer/dns/handler:error",
        "//dometer/dns/handler:error_code",
        "//dometer/dns/handler:mock_handler",
        "//dometer/dns/message:builder",
        "//dometer/dns/message:message_factory",
        "//dometer/dns/message:parser",
        "//dometer/dns/server:server",
        "//dometer/event:emitter",
        ":error",
        ":error_code",
        ":libresolv_helper",
        ":libresolv_resolver",
    ],
    copts = [
        "-DBIND_8_COMPAT",
    ],
    linkopts = [
        "-lresolv",
    ],
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

cc_library(
    name = "mock_resolver",
    hdrs = ["mock_resolver.hpp"],
    deps = [
        "@com_github_google_googletest//:gtest",
    ],

    visibility = ["//visibility:public"],
)
