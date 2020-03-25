#include <string>

#include "dometer/metrics/label.hpp"
#include "dometer/metrics/metric.hpp"
#include "dometer/metrics/type.hpp"
#include "dometer/metrics/unit.hpp"

namespace dometer::metrics {
    metric::metric(std::string name, std::string description,
                   dometer::metrics::type type, dometer::metrics::unit unit)
        :   name(name), description(description), type(type), unit(unit)
    {}
}
