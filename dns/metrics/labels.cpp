#include <memory>
#include <string>

#include "dns/metrics/labels.hpp"
#include "dns/metrics/type_label.hpp"
#include "metrics/label.hpp"

namespace dometer::dns::metrics {
    std::shared_ptr<dometer::metrics::Label<dns::Type>> Labels::type(std::string name) {
        return std::make_shared<TypeLabel>(name);
    }
}
