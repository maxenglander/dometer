#include <iostream>
#include <memory>
#include <vector>

#include "dometer/metrics/handler/handler.hpp"
#include "dometer/metrics/handler/handler_factory.hpp"
#include "dometer/metrics/observer.hpp"
#include "dometer/metrics/observer_factory.hpp"
#include "dometer/metrics/options.hpp"

namespace dometer::metrics {
    std::shared_ptr<Observer> ObserverFactory::makeObserver(Options options) {
        std::vector<dometer::metrics::handler::Handler> handlers;

        for(auto it = options.handlers.begin(); it < options.handlers.end(); it++) {
            std::cout << "pushing handler" << std::endl;
            handlers.push_back(dometer::metrics::handler::HandlerFactory::makeHandler(*it));
        }

        return std::make_shared<Observer>(handlers);
    }
}
