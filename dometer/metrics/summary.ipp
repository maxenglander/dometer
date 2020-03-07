#include <string>
#include <memory>
#include <tuple>
#include <utility>
#include <vector>

#include "dometer/metrics/label.hpp"
#include "dometer/metrics/metric.hpp"
#include "dometer/metrics/summary.hpp"
#include "dometer/metrics/type.hpp"
#include "dometer/metrics/unit.hpp"

namespace dometer::metrics {
    template<typename... L>
    summary<L...>::summary(std::string name, std::string description,
                           std::tuple<std::shared_ptr<label<L>>...> labels, std::vector<double> quantiles, unit unit)
            :   metric<double, L...>::metric(name, description, labels, type::summary, unit),
                quantiles(quantiles)
    {}
}
