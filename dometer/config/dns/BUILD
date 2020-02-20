cc_library(
    name = "dns",
    hdrs = ["dns.hpp"],
    deps = [
      "//dometer/dns/resolver:options",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "dns_parser",
    hdrs = ["dns_parser.hpp"],
    srcs = ["dns_parser.cpp"],
    deps = [
      "//dometer/config/dns/resolver:resolver_parser",
      "//dometer/config/dns/server:server_parser",
      ":dns",
    ],
    visibility = ["//visibility:public"],
)
