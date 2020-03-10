cc_library(
    name = "resolv_wrapper",
    deps = [
        "@org_samba_cwrap_resolv_wrapper//:resolv_wrapper",
        "//dometer/util:error",
        "//std/x:expected",
    ],
    hdrs = ["resolv_wrapper.hpp"],
    srcs = ["resolv_wrapper.cpp"],
    visibility = [
        "//visibility:public",
    ],
)

cc_test(
    name = "resolv_wrapper_test",
    deps = [
        "@com_github_google_googletest//:gtest_main",
        ":resolv_wrapper",
    ],
    srcs = ["resolv_wrapper_test.cpp"],
)
