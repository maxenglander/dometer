#pragma once

#include "dometer/dns/options.hpp"
#include "dometer/metrics/options.hpp"

namespace dometer::app {
    struct options {
        const dometer::dns::options dns;
        const dometer::metrics::options metrics;
    };
}
