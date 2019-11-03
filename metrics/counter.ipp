#include <string>
#include <memory>
#include <tuple>
#include <utility>

#include "metrics/counter.hpp"
#include "metrics/label.hpp"
#include "metrics/metric.hpp"
#include "metrics/type.hpp"
#include "metrics/unit.hpp"

namespace dometer::metrics {
    template<typename... L>
    Counter<L...>::Counter(std::string name, std::string description,
                                               std::tuple<std::shared_ptr<Label<L>>...> labels)
            :   Metric<uint64_t, L...>::Metric(name, description, labels, Type::COUNTER, Unit::NONE)
    {
    }
}
