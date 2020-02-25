#pragma once

#include "dometer/dns/server/options.hpp"
#include "dometer/dns/resolver/options.hpp"

namespace dometer::app::dns {
    struct Options {
        const dometer::dns::resolver::Options resolver;
        const dometer::dns::server::Options server;
    };
}
