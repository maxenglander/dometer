#pragma once

#include "dometer/dns/type.hpp"
#include "dometer/metrics/counter.hpp"

namespace dometer::dns::metrics {
    struct QueryCounter : dometer::metrics::Counter<std::string, std::string, dometer::dns::Type, bool> {
        static const QueryCounter INSTANCE;

        private:
            QueryCounter();
    };
}
