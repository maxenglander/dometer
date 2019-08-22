cc_library(
    name = "answer",
    hdrs = ["answer.h"],
    srcs = ["answer.cc"],
)

cc_library(
    name = "native_resolver",
    hdrs = ["native_resolver.h"],
    srcs = ["native_resolver.cc"],
    deps = ["//std/experimental:expected", ":result"],
    linkopts = ["-lresolv"],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "result",
    hdrs = ["result.h"],
    srcs = ["result.cc"],
    deps = [":answer"],
)
