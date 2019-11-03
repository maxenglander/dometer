#pragma once

#include <string> 
#include "dns/type.hpp"
#include "metrics/label.hpp"

namespace dometer::dns::metrics {
    class TypeLabel : public dometer::metrics::Label<dometer::dns::Type> {
        public:
            TypeLabel(std::string name);
            std::string toString(dometer::dns::Type) const;
    };
}
