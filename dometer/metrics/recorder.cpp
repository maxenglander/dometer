#include <iostream>
#include <vector>

#include "dometer/metrics/handler/handler.hpp"
#include "dometer/metrics/recorder.hpp"

namespace dometer::metrics {
    recorder::recorder(std::vector<dometer::metrics::handler::handler> handlers)
        : handlers(handlers) {
    }
}
