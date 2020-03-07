#pragma once

#include <map>
#include <memory>
#include <string>
#include <tuple>

#include "dometer/metrics/label.hpp"

namespace dometer::metrics {
    struct label_helper {
        label_helper() = delete;

        template<typename... T>
        static std::map<std::string, std::string> create_label_map(std::tuple<std::shared_ptr<label<T>>...>, std::tuple<T...>);
    };
}

#include "dometer/metrics/label_helper.ipp"
