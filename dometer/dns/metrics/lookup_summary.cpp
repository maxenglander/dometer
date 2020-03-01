#include <string>
#include <tuple>
#include <vector>

#include "dometer/dns/class.hpp"
#include "dometer/dns/type.hpp"
#include "dometer/dns/metrics/class_label.hpp"
#include "dometer/dns/metrics/labels.hpp"
#include "dometer/dns/metrics/lookup_summary.hpp"
#include "dometer/dns/metrics/type_label.hpp"
#include "dometer/metrics/labels.hpp"
#include "dometer/metrics/summary.hpp"
#include "dometer/metrics/unit.hpp"

namespace dometer::dns::metrics {
    const LookupSummary LookupSummary::INSTANCE = LookupSummary();

    LookupSummary::LookupSummary()
            :   dometer::metrics::Summary<
                    /* error  */std::string,
                    /* qclass */dometer::dns::Class,
                    /* qname  */std::string,
                    /* qtype  */dometer::dns::Type,
                    /* rcode  */std::string
                >::Summary(
                    "dometer_dns_lookup_duration_seconds", "Latency of DNS lookup attempts.",
                    std::make_tuple(
                        dometer::metrics::Labels::string("error"),
                        Labels::class_("qclass"), 
                        dometer::metrics::Labels::string("qname"),
                        Labels::type("qtype"),
                        dometer::metrics::Labels::string("rcode")
                    ),
                    std::vector<double>{0.5, 0.9, 0.95, 0.99},
                    dometer::metrics::Unit::SECONDS
                )
    {}
}
