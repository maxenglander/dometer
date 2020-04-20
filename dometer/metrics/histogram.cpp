#include <string>
#include <vector>

#include "dometer/metrics/metric.hpp"
#include "dometer/metrics/histogram.hpp"
#include "dometer/metrics/type.hpp"
#include "dometer/metrics/unit.hpp"

namespace dometer::metrics {
    histogram::histogram(std::string name,
                     std::string description,
                     std::vector<double> buckets,
                     dometer::metrics::unit _unit)
        :   metric::metric(name, description, type::histogram, _unit),
            buckets(buckets)
    {}
}
