#include <string>
#include <tuple>
#include <vector>

#include "dns/type.hpp"
#include "dns/metrics/labels.hpp"
#include "dns/metrics/lookup_summary.hpp"
#include "dns/metrics/type_label.hpp"
#include "metrics/labels.hpp"
#include "metrics/summary.hpp"
#include "metrics/unit.hpp"

namespace Dometer::Dns::Metrics {
    const LookupSummary LookupSummary::INSTANCE = LookupSummary();

    LookupSummary::LookupSummary()
            :   Dometer::Metrics::Summary<std::string, std::string, Dometer::Dns::Type>::Summary(
                    "dns_upstream_resolution_seconds", "Summary duration of DNS upstream resolutions",
                    std::make_tuple(
                        Dometer::Metrics::Labels::string("qclass"), 
                        Dometer::Metrics::Labels::string("qname"),
                        Labels::type("qtype")
                    ),
                    std::vector<double>{0.5, 0.9, 0.95, 0.99},
                    Dometer::Metrics::Unit::SECONDS
                )
    {}
}
