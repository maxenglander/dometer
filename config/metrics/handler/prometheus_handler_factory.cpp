#include "config/metrics/handler/prometheus_handler_factory.hpp"
#include "config/metrics/handler/prometheus_transport_factory.hpp"
#include "metrics/handler/prometheus_options.hpp"
#include "metrics/handler/prometheus_transport_options.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics::handler {
    PrometheusHandlerFactory::PrometheusHandlerFactory()
        : PrometheusHandlerFactory::PrometheusHandlerFactory(
                dometer::config::metrics::handler::PrometheusTransportFactory()) {}

    PrometheusHandlerFactory::PrometheusHandlerFactory(
            dometer::config::metrics::handler::PrometheusTransportFactory transportFactory)
        : transportFactory(transportFactory) {}

    dometer::metrics::handler::PrometheusOptions PrometheusHandlerFactory::fromJson(
            const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("maxTimeSeries"));
        assert(jsonValue["maxTimeSeries"].IsUint());
        assert(jsonValue.HasMember("transports"));
        assert(jsonValue["transports"].IsArray());

        std::vector<dometer::metrics::handler::PrometheusTransportOptions> transports;
        for(rapidjson::SizeType i = 0; i < jsonValue["transports"].Size(); i++) {
            transports.push_back(transportFactory.fromJson(jsonValue["transports"][i]));
        }

        return dometer::metrics::handler::PrometheusOptions{
            jsonValue["maxTimeSeries"].GetUint(),
            transports
        };
    }
}
