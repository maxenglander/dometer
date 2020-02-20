#include <memory>
#include <string>

#include "dometer/metrics/boolean_label.hpp"
#include "dometer/metrics/label.hpp"
#include "dometer/metrics/labels.hpp"
#include "dometer/metrics/string_label.hpp"

namespace dometer::metrics {
    std::shared_ptr<Label<bool>> Labels::boolean(std::string name) {
        return std::make_shared<BooleanLabel>(name);
    }

    std::shared_ptr<Label<std::string>> Labels::string(std::string name) {
        return std::make_shared<StringLabel>(name);
    }
}
