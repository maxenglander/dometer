#include "config/metrics/handler/handler_factory.hpp"
#include "metrics/handler/options.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics::handler {
    HandlerFactory::HandlerFactory()
        : HandlerFactory::HandlerFactory(dometer::config::metrics::handler::PrometheusHandlerFactory()) {}

    HandlerFactory::HandlerFactory(dometer::config::metrics::handler::PrometheusHandlerFactory prometheusFactory)
        : prometheusFactory(prometheusFactory) {}

    dometer::metrics::handler::Options HandlerFactory::fromJson(const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("type"));
        assert(jsonValue["type"].IsString());
        std::string type = jsonValue["type"].GetString();
        
        if(type == "prometheus") {
            assert(jsonValue.HasMember("prometheus"));
            assert(jsonValue["prometheus"].IsObject());

            return prometheusFactory.fromJson(jsonValue["prometheus"]);
        } else {
            assert(false);
        }
    }
}
