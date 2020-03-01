cc_library(
    name = "class_label",
    deps = [
        "//dometer/dns:class",
        "//dometer/metrics:label",
    ],
    hdrs = ["class_label.hpp"],
    srcs = ["class_label.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "labels",
    deps = [
        "//dometer/metrics:label",
        ":class_label",
        ":type_label",
    ],
    hdrs = ["labels.hpp"],
    srcs = ["labels.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "lookup_observation",
    deps = [
        "//dometer/dns:class",
        "//dometer/dns:type",
        "//dometer/dns:rcode",
        "//dometer/metrics:labels",
        "//dometer/metrics:observation",
        "//dometer/metrics:unit",
        ":class_label",
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
        "//dometer/dns:class",
        "//dometer/dns:type",
        "//dometer/metrics:labels",
        "//dometer/metrics:summary",
        "//dometer/metrics:unit",
        ":class_label",
        ":labels",
        ":type_label",
    ],
    hdrs = ["lookup_summary.hpp"],
    srcs = ["lookup_summary.cpp"],
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
