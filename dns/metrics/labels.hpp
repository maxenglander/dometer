#pragma once

#include <memory>
#include <string>

#include "dns/type.hpp"
#include "metrics/label.hpp"

namespace dometer::dns::metrics {
    class Labels {
        public:
            Labels() = delete;
            static std::shared_ptr<dometer::metrics::Label<dometer::dns::Type>> type(std::string);
    };
}
