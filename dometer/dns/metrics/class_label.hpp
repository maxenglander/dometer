#pragma once

#include <string> 
#include "dometer/dns/class.hpp"
#include "dometer/metrics/label.hpp"

namespace dometer::dns::metrics {
    class ClassLabel : public dometer::metrics::Label<dometer::dns::class_> {
        public:
            ClassLabel(std::string name);
            std::string toString(dometer::dns::class_) const;
    };
}
