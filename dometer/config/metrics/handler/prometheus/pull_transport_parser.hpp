#pragma once

#include "dometer/metrics/handler/prometheus/pull_transport_options.hpp"
#include "json/json.h"

namespace dometer::config::metrics::handler::prometheus {
    class PullTransportParser {
        public:
            dometer::metrics::handler::prometheus::PullTransportOptions fromJson(const Json::Value& jsonValue) const;
    };
}
