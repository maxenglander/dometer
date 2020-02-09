#include "config/dns/dns.hpp"
#include "config/dns/dns_factory.hpp"
#include "config/dns/resolver/resolver_factory.hpp"
#include "config/dns/server/server_factory.hpp"
#include "rapidjson/document.h"

namespace dometer::config::dns {
    DnsFactory::DnsFactory()
        : DnsFactory::DnsFactory(dometer::config::dns::resolver::ResolverFactory(),
                                 dometer::config::dns::server::ServerFactory()) {}

    DnsFactory::DnsFactory(dometer::config::dns::resolver::ResolverFactory resolverFactory,
                           dometer::config::dns::server::ServerFactory serverFactory)
        : resolverFactory(resolverFactory), serverFactory(serverFactory) {}

    Dns DnsFactory::fromJson(const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("resolver"));
        assert(jsonValue["resolver"].IsObject());
        assert(jsonValue.HasMember("server"));
        assert(jsonValue["server"].IsObject());

        return Dns{
            resolverFactory.fromJson(jsonValue["resolver"]),
            serverFactory.fromJson(jsonValue["server"])
        };
    }
}
