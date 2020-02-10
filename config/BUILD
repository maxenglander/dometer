cc_library(
    name = "config",
    hdrs = ["config.hpp"],
    deps = [
        "//config/dns:dns",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "config_factory",
    hdrs = ["config_factory.hpp"],
    srcs = ["config_factory.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        "//config/dns:dns_factory",
        "//config/metrics:metrics_factory",
        ":config",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "config_parser",
    hdrs = ["config_parser.hpp"],
    srcs = ["config_parser.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        "//x:expected",
        "//util:error",
        ":config",
        ":config_factory",
        ":schema_validator",
    ],
    visibility = ["//visibility:public"],
)

genrule(
    name = "schema",
    srcs = ["schema.json", "schema.hpp.tpl"],
    outs = ["schema.hpp"],
    cmd = "cat $(location schema.hpp.tpl) | SCHEMA=$$(cat $(location schema.json)) envsubst > $@",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "schema_validator",
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        "@com_github_tristanpenman_valijson//:valijson",
        "//x:expected",
        "//util:error",
    ],
    hdrs = [
        ":schema",
        "schema_validator.hpp",
    ],
    srcs = ["schema_validator.cpp"],
    visibility = ["//visibility:public"],
)
