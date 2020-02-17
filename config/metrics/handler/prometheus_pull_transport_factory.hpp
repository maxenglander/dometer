#pragma once

#include "metrics/prometheus_pull_transport_options.hpp"
#include "rapidjson/document.h"

namespace dometer::config::metrics::handler {
    class PrometheusPullTransportFactory {
        public:
            dometer::metrics::PrometheusPullTransportOptions fromJson(const rapidjson::Value& jsonValue) const;
    };
}
