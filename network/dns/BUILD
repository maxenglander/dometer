cc_library(
    name = "answer",
    hdrs = ["answer.hpp"],
)

cc_library(
    name = "header",
    hdrs = ["header.hpp"],
)

cc_library(
    name = "native_resolver",
    hdrs = ["native_resolver.hpp"],
    srcs = ["native_resolver.cpp"],
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
    hdrs = ["response.hpp"],
    deps = [
        ":answer",
        ":header",
    ]
)
