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
    const lookup_summary lookup_summary::instance = lookup_summary();

    lookup_summary::lookup_summary()
            :   dometer::metrics::summary<
                    /* error  */std::string,
                    /* qclass */dometer::dns::class_,
                    /* qname  */std::string,
                    /* qtype  */dometer::dns::type,
                    /* rcode  */std::string
                >::summary(
                    "dometer_dns_lookup_duration_seconds", "Latency of DNS lookup attempts.",
                    std::make_tuple(
                        dometer::metrics::labels::string("error"),
                        labels::class_("qclass"), 
                        dometer::metrics::labels::string("qname"),
                        labels::type("qtype"),
                        dometer::metrics::labels::string("rcode")
                    ),
                    std::vector<double>{0.5, 0.9, 0.95, 0.99},
                    dometer::metrics::unit::seconds
                )
    {}
}
