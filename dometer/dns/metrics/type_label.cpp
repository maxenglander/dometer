#include "dometer/dns/type.hpp"
#include "dometer/dns/metrics/type_label.hpp"

namespace dometer::dns::metrics {
    type_label::type_label(std::string name)
            :    dometer::metrics::label<dometer::dns::type>::label(name, dometer::dns::type::a) {}

    std::string type_label::to_string(dometer::dns::type type) const {
        return type;
    }
}
