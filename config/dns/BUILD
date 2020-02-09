cc_library(
    name = "dns",
    hdrs = ["dns.hpp"],
    deps = [
      "//config/dns/server:server",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "dns_factory",
    hdrs = ["dns_factory.hpp"],
    srcs = ["dns_factory.cpp"],
    deps = [
      "//config/dns/resolver:resolver_factory",
      "//config/dns/server:server_factory",
      ":dns",
    ],
    visibility = ["//visibility:public"],
)
