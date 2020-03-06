#include <cassert>

#include "dometer/config/dns/server/transport_parser.hpp"
#include "dometer/dns/server/transport_options.hpp"
#include "json/json.h"

namespace dometer::config::dns::server {
    dometer::dns::server::transport_options transport_parser::from_json(const Json::Value& json_value) const {
        assert(json_value.isMember("bindAddress"));
        assert(json_value["bindAddress"].isString());

        return dometer::dns::server::transport_options{
            json_value["bindAddress"].asString()
        };
    }
}
