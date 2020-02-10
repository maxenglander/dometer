#pragma once

#include <string>

#include "config/metrics/handler/prometheus/prometheus.hpp"
#include "x/optional.hpp"

namespace dometer::config::metrics::handler {
    struct Handler {
        std::string type;
        std::x::optional<dometer::config::metrics::handler::prometheus::Prometheus> prometheus;
    };
}
