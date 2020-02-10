#pragma once

#include <string>

namespace dometer::config::metrics::handler::prometheus::transport {
    struct Transport {
        std::string type;
    };
}
