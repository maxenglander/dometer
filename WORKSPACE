load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "expected",
    urls = ["https://github.com/TartanLlama/expected/archive/v1.0.0.tar.gz"],
    sha256 = "8f5124085a124113e75e3890b4e923e3a4de5b26a973b891b3deb40e19c03cee",
    build_file = "@//:BUILD.expected",
    strip_prefix = "expected-1.0.0",
)

http_archive(
    name = "jsoncpp",
    urls = ["https://github.com/open-source-parsers/jsoncpp/archive/1.8.4.tar.gz"],
    sha256 = "c49deac9e0933bcb7044f08516861a2d560988540b23de2ac1ad443b219afdb6",
    build_file = "@//:BUILD.jsoncpp",
    strip_prefix = "jsoncpp-1.8.4",
)
