#include <string>
#include <vector>

#include "dometer/metrics/label.hpp"
#include "dometer/metrics/metric.hpp"
#include "dometer/metrics/summary.hpp"
#include "dometer/metrics/type.hpp"
#include "dometer/metrics/unit.hpp"

namespace dometer::metrics {
    summary::summary(std::string name,
                     std::string description,
                     std::vector<double> quantiles,
                     dometer::metrics::unit _unit)
        :   metric::metric(name, description, type::summary, _unit),
            quantiles(quantiles)
    {}
}
