#pragma once

#include <memory>
#include <string>

#include "dometer/metrics/label.hpp"

namespace dometer::metrics {
    class Labels {
        public:
            Labels() = delete;
            static std::shared_ptr<label<bool>> boolean(std::string);
            static std::shared_ptr<label<std::string>> string(std::string);
    };
}
