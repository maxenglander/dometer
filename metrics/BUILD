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
    name = "descriptor",
    deps = [
        ":label",
        ":unit",
    ],
    hdrs = ["descriptor.hpp"],
    srcs = [],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "descriptors",
    deps = [
        ":descriptor",
        ":label",
        ":labels",
        ":unit",
    ],
    hdrs = ["descriptors.hpp"],
    srcs = ["descriptors.cpp"],
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
    name = "observation",
    deps = [
        ":descriptor",
    ],
    hdrs = ["observation.hpp"],
    srcs = [],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "observer",
    deps = [
        ":observation",
    ],
    hdrs = ["observer.hpp"],
    srcs = [],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "query_observation",
    deps = [
        ":descriptors",
        ":observation",
    ],
    hdrs = ["query_observation.hpp"],
    srcs = ["query_observation.cpp"],
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
    name = "unit",
    deps = [],
    hdrs = ["unit.hpp"],
    srcs = [],
    visibility = ["//visibility:public"],
)
