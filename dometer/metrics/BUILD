cc_library(
    name = "example_histogram",
    deps = [
        ":histogram",
        ":unit",
    ],
    hdrs = ["example_histogram.hpp"],
    srcs = ["example_histogram.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "histogram",
    deps = [
        ":metric",
        ":type",
        ":unit",
    ],
    hdrs = ["histogram.hpp"],
    srcs = ["histogram.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "metric",
    deps = [
        ":type",
        ":unit",
    ],
    hdrs = ["metric.hpp"],
    srcs = ["metric.cpp"], 
    visibility = ["//visibility:public"],
)

cc_library(
    name = "mock_recorder",
    hdrs = ["mock_recorder.hpp"],
    deps = [
        "@com_github_google_googletest//:gtest",
        ":recorder",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "observation",
    hdrs = [
        "observation.hpp",
        "observation.ipp"
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "observation_builder",
    hdrs = [
        "observation_builder.hpp",
        "observation_builder.ipp"
    ],
    deps = [
        ":observation",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "options",
    hdrs = ["options.hpp"],
    deps = [
        "//dometer/metrics/handler:options",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "recorder",
    deps = [
        "//dometer/metrics/handler:handler",
        ":histogram",
    ],
    hdrs = ["recorder.hpp"],
    srcs = ["recorder.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "recorder_factory",
    deps = [
        "//dometer/metrics/handler:handler_factory",
        "//dometer/util:error",
        "//std/x:expected",
        ":options",
        ":recorder",
    ],
    hdrs = [
        "recorder_factory.hpp",
    ],
    srcs = ["recorder_factory.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "type",
    deps = [],
    hdrs = ["type.hpp"],
    srcs = [],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "unit",
    deps = [],
    hdrs = ["unit.hpp"],
    srcs = [],
    visibility = ["//visibility:public"],
)
