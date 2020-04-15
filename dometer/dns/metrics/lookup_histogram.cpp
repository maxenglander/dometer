#include <string>
#include <vector>

#include "dometer/dns/metrics/lookup_histogram.hpp"
#include "dometer/metrics/histogram.hpp"
#include "dometer/metrics/unit.hpp"

namespace dometer::dns::metrics {
    const lookup_histogram lookup_histogram::instance = lookup_histogram();

    lookup_histogram::lookup_histogram() : dometer::metrics::histogram::histogram(
            "dometer_dns_lookup_duration_seconds",
            "Latency of DNS lookup attempts.",
            std::vector<double>{
                0.00001,
                0.000025,
                0.00005,
                0.000075,
                0.0001,
                0.00025,
                0.0005,
                0.00075,
                0.001,
                0.0025,
                0.005,
                0.0075,
                0.01,
                0.025,
                0.05,
                0.075,
                0.1,
                0.25,
                0.5,
                0.75,
                1,
                2.5,
                5,
                7.5,
                10,
                25,
                75,
                100,
            },
            dometer::metrics::unit::seconds
        )
    {}
}
