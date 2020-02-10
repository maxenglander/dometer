#pragma once

#include <string>

#include "config/metrics/handler/prometheus/transport/exposer.hpp"
#include "x/optional.hpp"

namespace dometer::config::metrics::handler::prometheus::transport {
    struct Transport {
        const std::string type;
        const std::x::optional<Exposer> exposer;
    };
}
