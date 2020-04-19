cc_library(
    name = "basic_server",
    hdrs = ["basic_server.hpp"],
    deps = [
        "@net_sourceforge_asio_asio//:asio",
        "//dometer/event:emitter",
        "//dometer/dns/event:any_event",
        "//dometer/dns/event:start_session_event",
        "//dometer/dns/event:stop_session_event",
        "//dometer/dns/handler:handler",
        "//dometer/dns/handler:resolving_handler",
        "//dometer/dns/message:message",
        "//dometer/util:error",
        "//std/x:expected",
        "//std/x:unique",
        ":server",
    ],
    srcs = ["basic_server.cpp"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "basic_server_test",
    srcs = ["basic_server_test.cpp"],
    deps = [
        "@com_github_google_googletest//:gtest_main",
        "//dometer/event:mock_emitter",
        "//dometer/dns/event:any_event",
        "//dometer/dns/event:start_session_event",
        "//dometer/dns/event:stop_session_event",
        "//dometer/dns/handler:handler",
        "//dometer/dns/handler:mock_handler",
        "//dometer/dns/message:builder",
        "//dometer/dns/message:qr",
        "//dometer/dns/message:opcode",
        "//dometer/dns/record:class",
        "//dometer/dns/record:type",
        "//dometer/dns/resolver:libresolv_helper",
        "//dometer/dns/resolver:libresolv_resolver",
        "//dometer/util:error",
        ":basic_server",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "mock_server",
    hdrs = ["mock_server.hpp"],
    deps = [
        "@com_github_google_googletest//:gtest",
        "//dometer/util:error",
        "//std/x:variant",
        ":server",
    ],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "options",
    hdrs = ["options.hpp"],
    deps = [
        ":transport_options",
    ],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "server",
    hdrs = ["server.hpp"],
    deps = [
        "//dometer/util:error",
        "//std/x:expected",
    ],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "transport_options",
    hdrs = ["transport_options.hpp"],
    visibility = ["//visibility:public"]
)
