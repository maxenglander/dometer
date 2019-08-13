cc_library(
  name = "unix_socket_backend",
  hdrs = ["unix_socket_backend.h"],
  srcs = ["unix_socket_backend.cc"],
  deps = [
      "//network/socket:socket_factory",
      "//network/socket:unix_socket",
      "//std/experimental:expected",
      "//util:read_until",
  ],
  visibility = ["//visibility:public"],
)
