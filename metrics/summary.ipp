#include <string>
#include <memory>
#include <tuple>
#include <utility>
#include <vector>

#include "metrics/label.hpp"
#include "metrics/metric.hpp"
#include "metrics/summary.hpp"
#include "metrics/type.hpp"
#include "metrics/unit.hpp"

namespace dometer::metrics {
    template<typename... L>
    Summary<L...>::Summary(std::string name, std::string description,
                           std::tuple<std::shared_ptr<Label<L>>...> labels, std::vector<double> quantiles, Unit unit)
            :   Metric<double, L...>::Metric(name, description, labels, Type::SUMMARY, unit),
                quantiles(quantiles)
    {}
}
