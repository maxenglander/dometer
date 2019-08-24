cc_library(
    name = "answer",
    hdrs = ["answer.h"],
)

cc_library(
    name = "header",
    hdrs = ["header.h"],
)

cc_library(
    name = "native_resolver",
    hdrs = ["native_resolver.h"],
    srcs = ["native_resolver.cc"],
    deps = [
        "//std/experimental:expected",
        "//util:error",
        ":answer",
        ":header",
        ":response",
    ],
    linkopts = ["-lresolv"],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "response",
    hdrs = ["response.h"],
    deps = [
        ":answer",
        ":header",
    ]
)
