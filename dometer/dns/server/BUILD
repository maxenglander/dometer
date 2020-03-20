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
    ],
    srcs = ["server.cpp"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "server_test",
    srcs = ["server_test.cpp"],
    deps = [
        "@com_github_google_googletest//:gtest_main",
        "//dometer/event:mock_emitter",
        "//dometer/dns:class",
        "//dometer/dns:qr",
        "//dometer/dns:opcode",
        "//dometer/dns:type",
        "//dometer/dns/event:any_event",
        "//dometer/dns/event:start_session_event",
        "//dometer/dns/event:stop_session_event",
        "//dometer/dns/handler:handler",
        "//dometer/dns/handler:mock_handler",
        "//dometer/dns/message:builder",
        "//dometer/dns/resolver:libresolv_helper",
        "//dometer/dns/resolver:libresolv_resolver",
        "//dometer/util:error",
        ":server",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "transport_options",
    hdrs = ["transport_options.hpp"],
    visibility = ["//visibility:public"]
)
