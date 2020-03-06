#include "dometer/dns/type.hpp"
#include "dometer/dns/metrics/type_label.hpp"

namespace dometer::dns::metrics {
    TypeLabel::TypeLabel(std::string name)
            :    dometer::metrics::label<dometer::dns::type>::label(name, dometer::dns::type::A) {}

    std::string TypeLabel::to_string(dometer::dns::type type) const {
        return type;
    }
}
