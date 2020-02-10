#include "config/metrics/handler/prometheus/prometheus.hpp"
#include "config/metrics/handler/prometheus/prometheus_factory.hpp"
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

        return Prometheus{
            jsonValue["maxTimeSeries"].GetUint()
        };
    }
}
