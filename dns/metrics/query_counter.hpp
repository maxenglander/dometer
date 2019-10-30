#pragma once

#include "dns/type.hpp"
#include "metrics/counter.hpp"

namespace Dometer::Dns::Metrics {
    struct QueryCounter : Dometer::Metrics::Counter<std::string, std::string, Dometer::Dns::Type, bool> {
        static const QueryCounter INSTANCE;

        private:
            QueryCounter();
    };
}
