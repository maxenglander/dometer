#pragma once

#include "config/metrics/handler/prometheus/transport/exposer.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics::handler::prometheus::transport {
    class ExposerFactory {
        public:
            Exposer fromJson(const rapidjson::Value& jsonValue) const;
    };
}
