#pragma once

#include "metrics/handler.hpp"
#include "metrics/observation.hpp"

namespace Dometer::Metrics {
    class Observer {
        public:
            Observer(Handler&);
            template<typename... T>
            void observe(Observation<T...>);
        private:
            Handler& handler;
            
    };
}

#include "metrics/observer.ipp"
