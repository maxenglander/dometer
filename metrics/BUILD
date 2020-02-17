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
    name = "metrics",
    deps = [
        ":counter_metric",
        ":metric",
        ":label",
        ":labels",
        ":unit",
    ],
    hdrs = ["metrics.hpp"],
    srcs = ["metrics.cpp"],
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
    name = "observer",
    deps = [
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
    name = "options",
    hdrs = ["options.hpp"],
    deps = [
        ":prometheus_options",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "prometheus_handler",
    deps = [
        "@com_github_jupp0r_prometheus_cpp//core",
        "//x:expected",
        "//x:variant",
        "//util:error",
        "//util:lru_map",
        ":counter",
        ":metric",
        ":label_helper",
        ":observation",
        ":prometheus_lru_map",
        ":prometheus_types",
        ":summary",
    ],
    hdrs = [
        "prometheus_handler.hpp",
        "prometheus_handler.ipp",
    ],
    srcs = ["prometheus_handler.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "prometheus_lru_map",
    deps = [
        "@com_github_jupp0r_prometheus_cpp//core",
        "//x:variant",
        "//util:lru_map",
        ":prometheus_types",
    ],
    hdrs = [
        "prometheus_lru_map.hpp",
    ],
    srcs = ["prometheus_lru_map.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "prometheus_handler_factory",
    hdrs = ["prometheus_handler_factory.hpp"],
    srcs = ["prometheus_handler_factory.cpp"],
    deps = [
        ":prometheus_handler",
        ":prometheus_options",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "prometheus_options",
    deps = [
        "//x:variant",
        ":prometheus_transport_options",
    ],
    hdrs = ["prometheus_options.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "prometheus_pull_transport_options",
    deps = [],
    hdrs = ["prometheus_pull_transport_options.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "prometheus_transport_options",
    deps = [
        "//x:variant",
        ":prometheus_pull_transport_options",
    ],
    hdrs = ["prometheus_transport_options.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "prometheus_types",
    deps = [
        "@com_github_jupp0r_prometheus_cpp//core"
    ],
    hdrs = [
        "prometheus_types.hpp",
    ],
    srcs = [],
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
