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

cc_library(
    name = "transport_options",
    hdrs = ["transport_options.hpp"],
    visibility = ["//visibility:public"]
)
