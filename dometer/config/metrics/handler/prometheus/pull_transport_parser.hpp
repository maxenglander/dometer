#pragma once

#include "dometer/metrics/handler/prometheus/pull_transport_options.hpp"
#include "json/json.h"

namespace dometer::config::metrics::handler::prometheus {
    class pull_transport_parser {
        public:
            dometer::metrics::handler::prometheus::pull_transport_options from_json(const Json::Value&) const;
    };
}
