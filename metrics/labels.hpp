#pragma once

#include <memory>
#include <string>

#include "metrics/label.hpp"

namespace Dometer::Metrics {
    class Labels {
        public:
            Labels() = delete;
            static std::unique_ptr<Label<bool>> boolean(std::string);
            static std::unique_ptr<Label<std::string>> string(std::string);
    };
}
