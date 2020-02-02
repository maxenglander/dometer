cc_library(
    name = "schema",
    hdrs = ["schema.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "validator",
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        "@com_github_tristanpenman_valijson//:valijson",
        "//experimental:expected",
        "//util:error",
        ":schema",
    ],
    hdrs = ["validator.hpp"],
    srcs = ["validator.cpp"],
    visibility = ["//visibility:public"],
)
