#include "dometer/dns/type.hpp"
#include "dometer/dns/metrics/type_label.hpp"

namespace dometer::dns::metrics {
    TypeLabel::TypeLabel(std::string name)
            :    dometer::metrics::Label<dometer::dns::Type>::Label(name, dometer::dns::Type::A) {}

    std::string TypeLabel::toString(dometer::dns::Type type) const {
        return type;
    }
}
