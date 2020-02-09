#pragma once

#include "config/config.hpp"
#include "config/dns/dns_factory.hpp"
#include "rapidjson/document.h"

namespace dometer::config {
    class ConfigFactory {
        public:
            ConfigFactory();
            ConfigFactory(dometer::config::dns::DnsFactory);
            Config fromJson(const rapidjson::Value&) const;
        private:
            const dometer::config::dns::DnsFactory dnsFactory;
    };
}
