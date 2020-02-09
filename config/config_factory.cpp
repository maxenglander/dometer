#include "config/config.hpp"
#include "config/config_factory.hpp"
#include "config/dns/dns_factory.hpp"
#include "rapidjson/document.h"

namespace dometer::config {
    ConfigFactory::ConfigFactory() : ConfigFactory::ConfigFactory(dometer::config::dns::DnsFactory()) {}

    ConfigFactory::ConfigFactory(dometer::config::dns::DnsFactory dnsFactory) : dnsFactory(dnsFactory) {}

    Config ConfigFactory::fromJson(const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("dns"));
        assert(jsonValue["dns"].IsObject());
        return Config{
            dnsFactory.fromJson(jsonValue["dns"])
        };
    }
}
