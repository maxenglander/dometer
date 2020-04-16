cc_library(
    name = "handler",
    hdrs = ["handler.hpp"],
    deps = [
        "//dometer/metrics:histogram",
        "//std/x:variant",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "handler_factory",
    hdrs = ["handler_factory.hpp"],
    srcs = ["handler_factory.cpp"],
    deps = [
        "//dometer/metrics/handler/prometheus:handler_factory",
        "//dometer/metrics/handler/prometheus:options",
        "//dometer/util:error",
        "//std/x:expected",
        "//std/x:variant",
        ":handler",
        ":options",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "options",
    hdrs = ["options.hpp"],
    deps = [
        "//dometer/metrics/handler/prometheus:options",
    ],
    visibility = ["//visibility:public"],
)
