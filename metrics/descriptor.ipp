#include <string>
#include <memory>
#include <tuple>
#include <utility>

#include "metrics/descriptor.hpp"
#include "metrics/label.hpp"
#include "metrics/type.hpp"
#include "metrics/unit.hpp"

namespace Dometer::Metrics {
    template<typename... T>
    Descriptor<T...>::Descriptor(std::string name, std::string description,
                                 std::tuple<std::unique_ptr<Label<T>>...> labels, Type type, Unit unit)
            :   name(name), description(description), labels(std::move(labels)), type(type), unit(unit)
    {
    }
}
