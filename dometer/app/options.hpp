#pragma once

#include "dometer/app/dns/options.hpp"
#include "dometer/app/metrics/options.hpp"

namespace dometer::app {
    struct Options {
        const dometer::app::dns::Options dns;
        const dometer::app::metrics::Options metrics;
    };
}
