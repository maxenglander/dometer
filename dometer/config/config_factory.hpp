#pragma once

#include "dometer/config/config.hpp"
#include "dometer/config/dns/dns_parser.hpp"
#include "dometer/config/metrics/metrics_parser.hpp"
#include "jsoncpp/json.h"

namespace dometer::config {
    class ConfigParser {
        public:
            ConfigParser();
            ConfigParser(dometer::config::dns::DnsParser,
                          dometer::config::metrics::MetricsParser);
            Config fromJson(const Json::Value&) const;
        private:
            const dometer::config::dns::DnsParser dnsParser;
            const dometer::config::metrics::MetricsParser metricsParser;
    };
}
