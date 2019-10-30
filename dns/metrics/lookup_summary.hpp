#pragma once

#include "dns/type.hpp"
#include "metrics/summary.hpp"

namespace Dometer::Dns::Metrics {
    struct LookupSummary : Dometer::Metrics::Summary<std::string, std::string, Dometer::Dns::Type> {
        static const LookupSummary INSTANCE;

        private:
            LookupSummary();
    };
}
