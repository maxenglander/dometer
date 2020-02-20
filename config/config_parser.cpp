#include <memory>

#include "config/config.hpp"
#include "config/dns/dns_parser.hpp"
#include "config/config_parser.hpp"
#include "config/metrics/metrics_parser.hpp"
#include "config/schema_validator.hpp"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include "util/error.hpp"
#include "x/expected.hpp"

using namespace std::x;
namespace util = dometer::util;

namespace dometer::config {
    ConfigParser::ConfigParser()
        : ConfigParser(dometer::config::dns::DnsParser(),
                       dometer::config::metrics::MetricsParser(),
                       SchemaValidator()) {}

    ConfigParser::ConfigParser(dometer::config::dns::DnsParser dnsParser,
                               dometer::config::metrics::MetricsParser metricsParser,
                               SchemaValidator schemaValidator)
        : dnsParser(dnsParser),
          metricsParser(metricsParser),
          schemaValidator(schemaValidator) {}

    expected<Config, util::Error> ConfigParser::fromJson(std::string json) {
        auto validation = schemaValidator.validate(json);
        if(!validation) {
            return unexpected<util::Error>(validation.error());
        } else {
            rapidjson::Value* jsonValue = (*validation).release();
            return fromJson(*jsonValue);
        }
    }

    Config ConfigParser::fromJson(const rapidjson::Value& jsonValue) const {
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
