cc_library(
    name = "dns",
    hdrs = ["dns.hpp"],
    deps = [
      "//config/dns/server:server",
      "//dns/resolver:options",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "dns_parser",
    hdrs = ["dns_parser.hpp"],
    srcs = ["dns_parser.cpp"],
    deps = [
      "//config/dns/resolver:resolver_parser",
      "//config/dns/server:server_parser",
      ":dns",
    ],
    visibility = ["//visibility:public"],
)
