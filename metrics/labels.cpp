#include <memory>
#include <string>

#include "metrics/boolean_label.hpp"
#include "metrics/label.hpp"
#include "metrics/labels.hpp"
#include "metrics/string_label.hpp"

namespace Dometer::Metrics {
    std::unique_ptr<Label<bool>> Labels::boolean(std::string name) {
        return std::make_unique<BooleanLabel>(name);
    }

    std::unique_ptr<Label<std::string>> Labels::string(std::string name) {
        return std::make_unique<StringLabel>(name);
    }
}
