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
    name = "handler",
    deps = [
        "//dometer/dns/message:message",
        "//dometer/event:callback",
        "//dometer/event:emitter",
        "//dometer/util:error",
        "//std/x:expected",
        ":error",
    ],
    hdrs = ["handler.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "mock_handler",
    hdrs = ["mock_handler.hpp"],
    srcs = ["mock_handler.cpp"],
    deps = [
        "@com_github_google_googletest//:gtest",
        "//dometer/dns/message:message",
        "//dometer/dns/message:message_factory",
        "//dometer/dns/message:parser",
        ":error",
        ":error_code",
        ":handler",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "resolving_handler",
    hdrs = ["resolving_handler.hpp"],
    srcs = ["resolving_handler.cpp"],
    deps = [
        "//dometer/dns/event:any_event",
        "//dometer/dns/event:parse_query_event",
        "//dometer/dns/event:parse_reply_event",
        "//dometer/dns/event:resolve_query_event",
        "//dometer/dns/message:message",
        "//dometer/dns/message:message_factory",
        "//dometer/dns/message:parser",
        "//dometer/dns/resolver:libresolv_resolver",
        "//dometer/event:callback",
        "//dometer/event:emitter",
        "//dometer/util:error",
        "//dometer/util:human_error_encoder",
        "//std/x:expected",
        ":error",
        ":handler",
    ],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "resolving_handler_test",
    srcs = ["resolving_handler_test.cpp"],
    deps = [
        "@com_github_google_googletest//:gtest_main",
        "//dometer/dns:opcode",
        "//dometer/dns/event:any_event",
        "//dometer/dns/handler:error_code",
        "//dometer/dns/handler:resolving_handler",
        "//dometer/dns/message:builder",
        "//dometer/dns/resolver:mock_resolver",
        "//dometer/event:mock_emitter",
    ],
)
