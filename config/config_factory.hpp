#pragma once

#include "config/config.hpp"
#include "config/dns/dns_factory.hpp"
#include "config/metrics/metrics_factory.hpp"
#include "rapidjson/document.h"

namespace dometer::config {
    class ConfigFactory {
        public:
            ConfigFactory();
            ConfigFactory(dometer::config::dns::DnsFactory,
                          dometer::config::metrics::MetricsFactory);
            Config fromJson(const rapidjson::Value&) const;
        private:
            const dometer::config::dns::DnsFactory dnsFactory;
            const dometer::config::metrics::MetricsFactory metricsFactory;
    };
}
