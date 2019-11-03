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

namespace dometer::dns::metrics {
    const LookupSummary LookupSummary::INSTANCE = LookupSummary();

    LookupSummary::LookupSummary()
            :   dometer::metrics::Summary<std::string, std::string, dometer::dns::Type>::Summary(
                    "dns_upstream_resolution_seconds", "Summary duration of DNS upstream resolutions",
                    std::make_tuple(
                        dometer::metrics::Labels::string("qclass"), 
                        dometer::metrics::Labels::string("qname"),
                        Labels::type("qtype")
                    ),
                    std::vector<double>{0.5, 0.9, 0.95, 0.99},
                    dometer::metrics::Unit::SECONDS
                )
    {}
}
