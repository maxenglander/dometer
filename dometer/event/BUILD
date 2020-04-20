cc_library(
    name = "callback",
    hdrs = ["callback.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "emitter",
    hdrs = ["emitter.hpp", "emitter.ipp"],
    deps = [
        ":callback"
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "mock_emitter",
    hdrs = ["mock_emitter.hpp"],
    deps = [
        "@com_github_google_googletest//:gtest",
        ":emitter",
    ],
    visibility = ["//visibility:public"],
)
