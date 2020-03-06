#include "dometer/dns/type.hpp"
#include "dometer/dns/metrics/type_label.hpp"

namespace dometer::dns::metrics {
    TypeLabel::TypeLabel(std::string name)
            :    dometer::metrics::Label<dometer::dns::type>::Label(name, dometer::dns::type::A) {}

    std::string TypeLabel::toString(dometer::dns::type type) const {
        return type;
    }
}
