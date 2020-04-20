#pragma once

#include <map>

namespace dometer::metrics {
    template <typename T>
    struct observation {
       observation(std::map<std::string, std::string>, T);
       const std::map<std::string, std::string> labels;
       const T value;
    };
}

#include "dometer/metrics/observation.ipp"
