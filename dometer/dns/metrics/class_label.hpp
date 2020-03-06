#pragma once

#include <string> 
#include "dometer/dns/class.hpp"
#include "dometer/metrics/label.hpp"

namespace dometer::dns::metrics {
    class ClassLabel : public dometer::metrics::Label<dometer::dns::dns_class> {
        public:
            ClassLabel(std::string name);
            std::string toString(dometer::dns::dns_class) const;
    };
}
