#include <string>
#include <tuple>
#include <vector>

#include "dometer/dns/type.hpp"
#include "dometer/dns/metrics/labels.hpp"
#include "dometer/dns/metrics/lookup_summary.hpp"
#include "dometer/dns/metrics/type_label.hpp"
#include "dometer/metrics/labels.hpp"
#include "dometer/metrics/summary.hpp"
#include "dometer/metrics/unit.hpp"

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
