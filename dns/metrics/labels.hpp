#pragma once

#include <memory>
#include <string>

#include "dns/type.hpp"
#include "metrics/label.hpp"

namespace Dometer::Dns::Metrics {
    class Labels {
        public:
            Labels() = delete;
            static std::shared_ptr<Dometer::Metrics::Label<Dometer::Dns::Type>> type(std::string);
    };
}
