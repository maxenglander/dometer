#include <cassert>

#include "dometer/dns/server/options.hpp"
#include "dometer/dns/server/transport_options.hpp"
#include "dometer/config/dns/server/server_parser.hpp"
#include "dometer/config/dns/server/transport_parser.hpp"
#include "json/json.h"

namespace dometer::config::dns::server {
    ServerParser::ServerParser() : ServerParser::ServerParser(TransportParser()) {}
    ServerParser::ServerParser(TransportParser transportParser) : transportParser(transportParser) {}

    dometer::dns::server::Options ServerParser::fromJson(const Json::Value& jsonValue) const {
        assert(jsonValue.isMember("transport"));
        assert(jsonValue["transport"].isObject());
        return dometer::dns::server::Options{
            transportParser.fromJson(jsonValue["transport"])
        };
    }
}
