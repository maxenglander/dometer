#include <string>
#include <memory>
#include <tuple>
#include <utility>

#include "metrics/label.hpp"
#include "metrics/metric.hpp"
#include "metrics/type.hpp"
#include "metrics/unit.hpp"

namespace dometer::metrics {
    template<typename V, typename... L>
    Metric<V, L...>::Metric(std::string name, std::string description,
                                 std::tuple<std::shared_ptr<Label<L>>...> labels, Type type, Unit unit)
            :   name(name), description(description), labels(labels), type(type), unit(unit)
    {}
}
