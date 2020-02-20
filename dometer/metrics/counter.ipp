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
    template<typename... L>
    Counter<L...>::Counter(std::string name, std::string description,
                                               std::tuple<std::shared_ptr<Label<L>>...> labels)
            :   Metric<uint64_t, L...>::Metric(name, description, labels, Type::COUNTER, Unit::NONE)
    {
    }
}
