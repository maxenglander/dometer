#pragma once

#include "dometer/config/dns/dns.hpp"
#include "dometer/config/dns/resolver/resolver_parser.hpp"
#include "dometer/config/dns/server/server_parser.hpp"
#include "json/json.h"

namespace dometer::config::dns {
    class DnsParser {
        public:
            DnsParser();
            DnsParser(dometer::config::dns::resolver::ResolverParser,
                    dometer::config::dns::server::ServerParser);
            Dns fromJson(const Json::Value& jsonValue) const;
        private:
            const dometer::config::dns::resolver::ResolverParser resolverParser;
            const dometer::config::dns::server::ServerParser serverParser;
    };
}
