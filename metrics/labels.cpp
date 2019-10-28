#include <memory>
#include <string>

#include "metrics/boolean_label.hpp"
#include "metrics/label.hpp"
#include "metrics/labels.hpp"
#include "metrics/string_label.hpp"

namespace Dometer::Metrics {
    std::shared_ptr<Label<bool>> Labels::boolean(std::string name) {
        return std::make_shared<BooleanLabel>(name);
    }

    std::shared_ptr<Label<std::string>> Labels::string(std::string name) {
        return std::make_shared<StringLabel>(name);
    }
}
