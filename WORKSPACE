load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_github_TartanLlama_expected",
    urls = ["https://github.com/TartanLlama/expected/archive/v1.0.0.tar.gz"],
    sha256 = "8f5124085a124113e75e3890b4e923e3a4de5b26a973b891b3deb40e19c03cee",
    build_file = "@//external:BUILD.expected",
    strip_prefix = "expected-1.0.0",
)

http_archive(
    name = "com_github_open-source-parsers_jsoncpp",
    urls = ["https://github.com/open-source-parsers/jsoncpp/archive/1.8.4.tar.gz"],
    sha256 = "c49deac9e0933bcb7044f08516861a2d560988540b23de2ac1ad443b219afdb6",
    build_file = "@//external:BUILD.jsoncpp",
    strip_prefix = "jsoncpp-1.8.4",
)

http_archive(
    name = "com_github_jupp0r_prometheus_cpp",
    strip_prefix = "prometheus-cpp-0.7.0",
    urls = ["https://github.com/jupp0r/prometheus-cpp/archive/v0.7.0.zip"],
)

load("@com_github_jupp0r_prometheus_cpp//:repositories.bzl", "prometheus_cpp_repositories")
prometheus_cpp_repositories()
