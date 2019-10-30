#include <memory>
#include <string>

#include "dns/metrics/labels.hpp"
#include "dns/metrics/type_label.hpp"
#include "metrics/label.hpp"

namespace Dometer::Dns::Metrics {
    std::shared_ptr<Dometer::Metrics::Label<Dns::Type>> Labels::type(std::string name) {
        return std::make_shared<TypeLabel>(name);
    }
}
