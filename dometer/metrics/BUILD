cc_library(
    name = "boolean_label",
    deps = [
        ":label"
    ],
    hdrs = ["boolean_label.hpp"],
    srcs = ["boolean_label.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "counter",
    deps = [
        ":metric",
    ],
    hdrs = ["counter.hpp"],
    srcs = ["counter.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "example_counter",
    deps = [
        ":counter",
    ],
    hdrs = ["example_counter.hpp"],
    srcs = ["example_counter.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "label",
    deps = [],
    hdrs = ["label.hpp"],
    srcs = [],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "label_helper",
    deps = [
        "//dometer/util:tuple_helper",
        ":label"
    ],
    hdrs = [
        "label_helper.hpp",
        "label_helper.ipp",
    ],
    srcs = [],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "labels",
    deps = [
        ":boolean_label",
        ":label",
        ":string_label",
    ],
    hdrs = ["labels.hpp"],
    srcs = ["labels.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "metric",
    deps = [
        ":label",
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
        ":counter",
        ":recorder",
        ":summary",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "options",
    hdrs = ["options.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "recorder",
    deps = [
        "//dometer/metrics/handler:handler",
        ":counter",
        ":summary",
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
    name = "string_label",
    deps = [
        ":label"
    ],
    hdrs = ["string_label.hpp"],
    srcs = ["string_label.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "summary",
    deps = [
        ":label",
        ":metric",
        ":type",
        ":unit",
    ],
    hdrs = ["summary.hpp"],
    srcs = ["summary.cpp"],
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
