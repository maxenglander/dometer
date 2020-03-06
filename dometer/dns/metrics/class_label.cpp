#include "dometer/dns/class.hpp"
#include "dometer/dns/metrics/class_label.hpp"

namespace dometer::dns::metrics {
    ClassLabel::ClassLabel(std::string name)
            :    dometer::metrics::Label<dometer::dns::class_>::Label(name, dometer::dns::class_::IN) {}

    std::string ClassLabel::toString(dometer::dns::class_ class_) const {
        return class_;
    }
}
