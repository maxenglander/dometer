cc_library(
    name = "factory",
    hdrs = ["factory.hpp"],
    deps = [
        "//dometer/dns:class",
        "//dometer/dns:opcode",
        "//dometer/dns:qr",
        "//dometer/dns:question",
        "//dometer/dns:rcode",
        "//dometer/dns:type",
        "//dometer/util:array_helper",
        "//dometer/util:error",
        "//std/x:expected",
        "//std/x:unique",
        ":message",
        ":parser",
    ],
    srcs = ["factory.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "parser",
    hdrs = ["parser.hpp"],
    deps = [
        "//dometer/util:array_helper",
        "//dometer/util:error",
        "//std/x:expected",
        "//std/x:unique",
        ":message",
    ],
    srcs = ["parser.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "message",
    hdrs = ["message.hpp"],
    deps = [
        "//dometer/dns:class",
        "//dometer/dns:opcode",
        "//dometer/dns:qr",
        "//dometer/dns:question",
        "//dometer/dns:rcode",
        "//dometer/dns:type",
        "//dometer/util:array_helper",
        "//dometer/util:error",
        "//std/x:expected",
        "//std/x:unique",
    ],
    srcs = ["message.cpp"],
    visibility = ["//visibility:public"],
)
