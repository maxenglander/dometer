#pragma once

#include "config/metrics/handler/prometheus_pull_transport_factory.hpp"
#include "metrics/prometheus_transport_options.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics::handler {
    class PrometheusTransportFactory {
        public:
            PrometheusTransportFactory();
            PrometheusTransportFactory(dometer::config::metrics::handler::PrometheusPullTransportFactory);
            dometer::metrics::PrometheusTransportOptions fromJson(const rapidjson::Value& jsonValue) const;
        private:
            dometer::config::metrics::handler::PrometheusPullTransportFactory pullTransportFactory;
    };
}
