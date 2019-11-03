#pragma once

#include "dns/type.hpp"
#include "metrics/counter.hpp"

namespace dometer::dns::metrics {
    struct QueryCounter : dometer::metrics::Counter<std::string, std::string, dometer::dns::Type, bool> {
        static const QueryCounter INSTANCE;

        private:
            QueryCounter();
    };
}
