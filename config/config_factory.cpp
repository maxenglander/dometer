#include "config/config.hpp"
#include "config/config_factory.hpp"
#include "config/dns/dns_factory.hpp"
#include "config/metrics/metrics_factory.hpp"
#include "rapidjson/document.h"

namespace dometer::config {
    ConfigFactory::ConfigFactory()
        :   ConfigFactory::ConfigFactory(dometer::config::dns::DnsFactory(),
                                         dometer::config::metrics::MetricsFactory()) {}

    ConfigFactory::ConfigFactory(dometer::config::dns::DnsFactory dnsFactory,
                                 dometer::config::metrics::MetricsFactory metricsFactory)
        :    dnsFactory(dnsFactory),
             metricsFactory(metricsFactory) {}

    Config ConfigFactory::fromJson(const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("dns"));
        assert(jsonValue["dns"].IsObject());
        assert(jsonValue.HasMember("metrics"));
        assert(jsonValue["metrics"].IsObject());
        return Config{
            dnsFactory.fromJson(jsonValue["dns"]),
            metricsFactory.fromJson(jsonValue["metrics"])
        };
    }
}
