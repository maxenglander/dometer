#include <string>
#include <memory>
#include <tuple>
#include <utility>

#include "dometer/metrics/counter.hpp"
#include "dometer/metrics/label.hpp"
#include "dometer/metrics/metric.hpp"
#include "dometer/metrics/type.hpp"
#include "dometer/metrics/unit.hpp"

namespace dometer::metrics {
    counter::counter(std::string name, std::string description,
                     std::tuple<std::shared_ptr<label<L>>...> labels)
        :   metric::metric(name, description, labels, type::counter, unit::none)
    {
    }
}
