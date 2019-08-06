cc_library(
    name = "answer",
    hdrs = ["answer.h"],
    srcs = ["answer.cc"],
)

cc_library(
    name = "query",
    hdrs = ["query.h"],
    srcs = ["query.cc"],
)

cc_library(
    name = "resolver",
    hdrs = ["resolver.h"],
    srcs = ["resolver.cc"],
    deps = ["//std/experimental:expected", ":query", ":result"],
    linkopts = ["-lresolv"],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "result",
    hdrs = ["result.h"],
    srcs = ["result.cc"],
    deps = [":answer"],
)
