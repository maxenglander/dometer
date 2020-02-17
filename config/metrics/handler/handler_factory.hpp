#pragma once

#include "config/metrics/handler/prometheus_handler_factory.hpp"
#include "metrics/options.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics::handler {
    class HandlerFactory {
        public:
            HandlerFactory();
            HandlerFactory(dometer::config::metrics::handler::PrometheusHandlerFactory);
            dometer::metrics::Options fromJson(const rapidjson::Value& jsonValue) const;
        private:
            dometer::config::metrics::handler::PrometheusHandlerFactory prometheusFactory;
    };
}
