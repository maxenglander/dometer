#include <iostream>
#include <vector>

#include "dometer/metrics/handler/handler.hpp"
#include "dometer/metrics/observer.hpp"

namespace dometer::metrics {
    observer::observer(std::vector<dometer::metrics::handler::handler> handlers)
        : handlers(handlers) {
    }
}
