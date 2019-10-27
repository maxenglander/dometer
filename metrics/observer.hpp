#pragma once

#include "metrics/observation.hpp"

namespace Dometer::Metrics {
    class Observer {
        public:
            template<typename T...>
            void observe(Observation<T...>);
    };
}
