#include <cassert>

#include "dometer/config/dns/server/server.hpp"
#include "dometer/config/dns/server/server_parser.hpp"
#include "dometer/config/dns/server/transport.hpp"
#include "dometer/config/dns/server/transport_parser.hpp"
#include "json/json.h"

namespace dometer::config::dns::server {
    ServerParser::ServerParser() : ServerParser::ServerParser(TransportParser()) {}
    ServerParser::ServerParser(TransportParser transportParser) : transportParser(transportParser) {}

    Server ServerParser::fromJson(const Json::Value& jsonValue) const {
        assert(jsonValue.isMember("transport"));
        assert(jsonValue["transport"].isObject());
        return Server{
            transportParser.fromJson(jsonValue["transport"])
        };
    }
}
