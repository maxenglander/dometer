#pragma once

#include <string>

#include "dns/type.hpp"
#include "metrics/label.hpp"

namespace Dometer::Dns::Metrics {
    class TypeLabel : public Dometer::Metrics::Label<Dometer::Dns::Type> {
        public:
            TypeLabel(std::string name);
            std::string toString(Dometer::Dns::Type) const;
    };
}
