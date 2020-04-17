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
    name = "lookup_observation_builder",
    hdrs = [
        "lookup_observation_builder.hpp",
        "lookup_observation_builder.ipp"
    ],
    deps = [
        "//dometer/dns:class",
        "//dometer/dns:rcode",
        "//dometer/dns:type",
        "//dometer/dns/resolver:error",
        "//dometer/metrics:observation_builder",
        "//dometer/metrics:unit",
    ],
    visibility = ["//visibility:public"],
)
