cc_library(
    name = "parser",
    hdrs = ["parser.hpp"],
    srcs = ["parser.cpp"],
    deps = [
        "@com_github_open-source-parsers_jsoncpp//:jsoncpp",
        "//dometer/app:options",
        "//dometer/util:error",
        "//std/x:expected",
        "//std/x:unique",
        ":internal_parser",
        ":schema_validator",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "internal_parser",
    hdrs = ["internal_parser.hpp"],
    srcs = ["internal_parser.cpp"],
    deps = [
        "@com_github_open-source-parsers_jsoncpp//:jsoncpp",
        "//dometer/app:options",
        "//dometer/config/dns:parser",
        "//dometer/config/metrics:parser",
        "//dometer/util:error",
        "//std/x:expected",
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
        "@com_github_open-source-parsers_jsoncpp//:jsoncpp",
        "@com_github_tristanpenman_valijson//:valijson",
        "//dometer/util:error",
        "//dometer/util:string_helper",
        "//std/x:expected",
        "//std/x:unique",
    ],
    hdrs = [
        ":schema",
        "schema_validator.hpp",
    ],
    srcs = ["schema_validator.cpp"],
    visibility = ["//visibility:public"],
)
