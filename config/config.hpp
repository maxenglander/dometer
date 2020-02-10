#pragma once

#include "config/dns/dns.hpp"
#include "config/metrics/metrics.hpp"

namespace dometer::config {
    struct Config {
        const dometer::config::dns::Dns dns;
        const dometer::config::metrics::Metrics metrics;
    };
}
