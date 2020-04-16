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
    name = "lookup_histogram",
    deps = [
        "//dometer/metrics:histogram",
        "//dometer/metrics:unit",
    ],
    hdrs = ["lookup_histogram.hpp"],
    srcs = ["lookup_histogram.cpp"],
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
