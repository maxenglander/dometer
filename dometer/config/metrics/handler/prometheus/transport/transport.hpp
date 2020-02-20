#pragma once

#include <string>

#include "dometer/config/metrics/handler/prometheus/transport/exposer.hpp"
#include "std/x/optional.hpp"

namespace dometer::config::metrics::handler::prometheus::transport {
    struct Transport {
        const std::string type;
        const std::x::optional<Exposer> exposer;
    };
}
