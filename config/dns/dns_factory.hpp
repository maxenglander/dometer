#pragma once

#include "config/dns/dns.hpp"
#include "config/dns/resolver/resolver_factory.hpp"
#include "config/dns/server/server_factory.hpp"
#include "rapidjson/document.h"

namespace dometer::config::dns {
    class DnsFactory {
        public:
            DnsFactory();
            DnsFactory(dometer::config::dns::resolver::ResolverFactory,
                    dometer::config::dns::server::ServerFactory);
            Dns fromJson(const rapidjson::Value& jsonValue) const;
        private:
            const dometer::config::dns::resolver::ResolverFactory resolverFactory;
            const dometer::config::dns::server::ServerFactory serverFactory;
    };
}
