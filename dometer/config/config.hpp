#pragma once

#include "dometer/config/dns/dns.hpp"
#include "dometer/metrics/options.hpp"

namespace dometer::config {
    struct Config {
        const dometer::config::dns::Dns dns;
        const dometer::metrics::Options metrics;
    };
}
