cc_library(
    name = "error",
    hdrs = ["error.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "json_serde",
    hdrs = ["json_serde.hpp"],
    srcs = ["json_serde.cc"],
    deps = [
        "@com_github_open-source-parsers_jsoncpp//:jsoncpp",
        "//std/experimental:expected",
    ],
    visibility = ["//visibility:public"],
)
