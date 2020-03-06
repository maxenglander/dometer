#pragma once

#include <string> 
#include "dometer/dns/class.hpp"
#include "dometer/metrics/label.hpp"

namespace dometer::dns::metrics {
    class ClassLabel : public dometer::metrics::label<dometer::dns::class_> {
        public:
            ClassLabel(std::string name);
            std::string to_string(dometer::dns::class_) const;
    };
}
