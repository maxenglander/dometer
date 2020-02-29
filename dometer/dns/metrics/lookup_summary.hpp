#pragma once

#include <string>

#include "dometer/dns/class.hpp"
#include "dometer/dns/type.hpp"
#include "dometer/metrics/summary.hpp"

namespace dometer::dns::metrics {
    struct LookupSummary : dometer::metrics::Summary<dometer::dns::Class, std::string, dometer::dns::Type, std::string> {
        static const LookupSummary INSTANCE;

        private:
            LookupSummary();
    };
}
