#pragma once

#include "dometer/app/dns/options.hpp"
#include "dometer/app/metrics/options.hpp"

namespace dometer::app {
    struct options {
        const dometer::app::dns::options dns;
        const dometer::app::metrics::options metrics;
    };
}
