genrule(
    name = "schema",
    srcs = ["schema.json", "schema.hpp.tpl"],
    outs = ["schema.hpp"],
    cmd = "cat $(location schema.hpp.tpl) | SCHEMA=$$(cat $(location schema.json)) envsubst > $@",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "validator",
    deps = [
        "@com_github_Tencent_rapidjson//:rapidjson",
        "@com_github_tristanpenman_valijson//:valijson",
        "//experimental:expected",
        "//util:error",
    ],
    hdrs = [":schema", "validator.hpp"],
    srcs = ["validator.cpp"],
    visibility = ["//visibility:public"],
)
