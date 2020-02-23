#pragma once

#include "dometer/metrics/handler/prometheus_pull_transport_options.hpp"
#include "json/json.h"

namespace dometer::config::metrics::handler {
    class PrometheusPullTransportParser {
        public:
            dometer::metrics::handler::PrometheusPullTransportOptions fromJson(const Json::Value& jsonValue) const;
    };
}
