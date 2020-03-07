#pragma once

#include <string> 
#include "dometer/dns/class.hpp"
#include "dometer/metrics/label.hpp"

namespace dometer::dns::metrics {
    class class_label : public dometer::metrics::label<dometer::dns::class_> {
        public:
            class_label(std::string name);
            std::string to_string(dometer::dns::class_) const;
    };
}
