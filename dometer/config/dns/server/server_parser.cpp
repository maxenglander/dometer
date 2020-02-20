#include "dometer/config/dns/server/server.hpp"
#include "dometer/config/dns/server/server_parser.hpp"
#include "dometer/config/dns/server/transport.hpp"
#include "dometer/config/dns/server/transport_parser.hpp"
#include "rapidjson/document.h"

namespace dometer::config::dns::server {
    ServerParser::ServerParser() : ServerParser::ServerParser(TransportParser()) {}
    ServerParser::ServerParser(TransportParser transportParser) : transportParser(transportParser) {}

    Server ServerParser::fromJson(const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("transport"));
        assert(jsonValue["transport"].IsObject());
        return Server{
            transportParser.fromJson(jsonValue["transport"])
        };
    }
}
