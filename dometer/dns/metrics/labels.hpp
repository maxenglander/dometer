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
            static std::shared_ptr<dometer::metrics::Label<dometer::dns::class_>> class_(std::string);
            static std::shared_ptr<dometer::metrics::Label<dometer::dns::type>> type(std::string);
    };
}
