#include <cassert>

#include "dometer/config/dns/server/transport.hpp"
#include "dometer/config/dns/server/transport_parser.hpp"
#include "json/json.h"

namespace dometer::config::dns::server {
    Transport TransportParser::fromJson(const Json::Value& jsonValue) const {
        assert(jsonValue.isMember("bindAddress"));
        assert(jsonValue["bindAddress"].isString());

        return Transport{
            jsonValue["bindAddress"].asString()
        };
    }
}
