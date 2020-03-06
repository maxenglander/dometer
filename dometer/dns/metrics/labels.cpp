#include <memory>
#include <string>

#include "dometer/dns/metrics/class_label.hpp"
#include "dometer/dns/metrics/labels.hpp"
#include "dometer/dns/metrics/type_label.hpp"
#include "dometer/metrics/label.hpp"

namespace dometer::dns::metrics {
    std::shared_ptr<dometer::metrics::Label<dns::dns_class>> Labels::class_(std::string name) {
        return std::make_shared<ClassLabel>(name);
    }

    std::shared_ptr<dometer::metrics::Label<dns::type>> Labels::type(std::string name) {
        return std::make_shared<TypeLabel>(name);
    }
}
