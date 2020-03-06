#include <ostream>

#include "dometer/util/error.hpp"

namespace dometer::util {
    class errorPrinter {
        public:
            errorPrinter(std::ostream);
            void print(error);
    };
}
