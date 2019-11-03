#pragma once

#include <map>
#include <memory>
#include <string>
#include <tuple>

#include "metrics/label.hpp"

namespace dometer::metrics {
    struct LabelHelper {
        LabelHelper() = delete;

        template<typename... T>
        static std::map<std::string, std::string> createLabelMap(std::tuple<std::shared_ptr<Label<T>>...>, std::tuple<T...>);
    };
}

#include "metrics/label_helper.ipp"
