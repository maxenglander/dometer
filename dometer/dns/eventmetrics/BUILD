cc_library(
    name = "metric_recording_event_functor",
    hdrs = ["metric_recording_event_functor.hpp"],
    srcs = ["metric_recording_event_functor.cpp"],
    deps = [
        "//dometer/dns/event:any_event",
        "//dometer/dns/event:parse_query_event",
        "//dometer/dns/event:parse_reply_event",
        "//dometer/dns/event:resolve_query_event",
        "//dometer/dns/event:session",
        "//dometer/dns/event:start_session_event",
        "//dometer/dns/event:stop_session_event",
        "//dometer/dns/metrics:lookup_summary",
        "//dometer/dns/resolver:error_code",
        "//dometer/metrics:recorder",
        "//std/x:variant",
    ],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "metric_recording_event_functor_test",
    srcs = ["metric_recording_event_functor_test.cpp"],
    deps = [
        "@com_github_google_googletest//:gtest_main",
        ":metric_recording_event_functor",
    ],
)

