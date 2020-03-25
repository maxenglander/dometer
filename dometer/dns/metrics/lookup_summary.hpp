#pragma once

#include "dometer/metrics/summary.hpp"

namespace dometer::dns::metrics {
    struct lookup_summary : dometer::metrics::summary {
        static const lookup_summary instance;

        private:
            lookup_summary();
    };
}
