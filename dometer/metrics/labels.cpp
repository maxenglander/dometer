#include <memory>
#include <string>

#include "dometer/metrics/boolean_label.hpp"
#include "dometer/metrics/label.hpp"
#include "dometer/metrics/labels.hpp"
#include "dometer/metrics/string_label.hpp"

namespace dometer::metrics {
    std::shared_ptr<label<bool>> labels::boolean(std::string name) {
        return std::make_shared<boolean_label>(name);
    }

    std::shared_ptr<label<std::string>> labels::string(std::string name) {
        return std::make_shared<string_label>(name);
    }
}
