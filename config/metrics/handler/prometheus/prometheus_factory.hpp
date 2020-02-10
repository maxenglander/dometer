#pragma once

#include "config/metrics/handler/prometheus/prometheus.hpp"
#include "config/metrics/handler/prometheus/transport/transport_factory.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics::handler::prometheus {
    class PrometheusFactory {
        public:
            PrometheusFactory();
            PrometheusFactory(dometer::config::metrics::handler::prometheus::transport::TransportFactory);
            Prometheus fromJson(const rapidjson::Value& jsonValue) const;
        private:
            dometer::config::metrics::handler::prometheus::transport::TransportFactory transportFactory;
    };
}
