cc_library(
    name = "class",
    deps = [],
    hdrs = ["class.hpp"],
    srcs = ["class.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "header",
    deps = [],
    hdrs = ["header.hpp"],
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
    ],
    linkopts = ["-lresolv"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "packet",
    hdrs = ["packet.hpp"],
    deps = [
        "//experimental:expected",
        "//util:error",
        ":class",
        ":header",
        ":question",
        ":type",
    ],
    srcs = ["packet.cpp"],
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
    name = "type",
    deps = [],
    hdrs = ["type.hpp"],
    srcs = ["type.cpp"],
    visibility = ["//visibility:public"],
)
