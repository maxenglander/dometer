#include "config/dns/server/transport.hpp"
#include "config/dns/server/transport_factory.hpp"
#include "rapidjson/document.h"

namespace dometer::config::dns::server {
    Transport TransportFactory::fromJson(const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("bindAddress"));
        assert(jsonValue["bindAddress"].IsString());
        assert(jsonValue.HasMember("maxConnections"));
        assert(jsonValue["maxConnections"].IsUint());

        return Transport{
            jsonValue["bindAddress"].GetString(),
            jsonValue["maxConnections"].GetUint()
        };
    }
}
