cc_library(
    name = "message_factory",
    hdrs = ["message_factory.hpp"],
    srcs = ["message_factory.cpp"],
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
    copts = [
        "-DBIND_8_COMPAT=1",
    ],
    srcs = ["message.cpp"],
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
    copts = [
        "-DBIND_8_COMPAT=1",
    ],
    srcs = ["parser.cpp"],
    visibility = ["//visibility:public"],
)
