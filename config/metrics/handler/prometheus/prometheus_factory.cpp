#include "config/metrics/handler/prometheus/prometheus.hpp"
#include "config/metrics/handler/prometheus/prometheus_factory.hpp"
#include "config/metrics/handler/prometheus/transport/transport.hpp"
#include "config/metrics/handler/prometheus/transport/transport_factory.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics::handler::prometheus {
    PrometheusFactory::PrometheusFactory()
        : PrometheusFactory::PrometheusFactory(dometer::config::metrics::handler::prometheus::transport::TransportFactory() ) {}

    PrometheusFactory::PrometheusFactory(dometer::config::metrics::handler::prometheus::transport::TransportFactory transportFactory)
        : transportFactory(transportFactory) {}

    Prometheus PrometheusFactory::fromJson(const rapidjson::Value& jsonValue) const {
        assert(jsonValue.HasMember("maxTimeSeries"));
        assert(jsonValue["maxTimeSeries"].IsUint());
        assert(jsonValue.HasMember("transports"));
        assert(jsonValue["transports"].IsArray());

        std::vector<dometer::config::metrics::handler::prometheus::transport::Transport> transports;
        for(rapidjson::SizeType i = 0; i < jsonValue["transports"].Size(); i++) {
            transports.push_back(transportFactory.fromJson(jsonValue["transports"][i]));
        }

        return Prometheus{
            jsonValue["maxTimeSeries"].GetUint(),
            transports
        };
    }
}
