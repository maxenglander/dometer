#include <string>

#include "dometer/metrics/observation.hpp"
#include "dometer/metrics/observation_builder.hpp"

namespace dometer::metrics {
    template <typename T>
    observation_builder<T>::observation_builder()
        : _labels(),
          _value()
    {}

    template <typename T>
    observation_builder<T>::observation_builder(const observation_builder& src)
        : _labels(src.labels),
          _value(src.value)
    {}

    template <typename T>
    const observation<T> observation_builder<T>::build() const {
        return observation<T>(_labels, _value);
    }

    template <typename T>
    observation_builder<T>& observation_builder<T>::label(std::string key, std::string value) {
        _labels[key] = value;
        return *this;
    }

    template <typename T>
    observation_builder<T>& observation_builder<T>::value(T value) {
        _value = value;
        return *this;
    }
}
