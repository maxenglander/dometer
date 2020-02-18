#include <iostream>
#include <memory>
#include <vector>

#include "metrics/handler/handler.hpp"
#include "metrics/handler/handler_factory.hpp"
#include "metrics/observer.hpp"
#include "metrics/observer_factory.hpp"
#include "metrics/options.hpp"

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
