#include "config/dns/dns.hpp"
#include "config/dns/dns_factory.hpp"
#include "config/dns/server/server.hpp"
#include "config/dns/server/server_factory.hpp"
#include "rapidjson/document.h"

namespace dometer::config::dns {
    DnsFactory::DnsFactory() : DnsFactory::DnsFactory(dometer::config::dns::server::ServerFactory()) {}

    DnsFactory::DnsFactory(dometer::config::dns::server::ServerFactory serverFactory) : serverFactory(serverFactory) {}

    Dns DnsFactory::fromJson(const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("server"));
        assert(jsonValue["server"].IsObject());
        return Dns{
            serverFactory.fromJson(jsonValue["server"])
        };
    }
}
