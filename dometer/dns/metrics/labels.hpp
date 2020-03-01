#pragma once

#include <memory>
#include <string>

#include "dometer/dns/class.hpp"
#include "dometer/dns/type.hpp"
#include "dometer/metrics/label.hpp"

namespace dometer::dns::metrics {
    class Labels {
        public:
            Labels() = delete;
            static std::shared_ptr<dometer::metrics::Label<dometer::dns::Class>> class_(std::string);
            static std::shared_ptr<dometer::metrics::Label<dometer::dns::Type>> type(std::string);
    };
}