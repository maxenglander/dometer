#pragma once

#include <memory>

#include "metrics/observation.hpp"

namespace Dometer::Metrics {
    template<typename Handler>
    class Observer {
        public:
            Observer(std::shared_ptr<Handler>);
            template<typename... L> void observe(Observation<uint64_t, L...>);
            template<typename... L> void observe(Observation<double, L...>);
        private:
            std::shared_ptr<Handler> handler;
    };
}

#include "metrics/observer.ipp"
