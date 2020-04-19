cc_library(
    name = "builder",
    hdrs = ["builder.hpp"],
    srcs = ["builder.cpp"],
    deps = [
        "//dometer/dns/message:qr",
        "//dometer/dns/message:question",
        "//dometer/dns/message:rcode",
        "//dometer/dns/record:record",
        "//dometer/util:error",
        "//std/x:expected",
        ":message",
        ":parser",
    ],
    copts = [
        "-DBIND_8_COMPAT",
    ],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "builder_test",
    srcs = ["builder_test.cpp"],
    deps = [
        "@com_github_google_googletest//:gtest_main",
        "//dometer/dns/message:opcode",
        "//dometer/dns/message:rcode",
        "//dometer/util:human_friendly_error_encoder",
        ":builder",
        ":message",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "message",
    hdrs = ["message.hpp"],
    deps = [
        "//dometer/dns/message:opcode",
        "//dometer/dns/message:qr",
        "//dometer/dns/message:question",
        "//dometer/dns/message:rcode",
        "//dometer/dns/record:class",
        "//dometer/dns/record:record",
        "//dometer/dns/record:type",
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
    name = "message_factory",
    hdrs = ["message_factory.hpp"],
    srcs = ["message_factory.cpp"],
    deps = [
        "//dometer/dns/message:builder",
        "//dometer/dns/message:opcode",
        "//dometer/dns/message:qr",
        "//dometer/dns/message:question",
        "//dometer/dns/message:rcode",
        "//dometer/dns/record:class",
        "//dometer/dns/record:record",
        "//dometer/dns/record:type",
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
    name = "opcode",
    hdrs = ["opcode.hpp"],
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
    linkopts = [
        "-lresolv",
    ],
    srcs = ["parser.cpp"],
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
        "//dometer/dns/record:class",
        "//dometer/dns/record:type",
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
