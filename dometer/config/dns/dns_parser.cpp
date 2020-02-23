#include <cassert>

#include "dometer/config/dns/dns.hpp"
#include "dometer/config/dns/dns_parser.hpp"
#include "dometer/config/dns/resolver/resolver_parser.hpp"
#include "dometer/config/dns/server/server_parser.hpp"
#include "json/json.h"

namespace dometer::config::dns {
    DnsParser::DnsParser()
        : DnsParser::DnsParser(dometer::config::dns::resolver::ResolverParser(),
                                 dometer::config::dns::server::ServerParser()) {}

    DnsParser::DnsParser(dometer::config::dns::resolver::ResolverParser resolverParser,
                           dometer::config::dns::server::ServerParser serverParser)
        : resolverParser(resolverParser), serverParser(serverParser) {}

    Dns DnsParser::fromJson(const Json::Value& jsonValue) const {
        assert(jsonValue.isMember("resolver"));
        assert(jsonValue["resolver"].isObject());
        assert(jsonValue.isMember("server"));
        assert(jsonValue["server"].isObject());

        return Dns{
            resolverParser.fromJson(jsonValue["resolver"]),
            serverParser.fromJson(jsonValue["server"])
        };
    }
}
