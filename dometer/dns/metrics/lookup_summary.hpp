#pragma once

#include "dometer/dns/type.hpp"
#include "dometer/metrics/summary.hpp"

namespace dometer::dns::metrics {
    struct LookupSummary : dometer::metrics::Summary<std::string, std::string, dometer::dns::Type> {
        static const LookupSummary INSTANCE;

        private:
            LookupSummary();
    };
}
