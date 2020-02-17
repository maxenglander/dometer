#include <vector>

#include "config/metrics/handler/handler_factory.hpp"
#include "config/metrics/metrics.hpp"
#include "config/metrics/metrics_factory.hpp"
#include "metrics/handler/options.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics {
    MetricsFactory::MetricsFactory()
        : MetricsFactory::MetricsFactory(dometer::config::metrics::handler::HandlerFactory()) {}

    MetricsFactory::MetricsFactory(dometer::config::metrics::handler::HandlerFactory handlerFactory)
        : handlerFactory(handlerFactory) {}

    Metrics MetricsFactory::fromJson(const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("handlers"));
        assert(jsonValue["handlers"].IsArray());

        std::vector<dometer::metrics::handler::Options> handlers;
        for(rapidjson::SizeType i = 0; i < jsonValue["handlers"].Size(); i++) {
            handlers.push_back(handlerFactory.fromJson(jsonValue["handlers"][i]));
        }

        return Metrics{
            handlers
        };
    }
}
