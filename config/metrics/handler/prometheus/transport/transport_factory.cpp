#include "config/metrics/handler/prometheus/transport/transport.hpp"
#include "config/metrics/handler/prometheus/transport/transport_factory.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics::handler::prometheus::transport {
    Transport TransportFactory::fromJson(const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("type"));
        assert(jsonValue["type"].IsString());

        return Transport{
            jsonValue["type"].GetString()
        };
    }
}
