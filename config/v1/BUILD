load("//:bzl/cc_gen_data_class.bzl", "cc_gen_data_class")

cc_gen_data_class(
    name = "schema",
    class_name = "Schema",
    function_name = "value",
    in_src = "schema.json",
    namespace = "dometer::config::v1",
    out_hdr = "schema.hpp",
    out_src = "schema.cpp",
)
