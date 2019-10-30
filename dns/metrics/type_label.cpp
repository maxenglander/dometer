#include "dns/type.hpp"
#include "dns/metrics/type_label.hpp"

namespace Dometer::Dns::Metrics {
    TypeLabel::TypeLabel(std::string name)
            :    Dometer::Metrics::Label<Dometer::Dns::Type>::Label(name, Dometer::Dns::Type::A) {}

    std::string TypeLabel::toString(Dometer::Dns::Type type) const {
        return type;
    }
}
