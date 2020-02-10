#include <string>

#include "config/metrics/handler/prometheus/transport/exposer_factory.hpp"
#include "config/metrics/handler/prometheus/transport/transport.hpp"
#include "config/metrics/handler/prometheus/transport/transport_factory.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics::handler::prometheus::transport {
    TransportFactory::TransportFactory()
        : TransportFactory::TransportFactory(dometer::config::metrics::handler::prometheus::transport::ExposerFactory()) {}

    TransportFactory::TransportFactory(dometer::config::metrics::handler::prometheus::transport::ExposerFactory exposerFactory)
        : exposerFactory(exposerFactory) {}

    Transport TransportFactory::fromJson(const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("type"));
        assert(jsonValue["type"].IsString());

        std::string type = jsonValue["type"].GetString();
        if(type == "pull") {
            assert(jsonValue.HasMember("exposer"));
            assert(jsonValue["exposer"].IsObject());

            return Transport{
                type,
                exposerFactory.fromJson(jsonValue["exposer"])
            };
        } else {
            return Transport{
                type,
                {}
            };
        }
    }
}
