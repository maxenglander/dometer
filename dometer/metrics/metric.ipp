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
    metric<V, L...>::metric(std::string name, std::string description,
                            std::tuple<std::shared_ptr<label<L>>...> labels,
                            dometer::metrics::type type,
                            dometer::metrics::unit unit)
            :   name(name), description(description), labels(labels), type(type), unit(unit)
    {}
}
