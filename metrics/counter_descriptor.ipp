#include <string>
#include <memory>
#include <tuple>
#include <utility>

#include "metrics/counter_descriptor.hpp"
#include "metrics/descriptor.hpp"
#include "metrics/label.hpp"
#include "metrics/type.hpp"
#include "metrics/unit.hpp"

namespace Dometer::Metrics {
    template<typename... T>
    CounterDescriptor<T...>::CounterDescriptor(std::string name, std::string description,
                                               std::tuple<std::unique_ptr<Label<T>>...> labels)
            :   Descriptor<T...>::Descriptor(name, description, labels, Type::COUNTER, Unit::NONE)
    {
    }
}
