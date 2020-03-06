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
    Summary<L...>::Summary(std::string name, std::string description,
                           std::tuple<std::shared_ptr<Label<L>>...> labels, std::vector<double> quantiles, Unit unit)
            :   Metric<double, L...>::Metric(name, description, labels, type::SUMMARY, unit),
                quantiles(quantiles)
    {}
}
