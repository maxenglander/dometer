#pragma once

#include "config/metrics/handler/prometheus/transport/transport.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics::handler::prometheus::transport {
    class TransportFactory {
        public:
            Transport fromJson(const rapidjson::Value& jsonValue) const;
    };
}
