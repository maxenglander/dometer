#pragma once

#include "config/dns/dns.hpp"

namespace dometer::config {
    struct Config {
        const dometer::config::dns::Dns dns;
    };
}
