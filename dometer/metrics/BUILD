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
        ":label",
        ":metric",
        ":type",
        ":unit",
    ],
    hdrs = [
        "counter.hpp",
        "counter.ipp",
    ],
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
    hdrs = [
        "metric.hpp",
        "metric.ipp",
    ],
    srcs = [],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "observer",
    deps = [
        "//dometer/metrics/handler:handler",
        ":counter",
        ":observation",
        ":summary",
    ],
    hdrs = [
        "observer.hpp",
        "observer.ipp",
    ],
    srcs = ["observer.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "observer_factory",
    deps = [
        "//dometer/metrics/handler:handler_factory",
        ":observer",
        ":options",
    ],
    hdrs = [
        "observer_factory.hpp",
    ],
    srcs = ["observer_factory.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "observation",
    deps = [
        ":metric",
    ],
    hdrs = [
        "observation.hpp",
        "observation.ipp",
    ],
    srcs = [],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "options",
    hdrs = ["options.hpp"],
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
    hdrs = [
        "summary.hpp",
        "summary.ipp",
    ],
    srcs = [],
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
