cc_library(
    name = "class",
    deps = [],
    hdrs = ["class.hpp"],
    srcs = ["class.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "native_resolver",
    hdrs = ["native_resolver.hpp"],
    srcs = ["native_resolver.cpp"],
    deps = [
        "//experimental:expected",
        "//util:error",
        ":packet",
        ":resolution_mode",
    ],
    linkopts = ["-lresolv"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "opcode",
    deps = [],
    hdrs = ["opcode.hpp"],
    srcs = [],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "packet",
    hdrs = ["packet.hpp"],
    deps = [
        "//experimental:expected",
        "//util:error",
        ":class",
        ":opcode",
        ":qr",
        ":question",
        ":rcode",
        ":type",
    ],
    srcs = ["packet.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "qr",
    deps = [],
    hdrs = ["qr.hpp"],
    srcs = [],
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
    deps = [],
    hdrs = ["rcode.hpp"],
    srcs = [],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "resolution_mode",
    deps = [],
    hdrs = ["resolution_mode.hpp"],
    srcs = [],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "type",
    deps = [],
    hdrs = ["type.hpp"],
    srcs = ["type.cpp"],
    visibility = ["//visibility:public"],
)
