#include <cassert>

#include "dometer/config/dns/server/transport_parser.hpp"
#include "dometer/dns/server/transport_options.hpp"
#include "json/json.h"

namespace dometer::config::dns::server {
    dometer::dns::server::TransportOptions TransportParser::fromJson(const Json::Value& jsonValue) const {
        assert(jsonValue.isMember("bindAddress"));
        assert(jsonValue["bindAddress"].isString());

        return dometer::dns::server::TransportOptions{
            jsonValue["bindAddress"].asString()
        };
    }
}
