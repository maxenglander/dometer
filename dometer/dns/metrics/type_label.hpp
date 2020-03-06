#pragma once

#include <string> 
#include "dometer/dns/type.hpp"
#include "dometer/metrics/label.hpp"

namespace dometer::dns::metrics {
    class TypeLabel : public dometer::metrics::label<dometer::dns::type> {
        public:
            TypeLabel(std::string name);
            std::string to_string(dometer::dns::type) const;
    };
}
