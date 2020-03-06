#pragma once

#include <map>
#include <memory>
#include <string>
#include <tuple>

#include "dometer/metrics/label.hpp"

namespace dometer::metrics {
    struct LabelHelper {
        LabelHelper() = delete;

        template<typename... T>
        static std::map<std::string, std::string> createLabelMap(std::tuple<std::shared_ptr<label<T>>...>, std::tuple<T...>);
    };
}

#include "dometer/metrics/label_helper.ipp"
