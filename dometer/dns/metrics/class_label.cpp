#include "dometer/dns/class.hpp"
#include "dometer/dns/metrics/class_label.hpp"

namespace dometer::dns::metrics {
    ClassLabel::ClassLabel(std::string name)
            :    dometer::metrics::Label<dometer::dns::Class>::Label(name, dometer::dns::Class::IN) {}

    std::string ClassLabel::toString(dometer::dns::Class class_) const {
        return class_;
    }
}
