cc_library(
    name = "libresolv",
    hdrs = ["libresolv.hpp"],
    deps = [],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "libresolv_parser",
    hdrs = ["libresolv_parser.hpp"],
    srcs = ["libresolv_parser.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        "//dns/resolver:libresolv_function",
        "//dns/resolver:libresolv_options",
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
    name = "resolver_parser",
    hdrs = ["resolver_parser.hpp"],
    srcs = ["resolver_parser.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        "//x:optional",
        "//dns/resolver:options",
        ":libresolv_parser",
        ":resolver",
    ],
    visibility = ["//visibility:public"],
)
