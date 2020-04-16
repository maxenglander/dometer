cc_library(
    name = "class",
    hdrs = ["class.hpp"],
    srcs = ["class.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "opcode",
    hdrs = ["opcode.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "options",
    hdrs = ["options.hpp"],
    deps = [
      "//dometer/dns/resolver:options",
      "//dometer/dns/server:options",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "qr",
    hdrs = ["qr.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "question",
    deps = [
        ":class",
        ":type",
    ],
    hdrs = ["question.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "rcode",
    hdrs = ["rcode.hpp"],
    srcs = ["rcode.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "record",
    hdrs = ["record.hpp"],
    deps = [
        ":type",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "type",
    hdrs = ["type.hpp"],
    srcs = ["type.cpp"],
    visibility = ["//visibility:public"],
)
