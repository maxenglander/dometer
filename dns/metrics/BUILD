cc_library(
    name = "labels",
    deps = [
        "//metrics:label",
        ":type_label",
    ],
    hdrs = ["labels.hpp"],
    srcs = ["labels.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "query_counter",
    deps = [
        "//dns:type",
        "//metrics:counter",
        "//metrics:labels",
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
        "//dns:type",
        "//metrics:observation",
        ":query_counter",
    ],
    hdrs = ["query_observation.hpp"],
    srcs = ["query_observation.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "reply_counter",
    deps = [
        "//metrics:counter",
        "//metrics:labels",
    ],
    hdrs = ["reply_counter.hpp"],
    srcs = ["reply_counter.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "reply_observation",
    deps = [
        "//metrics:observation",
        ":reply_counter",
    ],
    hdrs = ["reply_observation.hpp"],
    srcs = ["reply_observation.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "type_label",
    deps = [
        "//dns:type",
        "//metrics:label",
    ],
    hdrs = ["type_label.hpp"],
    srcs = ["type_label.cpp"],
    visibility = ["//visibility:public"],
)
