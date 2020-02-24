cc_library(
    name = "array_helper",
    hdrs = ["array_helper.hpp", "array_helper.ipp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "callback",
    hdrs = ["callback.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "callback_registry",
    hdrs = ["callback_registry.hpp"],
    deps = [
        ":callback"
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "error",
    hdrs = ["error.hpp"],
    srcs = ["error.cpp"],
    deps = [
        "//std/x:optional",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "enum_hasher",
    hdrs = ["enum_hasher.hpp"],
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

cc_library(
    name = "string_helper",
    hdrs = ["string_helper.hpp"],
    srcs = ["string_helper.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "tuple_helper",
    hdrs = ["tuple_helper.hpp"],
    visibility = ["//visibility:public"],
)
