#include <iostream>
#include <vector>

#include "dometer/metrics/handler/handler.hpp"
#include "dometer/metrics/observer.hpp"

namespace dometer::metrics {
    Observer::Observer(std::vector<dometer::metrics::handler::Handler> handlers)
        : handlers(handlers) {
    }
}
