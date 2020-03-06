#include "dometer/dns/class.hpp"
#include "dometer/dns/metrics/class_label.hpp"

namespace dometer::dns::metrics {
    ClassLabel::ClassLabel(std::string name)
            :    dometer::metrics::label<dometer::dns::class_>::label(name, dometer::dns::class_::IN) {}

    std::string ClassLabel::to_string(dometer::dns::class_ class_) const {
        return class_;
    }
}
