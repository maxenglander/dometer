#include <string>
#include <memory>
#include <tuple>
#include <utility>

#include "metrics/counter.hpp"
#include "metrics/label.hpp"
#include "metrics/metric.hpp"
#include "metrics/type.hpp"
#include "metrics/unit.hpp"

namespace Dometer::Metrics {
    template<typename... T>
    Counter<T...>::Counter(std::string name, std::string description,
                                               std::tuple<std::shared_ptr<Label<T>>...> labels)
            :   Metric<T...>::Metric(name, description, labels, Type::COUNTER, Unit::NONE)
    {
    }
}
