#include <memory>
#include <string>

#include "dometer/dns/metrics/labels.hpp"
#include "dometer/dns/metrics/type_label.hpp"
#include "dometer/metrics/label.hpp"

namespace dometer::dns::metrics {
    std::shared_ptr<dometer::metrics::Label<dns::Type>> Labels::type(std::string name) {
        return std::make_shared<TypeLabel>(name);
    }
}
