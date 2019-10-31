workspace(name = "com_github_maxenglander_dometer")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
   name = "rules_foreign_cc",
   strip_prefix = "rules_foreign_cc-c3d5405cbc570257e7c9f75f902fab42241e6a53",
   url = "https://github.com/bazelbuild/rules_foreign_cc/archive/c3d5405cbc570257e7c9f75f902fab42241e6a53.zip",
   sha256 = "b30d354592980848dd1ecc120de3de34a7c574985e85b3ae2bcecd174fd007b8"
)

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")
rules_foreign_cc_dependencies()

http_archive(
    name = "com_github_TartanLlama_expected",
    urls = ["https://github.com/TartanLlama/expected/archive/v1.0.0.tar.gz"],
    sha256 = "8f5124085a124113e75e3890b4e923e3a4de5b26a973b891b3deb40e19c03cee",
    build_file = "@//external:BUILD.expected",
    strip_prefix = "expected-1.0.0",
)

http_archive(
    name = "com_github_TartanLlama_optional",
    urls = ["https://github.com/TartanLlama/optional/archive/v1.0.0.tar.gz"],
    sha256 = "e18941da05bca12a796ebbeacb83993bc0f10e817fa10bb45124a421c2384690",
    build_file = "@//external:BUILD.optional",
    strip_prefix = "optional-1.0.0",
)

http_archive(
    name = "com_github_jupp0r_prometheus_cpp",
    strip_prefix = "prometheus-cpp-0.7.0",
    urls = ["https://github.com/jupp0r/prometheus-cpp/archive/v0.7.0.zip"],
    sha256 = "7838b5cd44bbb921f3c85ddf508a20327f8ffe2cabdc18f7c640995215cf2127"
)

load("@com_github_jupp0r_prometheus_cpp//:repositories.bzl", "prometheus_cpp_repositories")
prometheus_cpp_repositories()

http_archive(
    name = "com_github_mpark_variant",
    strip_prefix = "variant-1.4.0",
    urls = ["https://github.com/mpark/variant/archive/v1.4.0.zip"],
    build_file = "@//external:BUILD.variant",
    sha256 = "84ea1369054e4d1c796b0e2c9318b2a88d633aace87272beefbb4278dcdf9df4"
)

http_archive(
    name = "net_sourceforge_asio_asio",
    urls = ["https://downloads.sourceforge.net/project/asio/asio/1.14.0%20%28Stable%29/asio-1.14.0.tar.gz"],
    sha256 = "807eccd586c7f454bfc7908b6d0ef47f1c379026333f926e8981ecb0318ccd7d",
    build_file = "@//external:BUILD.asio",
    strip_prefix = "asio-1.14.0",
)
