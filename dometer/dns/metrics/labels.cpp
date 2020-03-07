#include <memory>
#include <string>

#include "dometer/dns/metrics/class_label.hpp"
#include "dometer/dns/metrics/labels.hpp"
#include "dometer/dns/metrics/type_label.hpp"
#include "dometer/metrics/label.hpp"

namespace dometer::dns::metrics {
    std::shared_ptr<dometer::metrics::label<dns::class_>> labels::class_(std::string name) {
        return std::make_shared<class_label>(name);
    }

    std::shared_ptr<dometer::metrics::label<dns::type>> labels::type(std::string name) {
        return std::make_shared<type_label>(name);
    }
}
