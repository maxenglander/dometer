cc_library(
    name = "config",
    hdrs = ["config.hpp"],
    deps = [
        "//dometer/config/dns:dns",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "config_parser",
    hdrs = ["config_parser.hpp"],
    srcs = ["config_parser.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        "//std/x:expected",
        "//dometer/util:error",
        ":config",
        ":internal_config_parser",
        ":schema_validator",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "internal_config_parser",
    hdrs = ["internal_config_parser.hpp"],
    srcs = ["internal_config_parser.cpp"],
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        "//dometer/config/dns:dns_parser",
        "//dometer/config/metrics:metrics_parser",
        "//std/x:expected",
        "//dometer/util:error",
        ":config",
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
        "//std/x:expected",
        "//dometer/util:error",
    ],
    hdrs = [
        ":schema",
        "schema_validator.hpp",
    ],
    srcs = ["schema_validator.cpp"],
    visibility = ["//visibility:public"],
)
