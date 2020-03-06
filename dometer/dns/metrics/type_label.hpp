#pragma once

#include <string> 
#include "dometer/dns/type.hpp"
#include "dometer/metrics/label.hpp"

namespace dometer::dns::metrics {
    class TypeLabel : public dometer::metrics::Label<dometer::dns::type> {
        public:
            TypeLabel(std::string name);
            std::string toString(dometer::dns::type) const;
    };
}
