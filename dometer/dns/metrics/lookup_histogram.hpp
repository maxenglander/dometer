#pragma once

#include "dometer/metrics/histogram.hpp"

namespace dometer::dns::metrics {
    struct lookup_histogram : dometer::metrics::histogram {
        static const lookup_histogram instance;

        private:
            lookup_histogram();
    };
}
