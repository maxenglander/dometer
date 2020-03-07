#pragma once

#include <memory>
#include <string>

#include "dometer/dns/class.hpp"
#include "dometer/dns/type.hpp"
#include "dometer/metrics/label.hpp"

namespace dometer::dns::metrics {
    class labels {
        public:
            labels() = delete;
            static std::shared_ptr<dometer::metrics::label<dometer::dns::class_>> class_(std::string);
            static std::shared_ptr<dometer::metrics::label<dometer::dns::type>> type(std::string);
    };
}
