#pragma once

#include "config/dns/dns.hpp"
#include "metrics/options.hpp"

namespace dometer::config {
    struct Config {
        const dometer::config::dns::Dns dns;
        const dometer::metrics::Options metrics;
    };
}
