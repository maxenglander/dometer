#pragma once

#include <memory>

#include "metrics/observation.hpp"

namespace Dometer::Metrics {
    template<typename Handler>
    class Observer {
        public:
            Observer(std::shared_ptr<Handler>);
            template<typename... T>
            void observe(Observation<T...>);
        private:
            std::shared_ptr<Handler> handler;
    };
}

#include "metrics/observer.ipp"
