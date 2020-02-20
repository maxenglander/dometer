#include "dometer/config/dns/server/transport.hpp"
#include "dometer/config/dns/server/transport_parser.hpp"
#include "rapidjson/document.h"

namespace dometer::config::dns::server {
    Transport TransportParser::fromJson(const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("bindAddress"));
        assert(jsonValue["bindAddress"].IsString());

        return Transport{
            jsonValue["bindAddress"].GetString()
        };
    }
}
