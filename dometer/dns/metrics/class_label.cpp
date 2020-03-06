#include "dometer/dns/class.hpp"
#include "dometer/dns/metrics/class_label.hpp"

namespace dometer::dns::metrics {
    ClassLabel::ClassLabel(std::string name)
            :    dometer::metrics::Label<dometer::dns::dns_class>::Label(name, dometer::dns::dns_class::IN) {}

    std::string ClassLabel::toString(dometer::dns::dns_class class_) const {
        return class_;
    }
}
