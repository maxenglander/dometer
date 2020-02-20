#pragma once

#include "config/config.hpp"
#include "config/dns/dns_parser.hpp"
#include "config/metrics/metrics_parser.hpp"
#include "rapidjson/document.h"

namespace dometer::config {
    class ConfigParser {
        public:
            ConfigParser();
            ConfigParser(dometer::config::dns::DnsParser,
                          dometer::config::metrics::MetricsParser);
            Config fromJson(const rapidjson::Value&) const;
        private:
            const dometer::config::dns::DnsParser dnsParser;
            const dometer::config::metrics::MetricsParser metricsParser;
    };
}
