#include <string>
#include <vector>

#include "dometer/dns/metrics/lookup_summary.hpp"
#include "dometer/metrics/summary.hpp"
#include "dometer/metrics/unit.hpp"

namespace dometer::dns::metrics {
    const lookup_summary lookup_summary::instance = lookup_summary();

    lookup_summary::lookup_summary() : dometer::metrics::summary::summary(
            "dometer_dns_lookup_duration_seconds",
            "Latency of DNS lookup attempts.",
            std::vector<double>{0.5, 0.9, 0.95, 0.99},
            dometer::metrics::unit::seconds
        )
    {}
}
