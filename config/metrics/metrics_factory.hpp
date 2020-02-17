#pragma once

#include "config/metrics/handler/handler_factory.hpp"
#include "metrics/options.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics {
    class MetricsFactory {
        public:
            MetricsFactory();
            MetricsFactory(dometer::config::metrics::handler::HandlerFactory);
            dometer::metrics::Options fromJson(const rapidjson::Value& jsonValue) const;
        private:
            const dometer::config::metrics::handler::HandlerFactory handlerFactory;
    };
}
