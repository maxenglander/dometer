#include <string>
#include <memory>
#include <tuple>
#include <utility>

#include "dometer/metrics/label.hpp"
#include "dometer/metrics/metric.hpp"
#include "dometer/metrics/type.hpp"
#include "dometer/metrics/unit.hpp"

namespace dometer::metrics {
    template<typename V, typename... L>
    Metric<V, L...>::Metric(std::string name, std::string description,
                                 std::tuple<std::shared_ptr<Label<L>>...> labels, dometer::metrics::type type, Unit unit)
            :   name(name), description(description), labels(labels), type(type), unit(unit)
    {}
}
