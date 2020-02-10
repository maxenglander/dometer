#include "config/metrics/handler/handler.hpp"
#include "config/metrics/handler/handler_factory.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics::handler {
    HandlerFactory::HandlerFactory()
        : HandlerFactory::HandlerFactory(dometer::config::metrics::handler::prometheus::PrometheusFactory()) {}

    HandlerFactory::HandlerFactory(dometer::config::metrics::handler::prometheus::PrometheusFactory prometheusFactory)
        : prometheusFactory(prometheusFactory) {}

    Handler HandlerFactory::fromJson(const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("type"));
        assert(jsonValue["type"].IsString());
        std::string type = jsonValue["type"].GetString();
        
        if(type == "prometheus") {
            assert(jsonValue.HasMember("prometheus"));
            assert(jsonValue["prometheus"].IsObject());

            return Handler{
                type,
                prometheusFactory.fromJson(jsonValue["prometheus"])
            };
        } else {
            return Handler{
                type,
                {}
            };
        }
    }
}
