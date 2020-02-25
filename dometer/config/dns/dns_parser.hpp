#pragma once

#include "dometer/app/dns/options.hpp"
#include "dometer/config/dns/resolver/resolver_parser.hpp"
#include "dometer/config/dns/server/server_parser.hpp"
#include "json/json.h"

namespace app = dometer::app;

namespace dometer::config::dns {
    class DnsParser {
        public:
            DnsParser();
            DnsParser(dometer::config::dns::resolver::ResolverParser,
                    dometer::config::dns::server::ServerParser);
            app::dns::Options fromJson(const Json::Value& jsonValue) const;
        private:
            const dometer::config::dns::resolver::ResolverParser resolverParser;
            const dometer::config::dns::server::ServerParser serverParser;
    };
}
