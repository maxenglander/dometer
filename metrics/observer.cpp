#include <iostream>
#include <vector>

#include "metrics/handler/handler.hpp"
#include "metrics/observer.hpp"

namespace dometer::metrics {
    Observer::Observer(std::vector<dometer::metrics::handler::Handler> handlers)
        : handlers(handlers) {
        std::cout << "initialized handlers, size = " << this->handlers.size() << std::endl;
    }
}
