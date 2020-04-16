#pragma once

#include "dometer/metrics/histogram.hpp"

namespace dometer::metrics {
    struct example_histogram : dometer::metrics::histogram {
        static const example_histogram instance;

        private:
            example_histogram();
    };
}
