cc_library(
    name = "array_helper",
    hdrs = ["array_helper.hpp", "array_helper.ipp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "error",
    hdrs = ["error.hpp"],
    srcs = ["error.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "error_encoder",
    hdrs = ["error_encoder.hpp"],
    deps = [
        ":error",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "human_friendly_error_encoder",
    hdrs = ["human_friendly_error_encoder.hpp"],
    srcs = ["human_friendly_error_encoder.cpp"],
    deps = [
        ":error",
        ":error_encoder",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "lru_map",
    hdrs = [
        "lru_map.hpp",
        "lru_map.ipp",
    ],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "lru_map_test",
    srcs = ["lru_map_test.cpp"],
    deps = [
        "@com_github_google_googletest//:gtest_main",
        ":lru_map", 
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "string_helper",
    hdrs = ["string_helper.hpp"],
    srcs = ["string_helper.cpp"],
    visibility = ["//visibility:public"],
)
