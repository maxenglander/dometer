#pragma once

#include "config/metrics/handler/prometheus_transport_factory.hpp"
#include "metrics/handler/prometheus_options.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics::handler {
    class PrometheusHandlerFactory {
        public:
            PrometheusHandlerFactory();
            PrometheusHandlerFactory(PrometheusTransportFactory);
            dometer::metrics::handler::PrometheusOptions fromJson(const rapidjson::Value& jsonValue) const;
        private:
            dometer::config::metrics::handler::PrometheusTransportFactory transportFactory;
    };
}
