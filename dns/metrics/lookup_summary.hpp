#pragma once

#include "dns/type.hpp"
#include "metrics/summary.hpp"

namespace dometer::dns::metrics {
    struct LookupSummary : dometer::metrics::Summary<std::string, std::string, dometer::dns::Type> {
        static const LookupSummary INSTANCE;

        private:
            LookupSummary();
    };
}
