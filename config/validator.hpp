#include <string>

#include "experimental/expected.hpp"

#include "util/error.hpp"

using namespace std::experimental;

namespace dometer::config {
    class Validator {
        public:
            expected<void, util::Error> validate(std::string);
    };
}
