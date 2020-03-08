workspace(name = "com_github_maxenglander_dometer")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Bazel foreign rules
http_archive(
   name = "rules_foreign_cc",
   sha256 = "450563dc2938f38566a59596bb30a3e905fbbcc35b3fff5a1791b122bc140465",
   url = "https://github.com/bazelbuild/rules_foreign_cc/archive/456425521973736ef346d93d3d6ba07d807047df.zip",
   strip_prefix = "rules_foreign_cc-456425521973736ef346d93d3d6ba07d807047df",
)

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")
rules_foreign_cc_dependencies()

##########################################################################
### External libraries                                                 ###
##########################################################################

# c++11 compatible implementation of c++17 std::expected
http_archive(
    name = "com_github_TartanLlama_expected",
    urls = ["https://github.com/TartanLlama/expected/archive/v1.0.0.tar.gz"],
    sha256 = "8f5124085a124113e75e3890b4e923e3a4de5b26a973b891b3deb40e19c03cee",
    build_file = "@//external:BUILD.expected",
    strip_prefix = "expected-1.0.0",
)

# c++11 compatible implementation of c++17 std::optional
http_archive(
    name = "com_github_TartanLlama_optional",
    urls = ["https://github.com/TartanLlama/optional/archive/v1.0.0.tar.gz"],
    sha256 = "e18941da05bca12a796ebbeacb83993bc0f10e817fa10bb45124a421c2384690",
    build_file = "@//external:BUILD.optional",
    strip_prefix = "optional-1.0.0",
)

# c++11 compatible implementation of c++17 std::variant
http_archive(
    name = "com_github_mpark_variant",
    strip_prefix = "variant-1.4.0",
    urls = ["https://github.com/mpark/variant/archive/v1.4.0.zip"],
    build_file = "@//external:BUILD.variant",
    sha256 = "84ea1369054e4d1c796b0e2c9318b2a88d633aace87272beefbb4278dcdf9df4"
)

# Non-Boost Asio networking library
http_archive(
    name = "net_sourceforge_asio_asio",
    urls = ["https://downloads.sourceforge.net/project/asio/asio/1.14.0%20%28Stable%29/asio-1.14.0.tar.gz"],
    sha256 = "807eccd586c7f454bfc7908b6d0ef47f1c379026333f926e8981ecb0318ccd7d",
    build_file = "@//external:BUILD.asio",
    strip_prefix = "asio-1.14.0",
)

# Google test
http_archive(
    name = "com_github_google_googletest",
    url = "https://github.com/google/googletest/archive/release-1.10.0.zip",
    sha256 = "94c634d499558a76fa649edb13721dce6e98fb1e7018dfaeba3cd7a083945e91",
    build_file = "@//external:BUILD.googletest",
    strip_prefix = "googletest-release-1.10.0",
)

# JsonCpp  library
http_archive(
    name = "com_github_open-source-parsers_jsoncpp",
    urls = ["https://github.com/open-source-parsers/jsoncpp/archive/0.10.7.zip"],
    sha256 = "165b2ac2f17601b500bf01b0b9a3b304f620986e0da5d988397d64f8f3c942c3",
    build_file = "@//external:BUILD.jsoncpp",
    strip_prefix = "jsoncpp-0.10.7",
)

# Prometheus client library
http_archive(
    name = "com_github_jupp0r_prometheus_cpp",
    strip_prefix = "prometheus-cpp-0.7.0",
    urls = ["https://github.com/jupp0r/prometheus-cpp/archive/v0.7.0.zip"],
    sha256 = "7838b5cd44bbb921f3c85ddf508a20327f8ffe2cabdc18f7c640995215cf2127"
)
load("@com_github_jupp0r_prometheus_cpp//:repositories.bzl", "prometheus_cpp_repositories")
prometheus_cpp_repositories()

# RapidJSON library
http_archive(
    name = "com_github_Tencent_rapidjson",
    urls = ["https://github.com/Tencent/rapidjson/archive/v1.1.0.zip"],
    sha256 = "8e00c38829d6785a2dfb951bb87c6974fa07dfe488aa5b25deec4b8bc0f6a3ab",
    build_file = "@//external:BUILD.rapidjson",
    strip_prefix = "rapidjson-1.1.0",
)

# Resolve wrapper
http_archive(
    name = "org_samba_cwrap_resolv_wrapper",
    urls = ["https://ftp.samba.org/pub/cwrap/resolv_wrapper-1.1.5.tar.gz"],
    sha256 = "e989fdaa1385bdf3ef7dbcb83b3f7f15c69e78ca6432e254be390b7c63e1b06c",
    build_file = "@//external:BUILD.resolv_wrapper",
    strip_prefix = "resolv_wrapper-1.1.5",
)

# Valijson library
http_archive(
    name = "com_github_tristanpenman_valijson",
    urls = ["https://github.com/tristanpenman/valijson/archive/v0.2.zip"],
    sha256 = "b5fa1106ad388408b9352223716bbfdd5650b2258f0ac8c4afb3d9d70b0a5e4d",
    build_file = "@//external:BUILD.valijson",
    strip_prefix = "valijson-0.2",
)
