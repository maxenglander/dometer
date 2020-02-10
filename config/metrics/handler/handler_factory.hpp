#pragma once

#include "config/metrics/handler/handler.hpp"
#include "config/metrics/handler/prometheus/prometheus_factory.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics::handler {
    class HandlerFactory {
        public:
            HandlerFactory();
            HandlerFactory(dometer::config::metrics::handler::prometheus::PrometheusFactory);
            Handler fromJson(const rapidjson::Value& jsonValue) const;
        private:
            dometer::config::metrics::handler::prometheus::PrometheusFactory prometheusFactory;
    };
}
