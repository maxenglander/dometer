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
    name = "counter_descriptor",
    deps = [
        ":descriptor",
        ":label",
        ":type",
        ":unit",
    ],
    hdrs = [
        "counter_descriptor.hpp",
        "counter_descriptor.ipp",
    ],
    srcs = [],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "descriptor",
    deps = [
        ":label",
        ":type",
        ":unit",
    ],
    hdrs = [
        "descriptor.hpp",
        "descriptor.ipp",
    ],
    srcs = [],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "descriptors",
    deps = [
        ":counter_descriptor",
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
    name = "handler",
    deps = [
        ":observation"
    ],
    hdrs = ["handler.hpp"],
    srcs = [],
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
        "//util:tuple_helper",
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
    name = "noop_handler",
    deps = [
        ":handler",
        ":observation",
    ],
    hdrs = ["noop_handler.hpp"],
    srcs = [],
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
        ":handler",
        ":observation",
    ],
    hdrs = [
        "observer.hpp",
        "observer.ipp",
    ],
    srcs = [
        "observer.cpp",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "prometheus_handler",
    deps = [
        "@com_github_jupp0r_prometheus_cpp//core",
        "@com_github_jupp0r_prometheus_cpp//pull",
        "@com_github_jupp0r_prometheus_cpp//push",
        ":descriptor",
        ":label_helper",
        ":observation",
    ],
    hdrs = [
        "prometheus_handler.hpp",
        "prometheus_handler.ipp",
    ],
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
