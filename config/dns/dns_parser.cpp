#include "config/dns/dns.hpp"
#include "config/dns/dns_parser.hpp"
#include "config/dns/resolver/resolver_parser.hpp"
#include "config/dns/server/server_parser.hpp"
#include "rapidjson/document.h"

namespace dometer::config::dns {
    DnsParser::DnsParser()
        : DnsParser::DnsParser(dometer::config::dns::resolver::ResolverParser(),
                                 dometer::config::dns::server::ServerParser()) {}

    DnsParser::DnsParser(dometer::config::dns::resolver::ResolverParser resolverParser,
                           dometer::config::dns::server::ServerParser serverParser)
        : resolverParser(resolverParser), serverParser(serverParser) {}

    Dns DnsParser::fromJson(const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("resolver"));
        assert(jsonValue["resolver"].IsObject());
        assert(jsonValue.HasMember("server"));
        assert(jsonValue["server"].IsObject());

        return Dns{
            resolverParser.fromJson(jsonValue["resolver"]),
            serverParser.fromJson(jsonValue["server"])
        };
    }
}
