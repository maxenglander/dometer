cc_library(
    name = "libresolv",
    hdrs = ["libresolv.hpp"],
    deps = [],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "libresolv_factory",
    hdrs = ["libresolv_factory.hpp"],
    srcs = ["libresolv_factory.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        ":libresolv",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "resolver",
    hdrs = ["resolver.hpp"],
    deps = [
        "//x:optional",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "resolver_factory",
    hdrs = ["resolver_factory.hpp"],
    srcs = ["resolver_factory.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        "//x:optional",
        ":libresolv_factory",
        ":resolver",
    ],
    visibility = ["//visibility:public"],
)
