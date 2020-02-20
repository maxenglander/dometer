#pragma once

#include <memory>
#include <string>

#include "config/config.hpp"
#include "config/dns/dns_parser.hpp"
#include "config/metrics/metrics_parser.hpp"
#include "config/schema_validator.hpp"
#include "rapidjson/document.h"
#include "util/error.hpp"
#include "x/expected.hpp"

using namespace std::x;
namespace util = dometer::util;

namespace dometer::config {
    class ConfigParser {
        public:
            ConfigParser();
            ConfigParser(dometer::config::dns::DnsParser,
                         dometer::config::metrics::MetricsParser,
                         SchemaValidator);
            expected<Config, util::Error> fromJson(std::string);
        protected:
            Config fromJson(const rapidjson::Value&) const;
        private:
            const dometer::config::dns::DnsParser dnsParser;
            const dometer::config::metrics::MetricsParser metricsParser;
            SchemaValidator schemaValidator;
    };
}
