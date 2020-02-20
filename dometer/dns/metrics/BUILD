cc_library(
    name = "labels",
    deps = [
        "//dometer/metrics:label",
        ":type_label",
    ],
    hdrs = ["labels.hpp"],
    srcs = ["labels.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "lookup_observation",
    deps = [
        "//dometer/dns:type",
        "//dometer/metrics:labels",
        "//dometer/metrics:observation",
        "//dometer/metrics:unit",
        ":labels",
        ":lookup_summary",
        ":type_label",
    ],
    hdrs = ["lookup_observation.hpp"],
    srcs = ["lookup_observation.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "lookup_summary",
    deps = [
        "//dometer/dns:type",
        "//dometer/metrics:labels",
        "//dometer/metrics:summary",
        "//dometer/metrics:unit",
        ":labels",
        ":type_label",
    ],
    hdrs = ["lookup_summary.hpp"],
    srcs = ["lookup_summary.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "query_counter",
    deps = [
        "//dometer/dns:type",
        "//dometer/metrics:counter",
        "//dometer/metrics:labels",
        ":labels",
        ":type_label",
    ],
    hdrs = ["query_counter.hpp"],
    srcs = ["query_counter.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "query_observation",
    deps = [
        "//dometer/dns:type",
        "//dometer/metrics:observation",
        ":query_counter",
    ],
    hdrs = ["query_observation.hpp"],
    srcs = ["query_observation.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "reply_counter",
    deps = [
        "//dometer/metrics:counter",
        "//dometer/metrics:labels",
    ],
    hdrs = ["reply_counter.hpp"],
    srcs = ["reply_counter.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "reply_observation",
    deps = [
        "//dometer/metrics:observation",
        ":reply_counter",
    ],
    hdrs = ["reply_observation.hpp"],
    srcs = ["reply_observation.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "type_label",
    deps = [
        "//dometer/dns:type",
        "//dometer/metrics:label",
    ],
    hdrs = ["type_label.hpp"],
    srcs = ["type_label.cpp"],
    visibility = ["//visibility:public"],
)
