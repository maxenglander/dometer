#include <memory>

#include "dometer/config/config.hpp"
#include "dometer/config/internal_config_parser.hpp"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include "dometer/util/error.hpp"
#include "std/x/expected.hpp"

using namespace std::x;
namespace util = dometer::util;

namespace dometer::config {
    InternalConfigParser::InternalConfigParser()
        : InternalConfigParser(dometer::config::dns::DnsParser(),
                       dometer::config::metrics::MetricsParser()) {}

    InternalConfigParser::InternalConfigParser(dometer::config::dns::DnsParser dnsParser,
                               dometer::config::metrics::MetricsParser metricsParser)
        : dnsParser(dnsParser),
          metricsParser(metricsParser) {}

    Config InternalConfigParser::fromJson(const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("dns"));
        assert(jsonValue["dns"].IsObject());
        assert(jsonValue.HasMember("metrics"));
        assert(jsonValue["metrics"].IsObject());
        return Config{
            dnsParser.fromJson(jsonValue["dns"]),
            metricsParser.fromJson(jsonValue["metrics"])
        };
    }
}
