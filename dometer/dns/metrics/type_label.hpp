#pragma once

#include <string> 
#include "dometer/dns/type.hpp"
#include "dometer/metrics/label.hpp"

namespace dometer::dns::metrics {
    class type_label : public dometer::metrics::label<dometer::dns::type> {
        public:
            type_label(std::string name);
            std::string to_string(dometer::dns::type) const;
    };
}
