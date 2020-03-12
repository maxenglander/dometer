cc_library(
    name = "builder",
    deps = [
        "//std/x:unique",
        ":file",
        ":resolv_wrapper",
        ":wrap_mode",
    ],
    hdrs = ["builder.hpp"],
    srcs = ["builder.cpp"],
    visibility = [
        "//visibility:public",
    ],
)

cc_library(
    name = "file",
    hdrs = ["file.hpp"],
    srcs = ["file.cpp"],
    visibility = [
        "//visibility:public",
    ],
)

cc_library(
    name = "resolv_wrapper",
    deps = [
        "@org_samba_cwrap_resolv_wrapper//:resolv_wrapper",
        ":file",
        ":wrap_mode",
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
        ":builder",
        ":resolv_wrapper",
        ":wrap_mode",
    ],
    copts = ["-DBIND_8_COMPAT"],
    linkopts = ["-lresolv"],
    srcs = ["resolv_wrapper_test.cpp"],
)

cc_library(
    name = "wrap_mode",
    hdrs = ["wrap_mode.hpp"],
    visibility = [
        "//visibility:public",
    ],
)
