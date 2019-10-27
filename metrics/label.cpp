#include <string>

#include "metrics/label.hpp"

namespace Dometer::Metrics {
    template<typename T>
    Label<T>::Label(std::string name) : name(name) {}
}
