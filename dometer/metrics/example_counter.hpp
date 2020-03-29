#pragma once

#include "dometer/metrics/counter.hpp"

namespace dometer::metrics {
    struct example_counter : dometer::metrics::counter {
        static const example_counter instance;

        private:
            example_counter();
    };
}
