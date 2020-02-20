#pragma once

#include "metrics/handler/prometheus_pull_transport_options.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics::handler {
    class PrometheusPullTransportParser {
        public:
            dometer::metrics::handler::PrometheusPullTransportOptions fromJson(const rapidjson::Value& jsonValue) const;
    };
}
